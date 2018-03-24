class Sprite
{
public:
    Float3 position;
    Float3 angles;
    Float3 scale;
    Float4 color;

    Sprite()
    {
        Initialize();
    }
    Sprite(const wchar_t* const filePath)
    {
        Initialize();
        Load(filePath);
    }
    Sprite(const BYTE* const buffer, int width, int height)
    {
        Initialize();
        Create(buffer, width, height);
    }
    ~Sprite()
    {
    }
    void Load(const wchar_t* const filePath)
    {
        texture.Load(filePath);

        mesh.GetMaterial().SetTexture(0, &texture);

        SetPivot(0.0f);
    }
    void Create(const BYTE* const buffer, int width, int height)
    {
        texture.Create(buffer, width, height);

        mesh.GetMaterial().SetTexture(0, &texture);

        SetPivot(0.0f);
    }
    DirectX::XMINT2 GetSize() const
    {
        return texture.GetSize();
    }
    void SetPivot(Float2 pivot)
    {
        Float2 textureSize(static_cast<float>(texture.GetSize().x), static_cast<float>(texture.GetSize().y));
        Float2 offset = textureSize / 2.0f * -pivot;

        mesh.CreatePlane(textureSize / 2.0f, Float3(offset.x, offset.y, 0.0f));
        mesh.Apply();
    }
    Material& GetMaterial()
    {
        return mesh.GetMaterial();
    }
    void Draw()
    {
        mesh.position = position;
        mesh.angles = angles;
        mesh.scale = scale;
        mesh.Draw();
    }

private:
    Mesh mesh;
    Texture texture;

    void Initialize()
    {
        App::Initialize();

        position = Float3(0.0f, 0.0f, 0.0f);
        angles = Float3(0.0f, 0.0f, 0.0f);
        scale = Float3(1.0f, 1.0f, 1.0f);
        color = Float4(1.0f, 1.0f, 1.0f, 1.0f);

        mesh.GetMaterial().Create(
            "cbuffer Camera : register(b0)"
            "{"
            "    matrix view;"
            "    matrix projection;"
            "};"
            "cbuffer Object : register(b1)"
            "{"
            "    matrix world;"
            "};"
            "cbuffer Sprite : register(b2)"
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
        );

        mesh.GetMaterial().SetBuffer(2, &color, sizeof(Float4));
    }
};