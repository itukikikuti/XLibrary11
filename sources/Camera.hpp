class Camera : public App::Window::Proceedable
{
	PROTECTED struct Constant
	{
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
	};

	PUBLIC Float3 position;
	PUBLIC Float3 angles;
	PROTECTED float fieldOfView;
	PROTECTED float nearClip;
	PROTECTED float farClip;
	PROTECTED Constant constant;
	PROTECTED ATL::CComPtr<ID3D11RenderTargetView> renderTargetView = nullptr;
	PROTECTED ATL::CComPtr<ID3D11DepthStencilView> depthStencilView = nullptr;
	PROTECTED ATL::CComPtr<ID3D11Texture2D> renderTexture = nullptr;
	PROTECTED ATL::CComPtr<ID3D11Texture2D> depthTexture = nullptr;
	PROTECTED ATL::CComPtr<ID3D11Buffer> constantBuffer = nullptr;

	PUBLIC Camera()
	{
		App::Initialize();
		Initialize();
		Create();
	}
	PUBLIC virtual ~Camera()
	{
		App::RemoveProcedure(this);
	}
	PROTECTED virtual void Initialize()
	{
		position = Float3(0.0f, 0.0f, -5.0f);
		angles = Float3(0.0f, 0.0f, 0.0f);

		SetPerspective(60.0f, 0.1f, 1000.0f);

		App::AddProcedure(this);
	}
	PROTECTED virtual void Create()
	{
		renderTexture.Release();
		App::GetGraphicsMemory().GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&renderTexture));
		renderTargetView.Release();
		App::GetGraphicsDevice().CreateRenderTargetView(renderTexture, nullptr, &renderTargetView);

		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		App::GetGraphicsMemory().GetDesc(&swapChainDesc);

		depthTexture.Release();
		D3D11_TEXTURE2D_DESC textureDesc = {};
		textureDesc.Width = static_cast<UINT>(App::GetWindowSize().x);
		textureDesc.Height = static_cast<UINT>(App::GetWindowSize().y);
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = DXGI_FORMAT_R32_TYPELESS;
		textureDesc.SampleDesc.Count = swapChainDesc.SampleDesc.Count;
		textureDesc.SampleDesc.Quality = swapChainDesc.SampleDesc.Quality;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		textureDesc.CPUAccessFlags = 0;
		textureDesc.MiscFlags = 0;
		App::GetGraphicsDevice().CreateTexture2D(&textureDesc, nullptr, &depthTexture);

		depthStencilView.Release();
		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc = {};
		depthStencilViewDesc.Format = DXGI_FORMAT_D32_FLOAT;
		if (swapChainDesc.SampleDesc.Count == 0)
		{
			depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			depthStencilViewDesc.Texture2D.MipSlice = 0;
		}
		else
		{
			depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
		}
		App::GetGraphicsDevice().CreateDepthStencilView(depthTexture, &depthStencilViewDesc, &depthStencilView);

		constantBuffer.Release();
		D3D11_BUFFER_DESC constantBufferDesc = {};
		constantBufferDesc.ByteWidth = static_cast<UINT>(sizeof(Constant));
		constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constantBufferDesc.CPUAccessFlags = 0;
		App::GetGraphicsDevice().CreateBuffer(&constantBufferDesc, nullptr, &constantBuffer);
	}
	PUBLIC void SetPerspective(float fieldOfView, float nearClip, float farClip)
	{
		this->fieldOfView = fieldOfView;
		this->nearClip = nearClip;
		this->farClip = farClip;
		constant.projection = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(fieldOfView), App::GetWindowSize().x / (float)App::GetWindowSize().y, nearClip, farClip);
	}
	PUBLIC virtual void Update()
	{
		constant.view =
			DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(angles.z)) *
			DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(angles.y)) *
			DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(angles.x)) *
			DirectX::XMMatrixTranslation(position.x, position.y, position.z);
		constant.view = DirectX::XMMatrixInverse(nullptr, constant.view);

		App::GetGraphicsContext().UpdateSubresource(constantBuffer, 0, nullptr, &constant, 0, 0);
		App::GetGraphicsContext().VSSetConstantBuffers(1, 1, &constantBuffer.p);
		App::GetGraphicsContext().HSSetConstantBuffers(1, 1, &constantBuffer.p);
		App::GetGraphicsContext().DSSetConstantBuffers(1, 1, &constantBuffer.p);
		App::GetGraphicsContext().GSSetConstantBuffers(1, 1, &constantBuffer.p);
		App::GetGraphicsContext().PSSetConstantBuffers(1, 1, &constantBuffer.p);

		App::GetGraphicsContext().OMSetRenderTargets(1, &renderTargetView.p, depthStencilView);
		
		static float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		App::GetGraphicsContext().ClearRenderTargetView(renderTargetView, color);
		App::GetGraphicsContext().ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}
	PROTECTED void OnProceed(HWND, UINT message, WPARAM, LPARAM) override
	{
		if (message != WM_SIZE)
			return;

		if (App::GetWindowSize().x <= 0.0f || App::GetWindowSize().y <= 0.0f)
			return;

		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		App::GetGraphicsMemory().GetDesc(&swapChainDesc);

		ATL::CComPtr<ID3D11RenderTargetView> nullRenderTarget = nullptr;
		ATL::CComPtr<ID3D11DepthStencilView> nullDepthStencil = nullptr;
		App::GetGraphicsContext().OMSetRenderTargets(1, &nullRenderTarget, nullDepthStencil);
		renderTargetView.Release();
		depthStencilView.Release();
		renderTexture.Release();
		depthTexture.Release();
		App::GetGraphicsContext().Flush();
		App::GetGraphicsMemory().ResizeBuffers(swapChainDesc.BufferCount, static_cast<UINT>(App::GetWindowSize().x), static_cast<UINT>(App::GetWindowSize().y), swapChainDesc.BufferDesc.Format, swapChainDesc.Flags);

		SetPerspective(fieldOfView, nearClip, farClip);
		Create();
	}
};
