class Mesh
{
public:
    Float3 position;
    Float3 angles;
    Float3 scale;
    std::vector<Vertex> vertices;
    std::vector<UINT> indices;
    Shader material = Shader::GetDiffuseShader();

    Mesh()
    {
        InitializeApplication();
		
        position = Float3(0.0f, 0.0f, 0.0f);
        angles = Float3(0.0f, 0.0f, 0.0f);
        scale = Float3(1.0f, 1.0f, 1.0f);

        SetCullingMode(D3D11_CULL_BACK);

        CreateCube();
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

        size /= 2.0f;

        leftDirection = DirectX::XMVector3Normalize(leftDirection);
        upDirection = DirectX::XMVector3Normalize(upDirection);
        forwardDirection = DirectX::XMVector3Normalize(forwardDirection);

        vertices.push_back(Vertex(leftDirection * -size.x + upDirection * size.y + offset, -forwardDirection, Float2(0.0f, 0.0f)));
        vertices.push_back(Vertex(leftDirection * size.x + upDirection * size.y + offset, -forwardDirection, Float2(1.0f, 0.0f)));
        vertices.push_back(Vertex(leftDirection * -size.x + upDirection * -size.y + offset, -forwardDirection, Float2(0.0f, 1.0f)));
        vertices.push_back(Vertex(leftDirection * size.x + upDirection * -size.y + offset, -forwardDirection, Float2(1.0f, 1.0f)));

        int indexOffset = (int)vertices.size() - 4;
        indices.push_back(indexOffset + 0);
        indices.push_back(indexOffset + 1);
        indices.push_back(indexOffset + 2);
        indices.push_back(indexOffset + 3);
        indices.push_back(indexOffset + 2);
        indices.push_back(indexOffset + 1);

        if (shouldClear)
            Apply();
    }
    void CreateCube(Float3 size = Float3(1.0f, 1.0f, 1.0f), bool shouldClear = true)
    {
        if (shouldClear)
        {
            vertices.clear();
            indices.clear();
        }

        CreatePlane(Float2(size.x, size.y), Float3(0.0f, 0.0f, -size.z / 2.0f), false, Float3(1.0f, 0.0f, 0.0f), Float3(0.0f, 1.0f, 0.0f), Float3(0.0f, 0.0f, 1.0f));	// front
        CreatePlane(Float2(size.x, size.y), Float3(0.0f, 0.0f, size.z / 2.0f), false, Float3(-1.0f, 0.0f, 0.0f), Float3(0.0f, 1.0f, 0.0f), Float3(0.0f, 0.0f, -1.0f));	// back
        CreatePlane(Float2(size.z, size.y), Float3(size.x / 2.0f, 0.0f, 0.0f), false, Float3(0.0f, 0.0f, 1.0f), Float3(0.0f, 1.0f, 0.0f), Float3(-1.0f, 0.0f, 0.0f));	// left
        CreatePlane(Float2(size.z, size.y), Float3(-size.x / 2.0f, 0.0f, 0.0f), false, Float3(0.0f, 0.0f, -1.0f), Float3(0.0f, 1.0f, 0.0f), Float3(1.0f, 0.0f, 0.0f));	// right
        CreatePlane(Float2(size.x, size.z), Float3(0.0f, size.y / 2.0f, 0.0f), false, Float3(1.0f, 0.0f, 0.0f), Float3(0.0f, 0.0f, 1.0f), Float3(0.0f, -1.0f, 0.0f));	// up
        CreatePlane(Float2(size.x, size.z), Float3(0.0f, -size.y / 2.0f, 0.0f), false, Float3(1.0f, 0.0f, 0.0f), Float3(0.0f, 0.0f, -1.0f), Float3(0.0f, 1.0f, 0.0f));	// down

        if (shouldClear)
            Apply();
    }
    void CreateSphere(float diameter = 1.0f, int tessellation = 10, bool shouldClear = true)
    {
        if (shouldClear)
        {
            vertices.clear();
            indices.clear();
        }

        int verticalSegments = tessellation;
        int horizontalSegments = tessellation * 2;

        float radius = diameter / 2;

        for (int i = 0; i <= verticalSegments; i++)
        {
            float v = float(i) / verticalSegments;

            float latitude = (i * XM_PI / verticalSegments) - XM_PIDIV2;
            float dy, dxz;

            XMScalarSinCos(&dy, &dxz, latitude);

            for (int j = 0; j <= horizontalSegments; j++)
            {
                float u = float(j) / horizontalSegments;

                float longitude = j * XM_2PI / horizontalSegments + XM_PI;
                float dx, dz;

                XMScalarSinCos(&dx, &dz, longitude);

                dx *= dxz;
                dz *= dxz;

                Float3 normal(dx, dy, dz);
                Float2 uv(u, v);

                vertices.push_back(Vertex(XMVectorScale(-normal, radius), -normal, uv));
            }
        }

        int stride = horizontalSegments + 1;

        for (int i = 0; i < verticalSegments; i++)
        {
            for (int j = 0; j <= horizontalSegments; j++)
            {
                int nextI = i + 1;
                int nextJ = (j + 1) % stride;

                indices.push_back(i * stride + j);
                indices.push_back(nextI * stride + j);
                indices.push_back(i * stride + nextJ);

                indices.push_back(i * stride + nextJ);
                indices.push_back(nextI * stride + j);
                indices.push_back(nextI * stride + nextJ);
            }
        }

        if (shouldClear)
            Apply();
    }
    void SetTexture(Texture* const texture)
    {
        _texture = texture;
    }
    void SetCullingMode(D3D11_CULL_MODE cullingMode)
    {
        D3D11_RASTERIZER_DESC rasterizerDesc = {};
        rasterizerDesc.FillMode = D3D11_FILL_SOLID;
        rasterizerDesc.CullMode = cullingMode;
        _rasterizerState.Reset();
        Graphics::GetDevice3D().CreateRasterizerState(&rasterizerDesc, _rasterizerState.GetAddressOf());
    }
    void Apply()
    {
        _vertexBuffer.Reset();
        if (vertices.size() > 0)
        {
            D3D11_BUFFER_DESC vertexBufferDesc = {};
            vertexBufferDesc.ByteWidth = sizeof(Vertex) * UINT(vertices.size());
            vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
            vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
            D3D11_SUBRESOURCE_DATA vertexSubresourceData = {};
            vertexSubresourceData.pSysMem = vertices.data();
            Graphics::GetDevice3D().CreateBuffer(&vertexBufferDesc, &vertexSubresourceData, _vertexBuffer.GetAddressOf());
        }

        _indexBuffer.Reset();
        if (indices.size() > 0)
        {
            D3D11_BUFFER_DESC indexBufferDesc = {};
            indexBufferDesc.ByteWidth = sizeof(UINT) * UINT(indices.size());
            indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
            indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
            D3D11_SUBRESOURCE_DATA indexSubresourceData = {};
            indexSubresourceData.pSysMem = indices.data();
            Graphics::GetDevice3D().CreateBuffer(&indexBufferDesc, &indexSubresourceData, _indexBuffer.GetAddressOf());
        }
    }
    void Draw()
    {
        if (_vertexBuffer == nullptr)
            return;

        if (_texture != nullptr)
            _texture->Attach(0);

        DirectX::XMMATRIX world = DirectX::XMMatrixTranspose(
            DirectX::XMMatrixScaling(scale.x, scale.y, scale.z) *
            DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(angles.x)) *
            DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(angles.z)) *
            DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(angles.y)) *
            DirectX::XMMatrixTranslation(position.x, position.y, position.z)
        );
        DirectX::XMStoreFloat4x4(&_cbuffer.Get().world, world);

        _cbuffer.Attach(5);

        material.Attach();

        Graphics::GetContext3D().RSSetState(_rasterizerState.Get());

        UINT stride = sizeof(Vertex);
        UINT offset = 0;
        Graphics::GetContext3D().IASetVertexBuffers(0, 1, _vertexBuffer.GetAddressOf(), &stride, &offset);

        if (_indexBuffer == nullptr)
        {
            Graphics::GetContext3D().Draw((UINT)vertices.size(), 0);
        }
        else
        {
            Graphics::GetContext3D().IASetIndexBuffer(_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
            Graphics::GetContext3D().DrawIndexed((UINT)indices.size(), 0, 0);
        }
    }

private:
    struct Constant
    {
        DirectX::XMFLOAT4X4 world;
    };

    Texture* _texture;
    CBuffer<Constant> _cbuffer;
    ComPtr<ID3D11Buffer> _vertexBuffer = nullptr;
    ComPtr<ID3D11Buffer> _indexBuffer = nullptr;
    ComPtr<ID3D11RasterizerState> _rasterizerState = nullptr;
};