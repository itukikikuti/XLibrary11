class Light
{
public:
    enum class Type : int
    {
        Directional,
        Point,
    };

    Type type;
    Float3 position;
    Float3 angles;
    Float3 color;
    float range;
    float intensity;

    Light()
    {
        type = Type::Directional;
        color = Float3(1.0f, 1.0f, 1.0f);
        range = 5.0f;
        intensity = 1.0f;

        LightManager::AddLight(&_constant);
    }
    ~Light()
    {
        LightManager::RemoveLight(&_constant);
    }
    void Update()
    {
        _constant.direction = Float3(
            cosf(XMConvertToRadians(angles.x)) * cosf(XMConvertToRadians(angles.y + 90.0f)),
            sinf(XMConvertToRadians(angles.x)),
            cosf(XMConvertToRadians(angles.x)) * sinf(XMConvertToRadians(angles.y + 90.0f))
        );

        _constant.type = (int)type;
        _constant.position = position;
        _constant.color = color * intensity;
        _constant.range = range;
    }

private:
    LightManager::Constant _constant;
};