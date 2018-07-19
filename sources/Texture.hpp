class Texture
{
public:
    Texture()
    {
        InitializeApplication();
    }
    Texture(const wchar_t* const filePath)
    {
        InitializeApplication();
        Load(filePath);
    }
    Texture(const BYTE* const buffer, int width, int height)
    {
        InitializeApplication();
        Create(buffer, width, height);
    }
    ~Texture()
    {
    }
    void Load(const wchar_t* const filePath)
    {
        ComPtr<IWICBitmapDecoder> decoder = nullptr;

        HRESULT result = Graphics::GetTextureFactory().CreateDecoderFromFilename(filePath, 0, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &decoder);

        if (decoder == nullptr)
            Utility::Alert(result);

        ComPtr<IWICBitmapFrameDecode> frame = nullptr;
        decoder->GetFrame(0, &frame);
        UINT width, height;
        frame->GetSize(&width, &height);

        WICPixelFormatGUID pixelFormat;
        frame->GetPixelFormat(&pixelFormat);
        std::unique_ptr<BYTE[]> buffer(new BYTE[width * height * 4]);

        if (pixelFormat != GUID_WICPixelFormat32bppBGRA)
        {
            ComPtr<IWICFormatConverter> formatConverter = nullptr;
            Graphics::GetTextureFactory().CreateFormatConverter(&formatConverter);

            formatConverter->Initialize(frame.Get(), GUID_WICPixelFormat32bppBGRA, WICBitmapDitherTypeErrorDiffusion, 0, 0, WICBitmapPaletteTypeCustom);

            formatConverter->CopyPixels(0, width * 4, width * height * 4, buffer.get());
        }
        else
        {
            frame->CopyPixels(0, width * 4, width * height * 4, buffer.get());
        }

        Create(buffer.get(), width, height);
    }
    void Create(const BYTE* const buffer, int width, int height)
    {
        _size = DirectX::XMINT2(width, height);

        _texture.Reset();
        D3D11_TEXTURE2D_DESC textureDesc = {};
        textureDesc.Width = width;
        textureDesc.Height = height;
        textureDesc.MipLevels = 1;
        textureDesc.ArraySize = 1;
        textureDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        textureDesc.SampleDesc.Count = 1;
        textureDesc.SampleDesc.Quality = 0;
        textureDesc.Usage = D3D11_USAGE_DEFAULT;
        textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
        textureDesc.CPUAccessFlags = 0;
        textureDesc.MiscFlags = 0;

        D3D11_SUBRESOURCE_DATA textureSubresourceData = {};
        textureSubresourceData.pSysMem = buffer;
        textureSubresourceData.SysMemPitch = width * 4;
        textureSubresourceData.SysMemSlicePitch = width * height * 4;
        Graphics::GetDevice3D().CreateTexture2D(&textureDesc, &textureSubresourceData, _texture.GetAddressOf());

        _shaderResourceView.Reset();
        D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc = {};
        shaderResourceViewDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        shaderResourceViewDesc.Texture2D.MipLevels = 1;
        Graphics::GetDevice3D().CreateShaderResourceView(_texture.Get(), &shaderResourceViewDesc, _shaderResourceView.GetAddressOf());

        _samplerState.Reset();
        D3D11_SAMPLER_DESC samplerDesc = {};
        samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
        samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.MipLODBias = 0.0f;
        samplerDesc.MaxAnisotropy = 1;
        samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
        samplerDesc.BorderColor[0] = 0.0f;
        samplerDesc.BorderColor[1] = 0.0f;
        samplerDesc.BorderColor[2] = 0.0f;
        samplerDesc.BorderColor[3] = 0.0f;
        samplerDesc.MinLOD = 0.0f;
        samplerDesc.MaxLOD = std::numeric_limits<float>::max();
        Graphics::GetDevice3D().CreateSamplerState(&samplerDesc, _samplerState.GetAddressOf());
    }
    DirectX::XMINT2 GetSize() const
    {
        return _size;
    }
    void Attach(int slot)
    {
        if (_texture == nullptr)
            return;

        Graphics::GetContext3D().PSSetShaderResources(slot, 1, _shaderResourceView.GetAddressOf());
        Graphics::GetContext3D().PSSetSamplers(slot, 1, _samplerState.GetAddressOf());
    }
    ID3D11Texture2D& GetInterface()
    {
        return *_texture.Get();
    }

private:
    DirectX::XMINT2 _size;
    ComPtr<ID3D11Texture2D> _texture = nullptr;
    ComPtr<ID3D11ShaderResourceView> _shaderResourceView = nullptr;
    ComPtr<ID3D11SamplerState> _samplerState = nullptr;
};