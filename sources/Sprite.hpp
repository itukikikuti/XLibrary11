class Sprite
{
public:
    Float3 position;
    Float3 angles;
    Float3 scale;
    Texture texture;

    Sprite(const wchar_t* const filePath)
    {
        App::Initialize();
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

        Float2 textureSize(texture.GetSize().x, texture.GetSize().y);
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
        position = Float3(0.0f, 0.0f, 0.0f);
        angles = Float3(0.0f, 0.0f, 0.0f);
        scale = Float3(1.0f, 1.0f, 1.0f);

        mesh.material = Material(
            "cbuffer Object : register(b0)"
            "{"
            "    matrix _world;"
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
            "    float2 uv : TEXCOORD;"
            "};"
            "VSOutput VS(float3 position : POSITION, float2 uv : TEXCOORD)"
            "{"
            "    VSOutput output = (VSOutput)0;"
            "    output.position = mul(_world, float4(position, 1.0));"
            "    output.position = mul(_view, output.position);"
            "    output.position = mul(_projection, output.position);"
            "    output.uv = uv;"
            "    return output;"
            "}"
            "float4 PS(VSOutput pixel) : SV_TARGET"
            "{"
            "    return max(0, tex.Sample(samp, pixel.uv));"
            "}"
        );
    }
};