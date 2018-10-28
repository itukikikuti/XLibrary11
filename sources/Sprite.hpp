class Sprite
{
public:
    Float3 position;
    Float3 angles;
    Float3 scale;
    Float4 color;
    Material material = Material::GetSpriteMaterial();

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
        _texture.Load(filePath);

        _mesh.SetTexture(&_texture);

        SetPivot(0.0f);
    }
    void Create(const BYTE* const buffer, int width, int height)
    {
        _texture.Create(buffer, width, height);

        _mesh.SetTexture(&_texture);

        SetPivot(0.0f);
    }
    DirectX::XMINT2 GetSize() const
    {
        return _texture.GetSize();
    }
    void SetPivot(Float2 pivot)
    {
        Float2 textureSize((float)_texture.GetSize().x, (float)_texture.GetSize().y);
        Float2 offset = textureSize / 2.0f * -pivot;

        _mesh.CreatePlane(textureSize, Float3(offset.x, offset.y, 0.0f));
    }
    void Draw()
    {
        _cbuffer.GetData() = color;
        _cbuffer.Attach(6);

        _mesh.position = position;
        _mesh.angles = angles;
        _mesh.scale = scale;
        _mesh.material = material;
        _mesh.Draw();
    }

protected:
    Mesh _mesh;
    Texture _texture;
    CBuffer<Float4> _cbuffer;

    void Initialize()
    {
        InitializeApplication();

        position = Float3(0.0f, 0.0f, 0.0f);
        angles = Float3(0.0f, 0.0f, 0.0f);
        scale = Float3(1.0f, 1.0f, 1.0f);
        color = Float4(1.0f, 1.0f, 1.0f, 1.0f);

        _mesh.SetCullingMode(D3D11_CULL_NONE);
    }
};