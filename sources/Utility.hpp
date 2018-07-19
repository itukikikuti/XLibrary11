struct Float2 : public DirectX::XMFLOAT2
{
    Float2() : DirectX::XMFLOAT2()
    {
    }
    Float2(float x, float y) : DirectX::XMFLOAT2(x, y)
    {
    }
    Float2(float value) : DirectX::XMFLOAT2(value, value)
    {
    }
    Float2(const DirectX::XMVECTOR& vector) : DirectX::XMFLOAT2()
    {
        DirectX::XMStoreFloat2(this, vector);
    }
    Float2& operator=(const DirectX::XMVECTOR& vector)
    {
        DirectX::XMStoreFloat2(this, vector);
        return *this;
    }
    operator DirectX::XMVECTOR() const
    {
        return DirectX::XMLoadFloat2(this);
    }
    Float2 operator+() const
    {
        return Float2(x, y);
    }
    Float2 operator-() const
    {
        return Float2(-x, -y);
    }
    Float2& operator=(const Float2& value)
    {
        x = value.x;
        y = value.y;
        return *this;
    }
    Float2& operator=(const float& value)
    {
        x = value;
        y = value;
        return *this;
    }
    Float2& operator+=(const Float2& value)
    {
        x += value.x;
        y += value.y;
        return *this;
    }
    Float2& operator+=(const float& value)
    {
        x += value;
        y += value;
        return *this;
    }
    Float2& operator-=(const Float2& value)
    {
        x -= value.x;
        y -= value.y;
        return *this;
    }
    Float2& operator-=(const float& value)
    {
        x -= value;
        y -= value;
        return *this;
    }
    Float2& operator*=(const Float2& value)
    {
        x *= value.x;
        y *= value.y;
        return *this;
    }
    Float2& operator*=(const float& value)
    {
        x *= value;
        y *= value;
        return *this;
    }
    Float2& operator/=(const Float2& value)
    {
        x /= value.x;
        y /= value.y;
        return *this;
    }
    Float2& operator/=(const float& value)
    {
        x /= value;
        y /= value;
        return *this;
    }
};

inline Float2 operator+(const Float2& t1, const Float2& t2)
{
    return Float2(t1) += t2;
}
inline Float2 operator+(const Float2& t1, const float& t2)
{
    return Float2(t1) += t2;
}
inline Float2 operator-(const Float2& t1, const Float2& t2)
{
    return Float2(t1) -= t2;
}
inline Float2 operator-(const Float2& t1, const float& t2)
{
    return Float2(t1) -= t2;
}
inline Float2 operator*(const Float2& t1, const Float2& t2)
{
    return Float2(t1) *= t2;
}
inline Float2 operator*(const Float2& t1, const float& t2)
{
    return Float2(t1) *= t2;
}
inline Float2 operator/(const Float2& t1, const Float2& t2)
{
    return Float2(t1) /= t2;
}
inline Float2 operator/(const Float2& t1, const float& t2)
{
    return Float2(t1) /= t2;
}

struct Float3 : public DirectX::XMFLOAT3
{
    Float3() : DirectX::XMFLOAT3()
    {
    }
    Float3(float x, float y, float z) : DirectX::XMFLOAT3(x, y, z)
    {
    }
    Float3(float value) : DirectX::XMFLOAT3(value, value, value)
    {
    }
    Float3(const DirectX::XMVECTOR& vector) : DirectX::XMFLOAT3()
    {
        DirectX::XMStoreFloat3(this, vector);
    }
    Float3& operator=(const DirectX::XMVECTOR& vector)
    {
        DirectX::XMStoreFloat3(this, vector);
        return *this;
    }
    operator DirectX::XMVECTOR() const
    {
        return DirectX::XMLoadFloat3(this);
    }
    Float3 operator+() const
    {
        return Float3(x, y, z);
    }
    Float3 operator-() const
    {
        return Float3(-x, -y, -z);
    }
    Float3& operator=(const Float3& value)
    {
        x = value.x;
        y = value.y;
        z = value.z;
        return *this;
    }
    Float3& operator=(const float& value)
    {
        x = value;
        y = value;
        z = value;
        return *this;
    }
    Float3& operator+=(const Float3& value)
    {
        x += value.x;
        y += value.y;
        z += value.z;
        return *this;
    }
    Float3& operator+=(const float& value)
    {
        x += value;
        y += value;
        z += value;
        return *this;
    }
    Float3& operator-=(const Float3& value)
    {
        x -= value.x;
        y -= value.y;
        z -= value.z;
        return *this;
    }
    Float3& operator-=(const float& value)
    {
        x -= value;
        y -= value;
        z -= value;
        return *this;
    }
    Float3& operator*=(const Float3& value)
    {
        x *= value.x;
        y *= value.y;
        z *= value.z;
        return *this;
    }
    Float3& operator*=(const float& value)
    {
        x *= value;
        y *= value;
        z *= value;
        return *this;
    }
    Float3& operator/=(const Float3& value)
    {
        x /= value.x;
        y /= value.y;
        z /= value.z;
        return *this;
    }
    Float3& operator/=(const float& value)
    {
        x /= value;
        y /= value;
        z /= value;
        return *this;
    }
};

inline Float3 operator+(const Float3& t1, const Float3& t2)
{
    return Float3(t1) += t2;
}
inline Float3 operator+(const Float3& t1, const float& t2)
{
    return Float3(t1) += t2;
}
inline Float3 operator-(const Float3& t1, const Float3& t2)
{
    return Float3(t1) -= t2;
}
inline Float3 operator-(const Float3& t1, const float& t2)
{
    return Float3(t1) -= t2;
}
inline Float3 operator*(const Float3& t1, const Float3& t2)
{
    return Float3(t1) *= t2;
}
inline Float3 operator*(const Float3& t1, const float& t2)
{
    return Float3(t1) *= t2;
}
inline Float3 operator/(const Float3& t1, const Float3& t2)
{
    return Float3(t1) /= t2;
}
inline Float3 operator/(const Float3& t1, const float& t2)
{
    return Float3(t1) /= t2;
}

struct Float4 : public DirectX::XMFLOAT4
{
    Float4() : DirectX::XMFLOAT4()
    {
    }
    Float4(float x, float y, float z, float w) : DirectX::XMFLOAT4(x, y, z, w)
    {
    }
    Float4(float value) : DirectX::XMFLOAT4(value, value, value, value)
    {
    }
    Float4(const DirectX::XMVECTOR& vector) : DirectX::XMFLOAT4()
    {
        DirectX::XMStoreFloat4(this, vector);
    }
    Float4& operator=(const DirectX::XMVECTOR& vector)
    {
        DirectX::XMStoreFloat4(this, vector);
        return *this;
    }
    operator DirectX::XMVECTOR() const
    {
        return DirectX::XMLoadFloat4(this);
    }
    Float4 operator+() const
    {
        return Float4(x, y, z, w);
    }
    Float4 operator-() const
    {
        return Float4(-x, -y, -z, -w);
    }
    Float4& operator=(const Float4& value)
    {
        x = value.x;
        y = value.y;
        z = value.z;
        w = value.w;
        return *this;
    }
    Float4& operator=(const float& value)
    {
        x = value;
        y = value;
        z = value;
        w = value;
        return *this;
    }
    Float4& operator+=(const Float4& value)
    {
        x += value.x;
        y += value.y;
        z += value.z;
        w += value.w;
        return *this;
    }
    Float4& operator+=(const float& value)
    {
        x += value;
        y += value;
        z += value;
        w += value;
        return *this;
    }
    Float4& operator-=(const Float4& value)
    {
        x -= value.x;
        y -= value.y;
        z -= value.z;
        w -= value.w;
        return *this;
    }
    Float4& operator-=(const float& value)
    {
        x -= value;
        y -= value;
        z -= value;
        w -= value;
        return *this;
    }
    Float4& operator*=(const Float4& value)
    {
        x *= value.x;
        y *= value.y;
        z *= value.z;
        w *= value.w;
        return *this;
    }
    Float4& operator*=(const float& value)
    {
        x *= value;
        y *= value;
        z *= value;
        w *= value;
        return *this;
    }
    Float4& operator/=(const Float4& value)
    {
        x /= value.x;
        y /= value.y;
        z /= value.z;
        w /= value.w;
        return *this;
    }
    Float4& operator/=(const float& value)
    {
        x /= value;
        y /= value;
        z /= value;
        w /= value;
        return *this;
    }
};

inline Float4 operator+(const Float4& t1, const Float4& t2)
{
    return Float4(t1) += t2;
}
inline Float4 operator+(const Float4& t1, const float& t2)
{
    return Float4(t1) += t2;
}
inline Float4 operator-(const Float4& t1, const Float4& t2)
{
    return Float4(t1) -= t2;
}
inline Float4 operator-(const Float4& t1, const float& t2)
{
    return Float4(t1) -= t2;
}
inline Float4 operator*(const Float4& t1, const Float4& t2)
{
    return Float4(t1) *= t2;
}
inline Float4 operator*(const Float4& t1, const float& t2)
{
    return Float4(t1) *= t2;
}
inline Float4 operator/(const Float4& t1, const Float4& t2)
{
    return Float4(t1) /= t2;
}
inline Float4 operator/(const Float4& t1, const float& t2)
{
    return Float4(t1) /= t2;
}

struct Vertex
{
    Float3 position;
    Float3 normal;
    Float2 uv;
    uint32_t blendIndices[8] = { 999, 999, 999, 999, 999, 999, 999, 999 };
    float blendWeights[8] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

    Vertex()
    {
    }
    Vertex(Float3 position, Float3 normal, Float2 uv)
    {
        this->position = position;
        this->normal = normal;
        this->uv = uv;
    }
};

class Utility
{
public:
    static std::string Format(const char* const format, ...)
    {
        va_list arguments;

        va_start(arguments, format);
        int size = vprintf_s(format, arguments);
        va_end(arguments);

        std::unique_ptr<char[]> buffer(new char[size + 1]);
        va_start(arguments, format);
        vsprintf_s(buffer.get(), size + 1, format, arguments);
        va_end(arguments);

        return std::string(buffer.get());
    }
    static std::wstring WFormat(const wchar_t* const format, ...)
    {
        va_list arguments;

        va_start(arguments, format);
        int size = vwprintf_s(format, arguments);
        va_end(arguments);

        std::unique_ptr<wchar_t[]> buffer(new wchar_t[size + 1]);
        va_start(arguments, format);
        vswprintf_s(buffer.get(), size + 1, format, arguments);
        va_end(arguments);

        return std::wstring(buffer.get());
    }
    static void Alert(DWORD errorCodeValue)
    {
        std::error_code errorCode(errorCodeValue, std::system_category());
        MessageBoxA(nullptr, errorCode.message().c_str(), Utility::Format("Error code 0x%x(%d)", errorCode.value(), errorCode.value()).c_str(), MB_ICONERROR | MB_OK);
#if defined(_DEBUG)
        throw std::system_error(errorCode);
#else
        std::exit(errorCode.value());
#endif
    }
};