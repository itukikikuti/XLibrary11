class Material
{
public:
    Material()
    {
        InitializeApplication();
    }
    Material(const wchar_t* const filePath)
    {
        InitializeApplication();
        Load(filePath);
    }
    Material(const std::string& source)
    {
        InitializeApplication();
        Create(source);
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

        Create(source);
    }
    void Create(const std::string& source)
    {
        _vertexShader.Reset();
        ComPtr<ID3DBlob> vertexShaderBlob = nullptr;
        CompileShader(source, "VS", "vs_5_0", vertexShaderBlob.GetAddressOf());
        Graphics::GetDevice3D().CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), nullptr, _vertexShader.GetAddressOf());

        _pixelShader.Reset();
        ComPtr<ID3DBlob> pixelShaderBlob = nullptr;
        CompileShader(source, "PS", "ps_5_0", pixelShaderBlob.GetAddressOf());
        Graphics::GetDevice3D().CreatePixelShader(pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize(), nullptr, _pixelShader.GetAddressOf());

        _inputLayout.Reset();
        std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDesc;
        inputElementDesc.push_back({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 });
        inputElementDesc.push_back({ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 });
        inputElementDesc.push_back({ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 });
        inputElementDesc.push_back({ "BLENDINDICES", 0, DXGI_FORMAT_R32G32B32A32_UINT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 });
        inputElementDesc.push_back({ "BLENDINDICES", 1, DXGI_FORMAT_R32G32B32A32_UINT, 0, 48, D3D11_INPUT_PER_VERTEX_DATA, 0 });
        inputElementDesc.push_back({ "BLENDWEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 64, D3D11_INPUT_PER_VERTEX_DATA, 0 });
        inputElementDesc.push_back({ "BLENDWEIGHT", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 80, D3D11_INPUT_PER_VERTEX_DATA, 0 });

        Graphics::GetDevice3D().CreateInputLayout(inputElementDesc.data(), (UINT)inputElementDesc.size(), vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), _inputLayout.GetAddressOf());
    }
    void Attach()
    {
        if (_vertexShader != nullptr)
            Graphics::GetContext3D().VSSetShader(_vertexShader.Get(), nullptr, 0);

        if (_pixelShader != nullptr)
            Graphics::GetContext3D().PSSetShader(_pixelShader.Get(), nullptr, 0);

        if (_inputLayout != nullptr)
            Graphics::GetContext3D().IASetInputLayout(_inputLayout.Get());
    }
    static Material GetDiffuseMaterial()
    {
        static std::unique_ptr<Material> diffuseMaterial;

        if (diffuseMaterial == nullptr)
        {
            diffuseMaterial.reset(new Material(
                "struct Vertex"
                "{"
                "    float4 position : POSITION;"
                "    float3 normal : NORMAL;"
                "    float2 uv : TEXCOORD;"
                "};"
                "struct Pixel"
                "{"
                "    float4 position : SV_POSITION;"
                "    float3 normal : NORMAL;"
                "    float2 uv : TEXCOORD0;"
                "    float3 worldPosition : TEXCOORD1;"
                "};"
                "struct Light"
                "{"
                "    int type;"
                "    float3 position;"
                "    float3 direction;"
                "    float range;"
                "    float4 color;"
                "};"
                "cbuffer Camera : register(b0)"
                "{"
                "    matrix view;"
                "    matrix projection;"
                "};"
                "cbuffer Light : register(b1)"
                "{"
                "    Light lights[100];"
                "};"
                "cbuffer Object : register(b5)"
                "{"
                "    matrix world;"
                "};"
                "Texture2D texture0 : register(t0);"
                "SamplerState sampler0 : register(s0);"
                "Pixel VS(Vertex vertex)"
                "{"
                "    Pixel output;"
                "    output.position = mul(vertex.position, world);"
                "    output.position = mul(output.position, view);"
                "    output.position = mul(output.position, projection);"
                "    output.normal = mul(vertex.normal, (float3x3)world);"
                "    output.uv = vertex.uv;"
                "    output.worldPosition = mul(vertex.position, world).xyz;"
                "    return output;"
                "}"
                "float4 PS(Pixel pixel) : SV_TARGET"
                "{"
                "    float3 diffuseColor = texture0.Sample(sampler0, pixel.uv).rgb;"
                "    float3 normal = normalize(pixel.normal);"
                "    float3 lightColor = float3(0.0, 0.0, 0.0);"
                "    for (int i = 0; i < 100; i++)"
                "    {"
                "        if (lights[i].type == 0)"
                "        {"
                "            float shade = max(0, dot(-lights[i].direction, normal));"
                "            lightColor += lights[i].color.xyz * shade;"
                "        }"
                "        if (lights[i].type == 1)"
                "        {"
                "            float3 lightDirection = normalize(lights[i].position.xyz - pixel.worldPosition);"
                "            float shade = max(0, dot(normal, lightDirection));"
                "            float attenuation = max(0, (lights[i].range - length(lights[i].position.xyz - pixel.worldPosition)) / lights[i].range);"
                "            lightColor += lights[i].color.xyz * shade * attenuation;"
                "        }"
                "    }"
                "    float3 ambientColor = float3(1.0, 1.0, 1.0) * 0.1;"
                "    return float4(diffuseColor * (lightColor + ambientColor), 1);"
                "}"
            ));
        }

        return *diffuseMaterial.get();
    }
    static Material GetSpriteMaterial()
    {
        static std::unique_ptr<Material> spriteMaterial;

        if (spriteMaterial == nullptr)
        {
            spriteMaterial.reset(new Material(
                "cbuffer Camera : register(b0)"
                "{"
                "    matrix view;"
                "    matrix projection;"
                "};"
                "cbuffer Object : register(b5)"
                "{"
                "    matrix world;"
                "};"
                "cbuffer Sprite : register(b6)"
                "{"
                "    float4 color;"
                "};"
                "Texture2D texture0 : register(t0);"
                "SamplerState sampler0 : register(s0);"
                "struct Vertex"
                "{"
                "    float4 position : POSITION;"
                "    float2 uv : TEXCOORD;"
                "};"
                "struct Pixel"
                "{"
                "    float4 position : SV_POSITION;"
                "    float2 uv : TEXCOORD;"
                "};"
                "Pixel VS(Vertex vertex)"
                "{"
                "    Pixel output;"
                "    output.position = mul(vertex.position, world);"
                "    output.position = mul(output.position, view);"
                "    output.position = mul(output.position, projection);"
                "    output.uv = vertex.uv;"
                "    return output;"
                "}"
                "float4 PS(Pixel pixel) : SV_TARGET"
                "{"
                "    float4 textureColor = texture0.Sample(sampler0, pixel.uv);"
                "    if (textureColor.a <= 0)"
                "        discard;"
                "    return textureColor * color;"
                "}"
            ));
        }

        return *spriteMaterial.get();
    }

private:
    ComPtr<ID3D11VertexShader> _vertexShader = nullptr;
    ComPtr<ID3D11PixelShader> _pixelShader = nullptr;
    ComPtr<ID3D11InputLayout> _inputLayout = nullptr;

    static void CompileShader(const std::string& source, const char* const entryPoint, const char* const shaderModel, ID3DBlob** out)
    {
        UINT shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(_DEBUG)
        shaderFlags |= D3DCOMPILE_DEBUG;
#endif

        ComPtr<ID3DBlob> errorBlob = nullptr;
        D3DCompile(source.c_str(), source.length(), nullptr, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint, shaderModel, shaderFlags, 0, out, errorBlob.GetAddressOf());

        if (errorBlob != nullptr)
        {
            OutputDebugStringA((char*)errorBlob->GetBufferPointer());
            MessageBoxA(Window::GetHandle(), (char*)errorBlob->GetBufferPointer(), "Shader error", MB_ICONERROR | MB_OK);
            std::exit(EXIT_FAILURE);
        }
    }
};