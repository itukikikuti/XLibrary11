class Camera {
	PROTECTED struct Constant {
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
	};

	PUBLIC Float3 position;
	PUBLIC Float3 angles;
	PROTECTED float fieldOfView;
	PROTECTED float nearClip;
	PROTECTED float farClip;
	PROTECTED Constant constant;
	PROTECTED Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView = nullptr;
	PROTECTED Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView = nullptr;
	PROTECTED Microsoft::WRL::ComPtr<ID3D11Texture2D> renderTexture = nullptr;
	PROTECTED Microsoft::WRL::ComPtr<ID3D11Texture2D> depthTexture = nullptr;
	PROTECTED Microsoft::WRL::ComPtr<ID3D11Buffer> constantBuffer = nullptr;

	PUBLIC Camera() {
		Initialize();
		Setup();
	}
	PUBLIC virtual ~Camera() {
	}
	PUBLIC void SetPerspective(float fieldOfView, float nearClip, float farClip) {
		this->fieldOfView = fieldOfView;
		this->nearClip = nearClip;
		this->farClip = farClip;
		constant.projection = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(fieldOfView), App::GetWindowSize().x / (float)App::GetWindowSize().y, nearClip, farClip);
	}
	PUBLIC virtual void Update() {
		TryResize();

		constant.view =
			DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(angles.z)) *
			DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(angles.y)) *
			DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(angles.x)) *
			DirectX::XMMatrixTranslation(position.x, position.y, position.z);
		constant.view = DirectX::XMMatrixInverse(nullptr, constant.view);

		App::GetGraphicsContext().UpdateSubresource(constantBuffer.Get(), 0, nullptr, &constant, 0, 0);
		App::GetGraphicsContext().VSSetConstantBuffers(1, 1, constantBuffer.GetAddressOf());
		App::GetGraphicsContext().HSSetConstantBuffers(1, 1, constantBuffer.GetAddressOf());
		App::GetGraphicsContext().DSSetConstantBuffers(1, 1, constantBuffer.GetAddressOf());
		App::GetGraphicsContext().GSSetConstantBuffers(1, 1, constantBuffer.GetAddressOf());
		App::GetGraphicsContext().PSSetConstantBuffers(1, 1, constantBuffer.GetAddressOf());

		App::GetGraphicsContext().OMSetRenderTargets(1, renderTargetView.GetAddressOf(), depthStencilView.Get());
		
		static float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		App::GetGraphicsContext().ClearRenderTargetView(renderTargetView.Get(), color);
		App::GetGraphicsContext().ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}
	PROTECTED void Initialize() {
		position = Float3(0.0f, 0.0f, -5.0f);
		angles = Float3(0.0f, 0.0f, 0.0f);

		SetPerspective(60.0f, 0.1f, 1000.0f);
	}
	PROTECTED void Setup() {
		renderTexture.Reset();
		App::GetGraphicsMemory().GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(renderTexture.GetAddressOf()));
		renderTargetView.Reset();
		App::GetGraphicsDevice().CreateRenderTargetView(renderTexture.Get(), nullptr, renderTargetView.GetAddressOf());
		
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		App::GetGraphicsMemory().GetDesc(&swapChainDesc);

		depthTexture.Reset();
		D3D11_TEXTURE2D_DESC textureDesc = {};
		textureDesc.Width = static_cast<float>(App::GetWindowSize().x);
		textureDesc.Height = static_cast<float>(App::GetWindowSize().y);
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = DXGI_FORMAT_R32_TYPELESS;
		textureDesc.SampleDesc.Count = swapChainDesc.SampleDesc.Count;
		textureDesc.SampleDesc.Quality = swapChainDesc.SampleDesc.Quality;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		textureDesc.CPUAccessFlags = 0;
		textureDesc.MiscFlags = 0;
		App::GetGraphicsDevice().CreateTexture2D(&textureDesc, nullptr, depthTexture.GetAddressOf());

		depthStencilView.Reset();
		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc = {};
		depthStencilViewDesc.Format = DXGI_FORMAT_D32_FLOAT;
		if (swapChainDesc.SampleDesc.Count == 0) {
			depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			depthStencilViewDesc.Texture2D.MipSlice = 0;
		}
		else {
			depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
		}
		App::GetGraphicsDevice().CreateDepthStencilView(depthTexture.Get(), &depthStencilViewDesc, depthStencilView.GetAddressOf());

		D3D11_VIEWPORT viewPort = {};
		viewPort.Width = static_cast<float>(App::GetWindowSize().x);
		viewPort.Height = static_cast<float>(App::GetWindowSize().y);
		viewPort.MinDepth = 0.0f;
		viewPort.MaxDepth = 1.0f;
		viewPort.TopLeftX = 0;
		viewPort.TopLeftY = 0;
		App::GetGraphicsContext().RSSetViewports(1, &viewPort);

		constantBuffer.Reset();
		D3D11_BUFFER_DESC constantBufferDesc = {};
		constantBufferDesc.ByteWidth = static_cast<UINT>(sizeof(Constant));
		constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constantBufferDesc.CPUAccessFlags = 0;
		App::GetGraphicsDevice().CreateBuffer(&constantBufferDesc, nullptr, constantBuffer.GetAddressOf());
	}
	PROTECTED void TryResize() {
		for (UINT message : App::GetWindowMessages()) {
			if (message != WM_SIZE) {
				continue;
			}
			if (App::GetWindowSize().x <= 0.0f || App::GetWindowSize().y <= 0.0f) {
				continue;
			}
			
			DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
			App::GetGraphicsMemory().GetDesc(&swapChainDesc);

			Microsoft::WRL::ComPtr<ID3D11RenderTargetView> nullRenderTarget = nullptr;
			Microsoft::WRL::ComPtr<ID3D11DepthStencilView> nullDepthStencil = nullptr;
			App::GetGraphicsContext().OMSetRenderTargets(1, nullRenderTarget.GetAddressOf(), nullDepthStencil.Get());
			renderTargetView.Reset();
			depthStencilView.Reset();
			renderTexture.Reset();
			depthTexture.Reset();
			App::GetGraphicsContext().Flush();
			App::GetGraphicsMemory().ResizeBuffers(swapChainDesc.BufferCount, static_cast<UINT>(App::GetWindowSize().x), static_cast<UINT>(App::GetWindowSize().y), swapChainDesc.BufferDesc.Format, swapChainDesc.Flags);

			SetPerspective(fieldOfView, nearClip, farClip);
			Setup();
			return;
		}
	}
};
