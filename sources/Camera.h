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
		CreateRenderTarget();

		D3D11_BUFFER_DESC constantBufferDesc = {};
		constantBufferDesc.ByteWidth = sizeof(ConstantBuffer);
		constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constantBufferDesc.CPUAccessFlags = 0;
		App::GetGraphicsDevice().CreateBuffer(&constantBufferDesc, nullptr, constantBuffer.GetAddressOf());

		SetPerspective(60.0f, 0.1f, 2000.0f);

		position = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
		angles = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	PUBLIC ~Camera() {
	}
	PUBLIC void SetPerspective(float fieldOfView, float nearClip, float farClip) {
		this->fieldOfView = fieldOfView;
		this->nearClip = nearClip;
		this->farClip = farClip;
		cbuffer.projection = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(fieldOfView), App::GetWindowSize().x / (float)App::GetWindowSize().y, nearClip, farClip);
	}
	PUBLIC void Refresh() {
		for (UINT message : App::GetWindowMessages()) {
			if (message == WM_SIZE) {
				Microsoft::WRL::ComPtr<ID3D11RenderTargetView> nullView = nullptr;
				App::GetGraphicsContext().OMSetRenderTargets(1, nullView.GetAddressOf(), nullptr);
				renderTarget.Reset();
				texture.Reset();
				App::GetGraphicsContext().Flush();
				App::GetGraphicsMemory().ResizeBuffers(2, App::GetWindowSize().x, App::GetWindowSize().y, DXGI_FORMAT_R8G8B8A8_UNORM, 0);

				CreateRenderTarget();

				SetPerspective(fieldOfView, nearClip, farClip);
				break;
			}
		}

		static float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		App::GetGraphicsContext().ClearRenderTargetView(renderTarget.Get(), color);

		cbuffer.view =
			DirectX::XMMatrixRotationRollPitchYaw(DirectX::XMConvertToRadians(angles.x), DirectX::XMConvertToRadians(angles.y), DirectX::XMConvertToRadians(angles.z)) *
			DirectX::XMMatrixTranslation(position.x, position.y, position.z);
		cbuffer.view = DirectX::XMMatrixInverse(nullptr, cbuffer.view);
		App::GetGraphicsContext().UpdateSubresource(constantBuffer.Get(), 0, nullptr, &cbuffer, 0, 0);
		App::GetGraphicsContext().VSSetConstantBuffers(1, 1, constantBuffer.GetAddressOf());
		App::GetGraphicsContext().PSSetConstantBuffers(1, 1, constantBuffer.GetAddressOf());
	}
	PRIVATE void CreateRenderTarget() {
		App::GetGraphicsMemory().GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(texture.GetAddressOf()));
		App::GetGraphicsDevice().CreateRenderTargetView(texture.Get(), nullptr, renderTarget.GetAddressOf());
		App::GetGraphicsContext().OMSetRenderTargets(1, renderTarget.GetAddressOf(), nullptr);

		D3D11_VIEWPORT viewPort = {};
		viewPort.Width = (float)App::GetWindowSize().x;
		viewPort.Height = (float)App::GetWindowSize().y;
		viewPort.MinDepth = 0.0f;
		viewPort.MaxDepth = 1.0f;
		viewPort.TopLeftX = 0;
		viewPort.TopLeftY = 0;
		App::GetGraphicsContext().RSSetViewports(1, &viewPort);
	}
};
