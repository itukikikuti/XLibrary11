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
	PROTECTED Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTarget = nullptr;
	PROTECTED Microsoft::WRL::ComPtr<ID3D11Texture2D> texture = nullptr;
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

		App::GetGraphicsContext().OMSetRenderTargets(1, renderTarget.GetAddressOf(), nullptr);

		static float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		App::GetGraphicsContext().ClearRenderTargetView(renderTarget.Get(), color);
	}
	PROTECTED void Initialize() {
		position = Float3(0.0f, 0.0f, -5.0f);
		angles = Float3(0.0f, 0.0f, 0.0f);

		SetPerspective(60.0f, 0.1f, 1000.0f);
	}
	PROTECTED void Setup() {
		App::GetGraphicsMemory().GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(texture.GetAddressOf()));
		App::GetGraphicsDevice().CreateRenderTargetView(texture.Get(), nullptr, renderTarget.GetAddressOf());

		D3D11_VIEWPORT viewPort = {};
		viewPort.Width = (float)App::GetWindowSize().x;
		viewPort.Height = (float)App::GetWindowSize().y;
		viewPort.MinDepth = 0.0f;
		viewPort.MaxDepth = 1.0f;
		viewPort.TopLeftX = 0;
		viewPort.TopLeftY = 0;
		App::GetGraphicsContext().RSSetViewports(1, &viewPort);

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

			Microsoft::WRL::ComPtr<ID3D11RenderTargetView> nullRenderTarget = nullptr;
			App::GetGraphicsContext().OMSetRenderTargets(1, nullRenderTarget.GetAddressOf(), nullptr);
			renderTarget.Reset();
			texture.Reset();
			App::GetGraphicsContext().Flush();
			App::GetGraphicsMemory().ResizeBuffers(2, static_cast<UINT>(App::GetWindowSize().x), static_cast<UINT>(App::GetWindowSize().y), DXGI_FORMAT_R8G8B8A8_UNORM, 0);

			SetPerspective(fieldOfView, nearClip, farClip);
			Setup();
			return;
		}
	}
};
