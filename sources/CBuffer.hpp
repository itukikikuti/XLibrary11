template <class T>
class CBuffer
{
public:
    CBuffer()
    {
        data = std::make_unique<T>();

        buffer.Reset();
        D3D11_BUFFER_DESC constantBufferDesc = {};
        constantBufferDesc.ByteWidth = sizeof(T);
        constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
        constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        HRESULT result = Graphics::GetDevice3D().CreateBuffer(&constantBufferDesc, nullptr, buffer.GetAddressOf());

        if (buffer == nullptr)
            Utility::Alert(result);
    }
    ~CBuffer()
    {
    }
    T& Get()
    {
        return *data.get();
    }
    void Attach(int slot)
    {
        Graphics::GetContext3D().UpdateSubresource(buffer.Get(), 0, nullptr, data.get(), 0, 0);
        Graphics::GetContext3D().VSSetConstantBuffers(slot, 1, buffer.GetAddressOf());
        Graphics::GetContext3D().PSSetConstantBuffers(slot, 1, buffer.GetAddressOf());
    }

private:
    ComPtr<ID3D11Buffer> buffer = nullptr;
    std::unique_ptr<T> data;
};