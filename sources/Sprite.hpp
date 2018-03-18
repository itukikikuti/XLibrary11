class Sprite
{
public:
    Float3 position;
    Float3 angles;
    Float3 scale;
    Texture texture;

    Sprite()
    {
        Initialize();
    }
    Sprite(const wchar_t* const filePath)
    {
        Initialize();
        Load(filePath);
    }
    ~Sprite()
    {
    }
    void Load(const wchar_t* const filePath)
    {
        texture.Load(filePath);

        mesh.material.SetTexture(0, &texture);

        Float2 textureSize(static_cast<float>(texture.GetSize().x), static_cast<float>(texture.GetSize().y));
        mesh.CreatePlane(textureSize / 2.0f);
        
        mesh.Apply();
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
    
    void Initialize()
    {
        App::Initialize();

        position = Float3(0.0f, 0.0f, 0.0f);
        angles = Float3(0.0f, 0.0f, 0.0f);
        scale = Float3(1.0f, 1.0f, 1.0f);

        mesh.material = Material(
            "cbuffer Object : register(b0)"
            "{"
            "    matrix world;"
            "};"
            "cbuffer Camera : register(b1)"
            "{"
            "    matrix view;"
            "    matrix projection;"
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
            "    return texture0.Sample(sampler0, pixel.uv);"
            "}"
        );
    }
};