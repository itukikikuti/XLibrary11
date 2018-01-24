class Camera {
	PRIVATE struct ConstantBuffer {
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
	};

	PUBLIC DirectX::XMFLOAT3 position;
	PUBLIC DirectX::XMFLOAT3 angles;
	PRIVATE ConstantBuffer cbuffer;
	PRIVATE ID3D11Buffer* constantBuffer;

	PUBLIC Camera() {
		D3D11_BUFFER_DESC constantBufferDesc = {};
		constantBufferDesc.ByteWidth = sizeof(ConstantBuffer);
		constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constantBufferDesc.CPUAccessFlags = 0;
		App::GetDevice().CreateBuffer(&constantBufferDesc, nullptr, &constantBuffer);

		SetPerspective(60.0f, App::GetWindowSize().x / (float)App::GetWindowSize().y, 0.1f, 2000.0f);

		position = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
		angles = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	PUBLIC void SetPerspective(float fieldOfView, float aspectRatio, float nearClip, float farClip) {
		cbuffer.projection = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(fieldOfView), aspectRatio, nearClip, farClip);
	}
	PUBLIC void Update() {
		cbuffer.view = DirectX::XMMatrixRotationRollPitchYaw(DirectX::XMConvertToRadians(angles.x), DirectX::XMConvertToRadians(angles.y), DirectX::XMConvertToRadians(angles.z)) * DirectX::XMMatrixTranslation(position.x, position.y, position.z);
		cbuffer.view = DirectX::XMMatrixInverse(nullptr, cbuffer.view);
		App::GetContext().UpdateSubresource(constantBuffer, 0, nullptr, &cbuffer, 0, 0);
		App::GetContext().VSSetConstantBuffers(1, 1, &constantBuffer);
		App::GetContext().PSSetConstantBuffers(1, 1, &constantBuffer);
	}
};
