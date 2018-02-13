class Mesh {
	PROTECTED struct Constant {
		DirectX::XMMATRIX world;
		Float3 lightDirection;
	};

	PUBLIC Float3 position;
	PUBLIC Float3 angles;
	PUBLIC Float3 scale;
	PUBLIC std::vector<Vertex> vertices;
	PUBLIC std::vector<int> indices;
	PUBLIC Material material;
	PROTECTED Constant constant;
	PROTECTED Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer = nullptr;
	PROTECTED Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer = nullptr;
	PROTECTED Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerState = nullptr;

	PUBLIC Mesh() :
		material(
			"cbuffer Object : register(b0) {"
			"    matrix _world;"
			"    float3 _lightDirection;"
			"};"
			"cbuffer Camera : register(b1) {"
			"    matrix _view;"
			"    matrix _projection;"
			"};"
			"Texture2D tex : register(t0);"
			"SamplerState samp: register(s0);"
			"struct VSOutput {"
			"    float4 position : SV_POSITION;"
			"    float4 normal : NORMAL;"
			"    float2 uv : TEXCOORD;"
			"};"
			"VSOutput VS(float3 vertex : POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD) {"
			"    VSOutput output = (VSOutput)0;"
			"    output.position = mul(_world, float4(vertex, 1.0));"
			"    output.position = mul(_view, output.position);"
			"    output.position = mul(_projection, output.position);"
			"    output.normal = normalize(mul(_world, float4(normal, 1)));"
			"    output.uv = uv;"
			"    return output;"
			"}"
			"float4 PS(VSOutput pixel) : SV_TARGET {"
			"    float diffuse = dot(-_lightDirection, pixel.normal.xyz);"
			"    return max(0, float4(tex.Sample(samp, pixel.uv).rgb * diffuse, 1));"
			"}") {
		Initialize();
		Setup();
		SetCullingMode(D3D11_CULL_BACK);
	}
	PUBLIC virtual ~Mesh() {
	}
	PUBLIC void CreateQuad(bool shouldClear = true) {
		if (shouldClear) {
			vertices.clear();
			indices.clear();
		}

		vertices.push_back(Vertex(Float3(-0.5f, 0.5f, 0.0f), Float3(0.0f, 0.0f, -1.0f), Float2(0.0f, 0.0f)));
		vertices.push_back(Vertex(Float3(0.5f, 0.5f, 0.0f), Float3(0.0f, 0.0f, -1.0f), Float2(1.0f, 0.0f)));
		vertices.push_back(Vertex(Float3(-0.5f, -0.5f, 0.0f), Float3(0.0f, 0.0f, -1.0f), Float2(0.0f, 1.0f)));
		vertices.push_back(Vertex(Float3(0.5f, -0.5f, 0.0f), Float3(0.0f, 0.0f, -1.0f), Float2(1.0f, 1.0f)));

		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);
		indices.push_back(3);
		indices.push_back(2);
		indices.push_back(1);
	}
	PUBLIC void CreateCube(bool shouldClear = true) {
		if (shouldClear) {
			vertices.clear();
			indices.clear();
		}

		vertices.push_back(Vertex(Float3(-0.5f, 0.5f, -0.5f), Float3(0.0f, 0.0f, -1.0f), Float2(0.0f, 0.0f)));
		vertices.push_back(Vertex(Float3(0.5f, 0.5f, -0.5f), Float3(0.0f, 0.0f, -1.0f), Float2(1.0f, 0.0f)));
		vertices.push_back(Vertex(Float3(-0.5f, -0.5f, -0.5f), Float3(0.0f, 0.0f, -1.0f), Float2(0.0f, 1.0f)));
		vertices.push_back(Vertex(Float3(0.5f, -0.5f, -0.5f), Float3(0.0f, 0.0f, -1.0f), Float2(1.0f, 1.0f)));

		vertices.push_back(Vertex(Float3(0.5f, 0.5f, -0.5f), Float3(1.0f, 0.0f, 0.0f), Float2(0.0f, 0.0f)));
		vertices.push_back(Vertex(Float3(0.5f, 0.5f, 0.5f), Float3(1.0f, 0.0f, 0.0f), Float2(1.0f, 0.0f)));
		vertices.push_back(Vertex(Float3(0.5f, -0.5f, -0.5f), Float3(1.0f, 0.0f, 0.0f), Float2(0.0f, 1.0f)));
		vertices.push_back(Vertex(Float3(0.5f, -0.5f, 0.5f), Float3(1.0f, 0.0f, 0.0f), Float2(1.0f, 1.0f)));
		
		vertices.push_back(Vertex(Float3(0.5f, 0.5f, 0.5f), Float3(0.0f, 0.0f, 1.0f), Float2(0.0f, 0.0f)));
		vertices.push_back(Vertex(Float3(-0.5f, 0.5f, 0.5f), Float3(0.0f, 0.0f, 1.0f), Float2(1.0f, 0.0f)));
		vertices.push_back(Vertex(Float3(0.5f, -0.5f, 0.5f), Float3(0.0f, 0.0f, 1.0f), Float2(0.0f, 1.0f)));
		vertices.push_back(Vertex(Float3(-0.5f, -0.5f, 0.5f), Float3(0.0f, 0.0f, 1.0f), Float2(1.0f, 1.0f)));
		
		vertices.push_back(Vertex(Float3(-0.5f, 0.5f, 0.5f), Float3(-1.0f, 0.0f, 0.0f), Float2(0.0f, 0.0f)));
		vertices.push_back(Vertex(Float3(-0.5f, 0.5f, -0.5f), Float3(-1.0f, 0.0f, 0.0f), Float2(1.0f, 0.0f)));
		vertices.push_back(Vertex(Float3(-0.5f, -0.5f, 0.5f), Float3(-1.0f, 0.0f, 0.0f), Float2(0.0f, 1.0f)));
		vertices.push_back(Vertex(Float3(-0.5f, -0.5f, -0.5f), Float3(-1.0f, 0.0f, 0.0f), Float2(1.0f, 1.0f)));
		
		vertices.push_back(Vertex(Float3(-0.5f, 0.5f, 0.5f), Float3(0.0f, 1.0f, 0.0f), Float2(0.0f, 0.0f)));
		vertices.push_back(Vertex(Float3(0.5f, 0.5f, 0.5f), Float3(0.0f, 1.0f, 0.0f), Float2(1.0f, 0.0f)));
		vertices.push_back(Vertex(Float3(-0.5f, 0.5f, -0.5f), Float3(0.0f, 1.0f, 0.0f), Float2(0.0f, 1.0f)));
		vertices.push_back(Vertex(Float3(0.5f, 0.5f, -0.5f), Float3(0.0f, 1.0f, 0.0f), Float2(1.0f, 1.0f)));
		
		vertices.push_back(Vertex(Float3(-0.5f, -0.5f, -0.5f), Float3(0.0f, -1.0f, 0.0f), Float2(0.0f, 0.0f)));
		vertices.push_back(Vertex(Float3(0.5f, -0.5f, -0.5f), Float3(0.0f, -1.0f, 0.0f), Float2(1.0f, 0.0f)));
		vertices.push_back(Vertex(Float3(-0.5f, -0.5f, 0.5f), Float3(0.0f, -1.0f, 0.0f), Float2(0.0f, 1.0f)));
		vertices.push_back(Vertex(Float3(0.5f, -0.5f, 0.5f), Float3(0.0f, -1.0f, 0.0f), Float2(1.0f, 1.0f)));

		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);
		indices.push_back(3);
		indices.push_back(2);
		indices.push_back(1);

		indices.push_back(4);
		indices.push_back(5);
		indices.push_back(6);
		indices.push_back(7);
		indices.push_back(6);
		indices.push_back(5);

		indices.push_back(8);
		indices.push_back(9);
		indices.push_back(10);
		indices.push_back(11);
		indices.push_back(10);
		indices.push_back(9);

		indices.push_back(12);
		indices.push_back(13);
		indices.push_back(14);
		indices.push_back(15);
		indices.push_back(14);
		indices.push_back(13);

		indices.push_back(16);
		indices.push_back(17);
		indices.push_back(18);
		indices.push_back(19);
		indices.push_back(18);
		indices.push_back(17);

		indices.push_back(20);
		indices.push_back(21);
		indices.push_back(22);
		indices.push_back(23);
		indices.push_back(22);
		indices.push_back(21);
	}
	PUBLIC void Apply() {
		Setup();
	}
	PUBLIC virtual void Draw() {
		material.Attach();

		constant.world =
			DirectX::XMMatrixScaling(scale.x, scale.y, scale.z) *
			DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(angles.z)) *
			DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(angles.y)) *
			DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(angles.x)) *
			DirectX::XMMatrixTranslation(position.x, position.y, position.z);
		DirectX::XMStoreFloat3(&constant.lightDirection, DirectX::XMVector3Normalize(DirectX::XMVectorSet(0.25f, -1.0f, 0.5f, 0.0f)));

		if (vertexBuffer == nullptr) {
			return;
		}

		App::GetGraphicsContext().RSSetState(rasterizerState.Get());

		UINT stride = static_cast<UINT>(sizeof(Vertex));
		UINT offset = 0;
		App::GetGraphicsContext().IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);

		if (indexBuffer == nullptr) {
			App::GetGraphicsContext().Draw(static_cast<UINT>(vertices.size()), 0);
		}
		else {
			App::GetGraphicsContext().IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
			App::GetGraphicsContext().DrawIndexed(static_cast<UINT>(indices.size()), 0, 0);
		}
	}
	PUBLIC void SetCullingMode(D3D11_CULL_MODE cullingMode) {
		D3D11_RASTERIZER_DESC rasterizerDesc = {};
		rasterizerDesc.FillMode = D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = cullingMode;
		App::GetGraphicsDevice().CreateRasterizerState(&rasterizerDesc, &rasterizerState);
	}
	PROTECTED void Initialize() {
		position = Float3(0.0f, 0.0f, 0.0f);
		angles = Float3(0.0f, 0.0f, 0.0f);
		scale = Float3(1.0f, 1.0f, 1.0f);
	}
	PROTECTED void Setup() {
		if (vertices.size() > 0) {
			vertexBuffer.Reset();
			D3D11_BUFFER_DESC vertexBufferDesc = {};
			vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
			vertexBufferDesc.ByteWidth = static_cast<UINT>(sizeof(Vertex) * vertices.size());
			vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			vertexBufferDesc.CPUAccessFlags = 0;
			D3D11_SUBRESOURCE_DATA vertexSubresourceData = {};
			vertexSubresourceData.pSysMem = &vertices[0];
			App::GetGraphicsDevice().CreateBuffer(&vertexBufferDesc, &vertexSubresourceData, vertexBuffer.GetAddressOf());
		}

		if (indices.size() > 0) {
			indexBuffer.Reset();
			D3D11_BUFFER_DESC indexBufferDesc = {};
			indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
			indexBufferDesc.ByteWidth = static_cast<UINT>(sizeof(int) * indices.size());
			indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			indexBufferDesc.CPUAccessFlags = 0;
			D3D11_SUBRESOURCE_DATA indexSubresourceData = {};
			indexSubresourceData.pSysMem = &indices[0];
			App::GetGraphicsDevice().CreateBuffer(&indexBufferDesc, &indexSubresourceData, indexBuffer.GetAddressOf());
		}

		material.SetCBuffer(&constant, sizeof(Constant));
	}
};
