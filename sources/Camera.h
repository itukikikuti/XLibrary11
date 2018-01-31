class Camera {
	PRIVATE struct ConstantBuffer {
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
	};

	PUBLIC DirectX::XMFLOAT3 position;
	PUBLIC DirectX::XMFLOAT3 angles;
	PRIVATE float fieldOfView;
	PRIVATE float nearClip;
	PRIVATE float farClip;
	PRIVATE ConstantBuffer cbuffer;
	PRIVATE Microsoft::WRL::ComPtr<ID3D11Buffer> constantBuffer = nullptr;
	PRIVATE Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTarget = nullptr;
	PRIVATE Microsoft::WRL::ComPtr<ID3D11Texture2D> texture = nullptr;

	PUBLIC Camera() {
		Initialize();
		Setup();
	}
	PUBLIC ~Camera() {
	}
	PUBLIC void SetPerspective(float fieldOfView, float nearClip, float farClip) {
		this->fieldOfView = fieldOfView;
		this->nearClip = nearClip;
		this->farClip = farClip;
		cbuffer.projection = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(fieldOfView), App::GetWindowSize().x / (float)App::GetWindowSize().y, nearClip, farClip);
	}
	PUBLIC void Update() {
		TryResize();

		cbuffer.view =
			DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(angles.z)) *
			DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(angles.y)) *
			DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(angles.x)) *
			DirectX::XMMatrixTranslation(position.x, position.y, position.z);
		cbuffer.view = DirectX::XMMatrixInverse(nullptr, cbuffer.view);

		App::GetGraphicsContext().OMSetRenderTargets(1, renderTarget.GetAddressOf(), nullptr);

		static float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		App::GetGraphicsContext().ClearRenderTargetView(renderTarget.Get(), color);

		App::GetGraphicsContext().UpdateSubresource(constantBuffer.Get(), 0, nullptr, &cbuffer, 0, 0);
		App::GetGraphicsContext().VSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());
		App::GetGraphicsContext().PSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());
	}
	PRIVATE void Initialize() {
		position = DirectX::XMFLOAT3(0.0f, 0.0f, -5.0f);
		angles = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);

		SetPerspective(60.0f, 0.1f, 1000.0f);
	}
	PRIVATE void Setup() {
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
		constantBufferDesc.ByteWidth = sizeof(ConstantBuffer);
		constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constantBufferDesc.CPUAccessFlags = 0;
		App::GetGraphicsDevice().CreateBuffer(&constantBufferDesc, nullptr, constantBuffer.GetAddressOf());
	}
	PRIVATE void TryResize() {
		for (UINT message : App::GetWindowMessages()) {
			if (message == WM_SIZE) {
				App::GetGraphicsContext().OMSetRenderTargets(1, nullptr, nullptr);
				renderTarget.Reset();
				texture.Reset();
				App::GetGraphicsContext().Flush();
				App::GetGraphicsMemory().ResizeBuffers(2, App::GetWindowSize().x, App::GetWindowSize().y, DXGI_FORMAT_R8G8B8A8_UNORM, 0);

				SetPerspective(fieldOfView, nearClip, farClip);
				Setup();
				break;
			}
		}
	}
};
