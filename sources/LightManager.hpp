class LightManager
{
public:
    struct Constant
    {
        int type;
        Float3 position;
        Float3 direction;
        float range;
        Float4 color;
    };

    static const int limit = 100;

    static void AddLight(Constant* const constant)
    {
        Get().lights.push_back(constant);
    }
    static void RemoveLight(Constant* const constant)
    {
        std::vector<Constant*>& v = Get().lights;
        v.erase(remove(v.begin(), v.end(), constant), v.end());
    }
    static void Update()
    {
        for (size_t i = 0; i < limit; i++)
        {
            if (Get().lights.size() > i)
                Get().constant[i] = *Get().lights[i];
            else
                Get().constant[i].type = -1;
        }

        Graphics::GetContext3D().UpdateSubresource(Get().constantBuffer.Get(), 0, nullptr, Get().constant, 0, 0);
        Graphics::GetContext3D().VSSetConstantBuffers(1, 1, Get().constantBuffer.GetAddressOf());
        Graphics::GetContext3D().HSSetConstantBuffers(1, 1, Get().constantBuffer.GetAddressOf());
        Graphics::GetContext3D().DSSetConstantBuffers(1, 1, Get().constantBuffer.GetAddressOf());
        Graphics::GetContext3D().GSSetConstantBuffers(1, 1, Get().constantBuffer.GetAddressOf());
        Graphics::GetContext3D().PSSetConstantBuffers(1, 1, Get().constantBuffer.GetAddressOf());
    }

private:
    struct Property
    {
        std::vector<Constant*> lights;
        Constant constant[limit];
        ComPtr<ID3D11Buffer> constantBuffer = nullptr;
    };

    static Property& Get()
    {
        static std::unique_ptr<Property> prop;

        if (prop == nullptr)
        {
            prop.reset(new Property());

            D3D11_BUFFER_DESC constantBufferDesc = {};
            constantBufferDesc.ByteWidth = sizeof(Constant) * limit;
            constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
            constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
            Graphics::GetDevice3D().CreateBuffer(&constantBufferDesc, nullptr, Get().constantBuffer.GetAddressOf());
        }

        return *prop;
    }
};