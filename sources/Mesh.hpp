class Mesh {
public:
    Float3 position;
    Float3 angles;
    Float3 scale;
    std::vector<Vertex> vertices;
    std::vector<UINT> indices;
    Material material;

    Mesh()
    {
        App::Initialize();

        position = Float3(0.0f, 0.0f, 0.0f);
        angles = Float3(0.0f, 0.0f, 0.0f);
        scale = Float3(1.0f, 1.0f, 1.0f);

        material = Material(
            "cbuffer Object : register(b0)"
            "{"
            "    matrix _world;"
            "    float3 _lightDirection;"
            "};"
            "cbuffer Camera : register(b1)"
            "{"
            "    matrix _view;"
            "    matrix _projection;"
            "};"
            "Texture2D tex : register(t0);"
            "SamplerState samp: register(s0);"
            "struct VSOutput"
            "{"
            "    float4 position : SV_POSITION;"
            "    float4 normal : NORMAL;"
            "    float2 uv : TEXCOORD;"
            "};"
            "VSOutput VS(float3 position : POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD)"
            "{"
            "    VSOutput output = (VSOutput)0;"
            "    output.position = mul(_world, float4(position, 1.0));"
            "    output.position = mul(_view, output.position);"
            "    output.position = mul(_projection, output.position);"
            "    output.normal = normalize(mul(_world, float4(normal, 1)));"
            "    output.uv = uv;"
            "    return output;"
            "}"
            "float4 PS(VSOutput pixel) : SV_TARGET"
            "{"
            "    float diffuse = dot(-_lightDirection, normalize(pixel.normal).xyz) + 0.25;"
            "    return max(0, float4(tex.Sample(samp, pixel.uv).rgb * diffuse, 1));"
            "}"
        );

        SetCullingMode(D3D11_CULL_BACK);

        CreateCube();
        Apply();
    }
    ~Mesh()
    {
    }
    void CreatePlane(Float2 size, Float3 offset = Float3(0.0f, 0.0f, 0.0f), bool shouldClear = true, Float3 leftDirection = Float3(1.0f, 0.0f, 0.0f), Float3 upDirection = Float3(0.0f, 1.0f, 0.0f), Float3 forwardDirection = Float3(0.0f, 0.0f, 1.0f))
    {
        if (shouldClear)
        {
            vertices.clear();
            indices.clear();
        }

        leftDirection = DirectX::XMVector3Normalize(leftDirection);
        upDirection = DirectX::XMVector3Normalize(upDirection);
        forwardDirection = DirectX::XMVector3Normalize(forwardDirection);

        vertices.push_back(Vertex(leftDirection * -size.x + upDirection * size.y + offset, -forwardDirection, Float2(0.0f, 0.0f)));
        vertices.push_back(Vertex(leftDirection * size.x + upDirection * size.y + offset, -forwardDirection, Float2(1.0f, 0.0f)));
        vertices.push_back(Vertex(leftDirection * -size.x + upDirection * -size.y + offset, -forwardDirection, Float2(0.0f, 1.0f)));
        vertices.push_back(Vertex(leftDirection * size.x + upDirection * -size.y + offset, -forwardDirection, Float2(1.0f, 1.0f)));

        size_t indexOffset = vertices.size() - 4;
        indices.push_back(indexOffset + 0);
        indices.push_back(indexOffset + 1);
        indices.push_back(indexOffset + 2);
        indices.push_back(indexOffset + 3);
        indices.push_back(indexOffset + 2);
        indices.push_back(indexOffset + 1);
    }
    void CreateCube(bool shouldClear = true)
    {
        if (shouldClear)
        {
            vertices.clear();
            indices.clear();
        }

        CreatePlane(Float2(0.5f, 0.5f), Float3(0.0f, 0.0f, -0.5f), false, Float3(1.0f, 0.0f, 0.0f), Float3(0.0f, 1.0f, 0.0f), Float3(0.0f, 0.0f, 1.0f));		// front
        CreatePlane(Float2(0.5f, 0.5f), Float3(0.0f, 0.0f, 0.5f), false, Float3(-1.0f, 0.0f, 0.0f), Float3(0.0f, 1.0f, 0.0f), Float3(0.0f, 0.0f, -1.0f));	// back
        CreatePlane(Float2(0.5f, 0.5f), Float3(0.5f, 0.0f, 0.0f), false, Float3(0.0f, 0.0f, 1.0f), Float3(0.0f, 1.0f, 0.0f), Float3(-1.0f, 0.0f, 0.0f));		// left
        CreatePlane(Float2(0.5f, 0.5f), Float3(-0.5f, 0.0f, 0.0f), false, Float3(0.0f, 0.0f, -1.0f), Float3(0.0f, 1.0f, 0.0f), Float3(1.0f, 0.0f, 0.0f));	// right
        CreatePlane(Float2(0.5f, 0.5f), Float3(0.0f, 0.5f, 0.0f), false, Float3(1.0f, 0.0f, 0.0f), Float3(0.0f, 0.0f, 1.0f), Float3(0.0f, -1.0f, 0.0f));		// up
        CreatePlane(Float2(0.5f, 0.5f), Float3(0.0f, -0.5f, 0.0f), false, Float3(1.0f, 0.0f, 0.0f), Float3(0.0f, 0.0f, -1.0f), Float3(0.0f, 1.0f, 0.0f));	// down
    }
    void SetCullingMode(D3D11_CULL_MODE cullingMode)
    {
        D3D11_RASTERIZER_DESC rasterizerDesc = {};
        rasterizerDesc.FillMode = D3D11_FILL_SOLID;
        rasterizerDesc.CullMode = cullingMode;
        App::GetGraphicsDevice().CreateRasterizerState(&rasterizerDesc, &rasterizerState);
    }
    void Apply()
    {
        if (vertices.size() > 0)
        {
            vertexBuffer.Release();
            D3D11_BUFFER_DESC vertexBufferDesc = {};
            vertexBufferDesc.ByteWidth = sizeof(Vertex) * vertices.size();
            vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
            vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
            D3D11_SUBRESOURCE_DATA vertexSubresourceData = {};
            vertexSubresourceData.pSysMem = vertices.data();
            App::GetGraphicsDevice().CreateBuffer(&vertexBufferDesc, &vertexSubresourceData, &vertexBuffer);
        }

        if (indices.size() > 0)
        {
            indexBuffer.Release();
            D3D11_BUFFER_DESC indexBufferDesc = {};
            indexBufferDesc.ByteWidth = sizeof(int) * indices.size();
            indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
            indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
            D3D11_SUBRESOURCE_DATA indexSubresourceData = {};
            indexSubresourceData.pSysMem = indices.data();
            App::GetGraphicsDevice().CreateBuffer(&indexBufferDesc, &indexSubresourceData, &indexBuffer);
        }

        material.SetBuffer(&constant, sizeof(Constant));
    }
    void Draw()
    {
        if (vertexBuffer == nullptr)
            return;

        material.Attach();

        constant.world =
            DirectX::XMMatrixScaling(scale.x, scale.y, scale.z) *
            DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(angles.z)) *
            DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(angles.y)) *
            DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(angles.x)) *
            DirectX::XMMatrixTranslation(position.x, position.y, position.z);
        constant.lightDirection = DirectX::XMVector3Normalize(DirectX::XMVectorSet(0.25f, -1.0f, 0.5f, 0.0f));
        
        App::GetGraphicsContext().RSSetState(rasterizerState);

        UINT stride = sizeof(Vertex);
        UINT offset = 0;
        App::GetGraphicsContext().IASetVertexBuffers(0, 1, &vertexBuffer.p, &stride, &offset);

        if (indexBuffer == nullptr)
        {
            App::GetGraphicsContext().Draw(vertices.size(), 0);
        }
        else
        {
            App::GetGraphicsContext().IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
            App::GetGraphicsContext().DrawIndexed(indices.size(), 0, 0);
        }
    }

private:
    struct Constant
    {
        DirectX::XMMATRIX world;
        Float3 lightDirection;
    };

    Constant constant;
    ATL::CComPtr<ID3D11Buffer> vertexBuffer = nullptr;
    ATL::CComPtr<ID3D11Buffer> indexBuffer = nullptr;
    ATL::CComPtr<ID3D11RasterizerState> rasterizerState = nullptr;
};