class Material
{
public:
    Material()
    {
        App::Initialize();
        char* source =
            "cbuffer Object : register(b0)"
            "{"
            "    matrix _world;"
            "};"
            "cbuffer Camera : register(b1)"
            "{"
            "    matrix _view;"
            "    matrix _projection;"
            "};"
            "float4 VS(float4 vertex : POSITION) : SV_POSITION"
            "{"
            "    float4 output = vertex;"
            "    output = mul(_world, output);"
            "    output = mul(_view, output);"
            "    output = mul(_projection, output);"
            "    return output;"
            "}"
            "float4 PS(float4 position : SV_POSITION) : SV_TARGET"
            "{"
            "    return float4(1, 0, 1, 1);"
            "}";

        Initialize();
        Create(source);
    }
    Material(char* source)
    {
        App::Initialize();
        Initialize();
        Create(source);
    }
    Material(const wchar_t* const filePath)
    {
        App::Initialize();
        Initialize();
        Load(filePath);
    }
    ~Material()
    {
    }
    void Load(const wchar_t* const filePath)
    {
        std::ifstream sourceFile(filePath);
        std::istreambuf_iterator<char> iterator(sourceFile);
        std::istreambuf_iterator<char> last;
        std::string source(iterator, last);
        sourceFile.close();

        Create(source.c_str());
    }
    void SetCBuffer(void* cbuffer, size_t size)
    {
        this->cbuffer = cbuffer;

        constantBuffer.Release();
        D3D11_BUFFER_DESC constantBufferDesc = {};
        constantBufferDesc.ByteWidth = static_cast<UINT>(size);
        constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
        constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        constantBufferDesc.CPUAccessFlags = 0;
        App::GetGraphicsDevice().CreateBuffer(&constantBufferDesc, nullptr, &constantBuffer);
    }
    void SetTexture(int slot, Texture* texture)
    {
        textures[slot] = texture;
    }
    void Attach()
    {
        App::GetGraphicsContext().VSSetShader(vertexShader, nullptr, 0);
        App::GetGraphicsContext().PSSetShader(pixelShader, nullptr, 0);
        App::GetGraphicsContext().IASetInputLayout(inputLayout);

        if (cbuffer != nullptr)
        {
            App::GetGraphicsContext().UpdateSubresource(constantBuffer, 0, nullptr, cbuffer, 0, 0);
            App::GetGraphicsContext().VSSetConstantBuffers(0, 1, &constantBuffer.p);
            App::GetGraphicsContext().HSSetConstantBuffers(0, 1, &constantBuffer.p);
            App::GetGraphicsContext().DSSetConstantBuffers(0, 1, &constantBuffer.p);
            App::GetGraphicsContext().GSSetConstantBuffers(0, 1, &constantBuffer.p);
            App::GetGraphicsContext().PSSetConstantBuffers(0, 1, &constantBuffer.p);
        }

        int i = 0;
        for (Texture* texture : textures)
        {
            if (texture != nullptr)
            {
                texture->Attach(i);
            }
            i++;
        }
    }

private:
    void* cbuffer = nullptr;
    Texture* textures[10];
    ATL::CComPtr<ID3D11VertexShader> vertexShader = nullptr;
    ATL::CComPtr<ID3D11PixelShader> pixelShader = nullptr;
    ATL::CComPtr<ID3D11InputLayout> inputLayout = nullptr;
    ATL::CComPtr<ID3D11Buffer> constantBuffer = nullptr;

    void Initialize()
    {
        for (int i = 0; i < 10; i++) {
            textures[i] = nullptr;
        }
    }
    void Create(const char* source)
    {
        vertexShader.Release();
        ATL::CComPtr<ID3DBlob> vertexShaderBlob = nullptr;
        CompileShader(source, "VS", "vs_5_0", &vertexShaderBlob);
        App::GetGraphicsDevice().CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), nullptr, &vertexShader);

        pixelShader.Release();
        ATL::CComPtr<ID3DBlob> pixelShaderBlob = nullptr;
        CompileShader(source, "PS", "ps_5_0", &pixelShaderBlob);
        App::GetGraphicsDevice().CreatePixelShader(pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize(), nullptr, &pixelShader);

        inputLayout.Release();
        std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDesc;
        inputElementDesc.push_back({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 });
        inputElementDesc.push_back({ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 });
        inputElementDesc.push_back({ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 });

        App::GetGraphicsDevice().CreateInputLayout(&inputElementDesc[0], static_cast<UINT>(inputElementDesc.size()), vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), &inputLayout);
    }
    static void CompileShader(const char* source, const char* entryPoint, const char* shaderModel, ID3DBlob** out)
    {
        DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(_DEBUG)
        shaderFlags |= D3DCOMPILE_DEBUG;
#endif

        ATL::CComPtr<ID3DBlob> errorBlob = nullptr;
        D3DCompile(source, strlen(source), nullptr, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint, shaderModel, shaderFlags, 0, out, &errorBlob);

        if (errorBlob != nullptr)
        {
            OutputDebugStringA((char*)errorBlob->GetBufferPointer());
            MessageBoxA(App::GetWindowHandle(), (char*)errorBlob->GetBufferPointer(), "Shader Error", MB_OK);
        }
    }
};