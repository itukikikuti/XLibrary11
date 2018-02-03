class Mesh {
	PRIVATE struct ConstantBuffer {
		DirectX::XMMATRIX objectToWorld;
		DirectX::XMMATRIX worldToObject;
		DirectX::XMFLOAT3 lightDirection;
	};

	PUBLIC DirectX::XMFLOAT3 position;
	PUBLIC DirectX::XMFLOAT3 angles;
	PUBLIC DirectX::XMFLOAT3 scale;
	PUBLIC std::vector<Vertex> vertices;
	PUBLIC std::vector<int> indices;
	PUBLIC Material material;
	PRIVATE ConstantBuffer cbuffer;
	PRIVATE Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer = nullptr;
	PRIVATE Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer = nullptr;
	PRIVATE Microsoft::WRL::ComPtr<ID3D11Buffer> constantBuffer = nullptr;

	PUBLIC Mesh() : material(
		"cbuffer Object : register(b0) {"
		"    matrix _objectToWorld;"
		"    matrix _worldToObject;"
		"    float3 _lightDirection;"
		"};"
		"cbuffer Camera : register(b1) {"
		"    matrix _view;"
		"    matrix _projection;"
		"};"
		"struct VSOutput {"
		"    float4 position : SV_POSITION;"
		"    float3 normal : NORMAL;"
		"};"
		"VSOutput VS(float3 vertex : POSITION, float3 normal : NORMAL) {"
		"    VSOutput output = (VSOutput)0;"
		"    matrix vp = mul(_projection, _view);"
		"    output.position = mul(vp, mul(_objectToWorld, float4(vertex, 1.0)));"
		"    output.normal = normalize(mul(normal, (float3x3)_worldToObject));"
		"    return output;"
		"}"
		"float4 PS(VSOutput vsout) : SV_TARGET {"
		"    float lightIntensity = dot(normalize(vsout.normal), normalize(_lightDirection));"
		"    return max(float4(1, 1, 1, 1) * lightIntensity, 0);"
		"}"
	){
		Initialize();
		CreateQuad();
		Setup();
	}
	PUBLIC ~Mesh() {
	}
	PUBLIC void CreateQuad() {
		vertices.clear();
		vertices.push_back({ DirectX::XMFLOAT3(-0.5f, 0.5f, 0.0f), DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT3(0.0f, 0.0f, -1.0f) });
		vertices.push_back({ DirectX::XMFLOAT3(0.5f, 0.5f, 0.0f), DirectX::XMFLOAT2(1.0f, 0.0f), DirectX::XMFLOAT3(0.0f, 0.0f, -1.0f) });
		vertices.push_back({ DirectX::XMFLOAT3(-0.5f, -0.5f, 0.0f), DirectX::XMFLOAT2(0.0f, 1.0f), DirectX::XMFLOAT3(0.0f, 0.0f, -1.0f) });
		vertices.push_back({ DirectX::XMFLOAT3(0.5f, -0.5f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f), DirectX::XMFLOAT3(0.0f, 0.0f, -1.0f) });

		indices.clear();
		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);
		indices.push_back(3);
		indices.push_back(2);
		indices.push_back(1);
	}
	PUBLIC void Apply() {
		Setup();
	}
	PUBLIC void Draw() {
		material.Attach();

		cbuffer.objectToWorld =
			DirectX::XMMatrixScaling(scale.x, scale.y, scale.z) *
			DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(angles.z)) *
			DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(angles.y)) *
			DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(angles.x)) *
			DirectX::XMMatrixTranslation(position.x, position.y, position.z);
		cbuffer.worldToObject = DirectX::XMMatrixInverse(nullptr, cbuffer.objectToWorld);
		DirectX::XMStoreFloat3(&cbuffer.lightDirection, DirectX::XMVector3Normalize(DirectX::XMVectorSet(1.0, -1.0, 0.0f, 1.0f)));

		UINT stride = static_cast<UINT>(sizeof(Vertex));
		UINT offset = 0;
		App::GetGraphicsContext().IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);

		App::GetGraphicsContext().IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

		App::GetGraphicsContext().UpdateSubresource(constantBuffer.Get(), 0, nullptr, &cbuffer, 0, 0);
		App::GetGraphicsContext().VSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());
		App::GetGraphicsContext().HSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());
		App::GetGraphicsContext().DSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());
		App::GetGraphicsContext().GSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());
		App::GetGraphicsContext().PSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());

		App::GetGraphicsContext().DrawIndexed(static_cast<UINT>(indices.size()), 0, 0);
	}
	PRIVATE void Initialize() {
		position = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
		angles = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
		scale = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
	}
	PRIVATE void Setup() {
		D3D11_BUFFER_DESC vertexBufferDesc = {};
		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.ByteWidth = static_cast<UINT>(sizeof(Vertex) * vertices.size());
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = 0;
		D3D11_SUBRESOURCE_DATA vertexSubresourceData = {};
		vertexSubresourceData.pSysMem = &vertices[0];
		App::GetGraphicsDevice().CreateBuffer(&vertexBufferDesc, &vertexSubresourceData, vertexBuffer.GetAddressOf());

		D3D11_BUFFER_DESC indexBufferDesc = {};
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = static_cast<UINT>(sizeof(int) * indices.size());
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		D3D11_SUBRESOURCE_DATA indexSubresourceData = {};
		indexSubresourceData.pSysMem = &indices[0];
		App::GetGraphicsDevice().CreateBuffer(&indexBufferDesc, &indexSubresourceData, indexBuffer.GetAddressOf());

		D3D11_BUFFER_DESC constantBufferDesc = {};
		constantBufferDesc.ByteWidth = sizeof(ConstantBuffer);
		constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constantBufferDesc.CPUAccessFlags = 0;
		App::GetGraphicsDevice().CreateBuffer(&constantBufferDesc, nullptr, constantBuffer.GetAddressOf());
	}
};
