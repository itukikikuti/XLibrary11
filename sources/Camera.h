class Camera {
	PRIVATE struct ConstantBuffer {
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
	};

	PUBLIC DirectX::XMFLOAT3 position;
	PUBLIC DirectX::XMFLOAT3 angles;
	PRIVATE ConstantBuffer cbuffer;
	PRIVATE ID3D11Buffer* constantBuffer;
	PRIVATE ID3D11RenderTargetView* renderTarget = nullptr;
	PRIVATE ID3D11Texture2D* texture = nullptr;

	PUBLIC Camera() {
		App::GetGraphicsMemory().GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&texture);
		App::GetGraphicsDevice().CreateRenderTargetView(texture, nullptr, &renderTarget);
		App::GetGraphicsContext().OMSetRenderTargets(1, &renderTarget, nullptr);

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
		App::GetGraphicsDevice().CreateBuffer(&constantBufferDesc, nullptr, &constantBuffer);

		SetPerspective(60.0f, App::GetWindowSize().x / (float)App::GetWindowSize().y, 0.1f, 2000.0f);

		position = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
		angles = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	PUBLIC ~Camera() {
		if (constantBuffer) {
			constantBuffer->Release();
			constantBuffer = nullptr;
		}

		if (renderTarget) {
			renderTarget->Release();
			renderTarget = nullptr;
		}

		if (texture) {
			texture->Release();
			texture = nullptr;
		}
	}
	PUBLIC void SetPerspective(float fieldOfView, float aspectRatio, float nearClip, float farClip) {
		cbuffer.projection = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(fieldOfView), aspectRatio, nearClip, farClip);
	}
	PUBLIC void Refresh() {
		static float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		App::GetGraphicsContext().ClearRenderTargetView(renderTarget, color);

		cbuffer.view = DirectX::XMMatrixRotationRollPitchYaw(DirectX::XMConvertToRadians(angles.x), DirectX::XMConvertToRadians(angles.y), DirectX::XMConvertToRadians(angles.z)) * DirectX::XMMatrixTranslation(position.x, position.y, position.z);
		cbuffer.view = DirectX::XMMatrixInverse(nullptr, cbuffer.view);
		App::GetGraphicsContext().UpdateSubresource(constantBuffer, 0, nullptr, &cbuffer, 0, 0);
		App::GetGraphicsContext().VSSetConstantBuffers(1, 1, &constantBuffer);
		App::GetGraphicsContext().PSSetConstantBuffers(1, 1, &constantBuffer);
	}
};
