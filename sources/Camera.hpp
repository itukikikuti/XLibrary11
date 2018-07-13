class Camera : public Window::Proceedable
{
public:
    Float3 position;
    Float3 angles;
    Float4 color;
    bool clear = true;

    Camera()
    {
        InitializeApplication();

        position = Float3(0.0f, 0.0f, 0.0f);
        angles = Float3(0.0f, 0.0f, 0.0f);
        color = Float4(1.0f, 1.0f, 1.0f, 1.0f);

        SetupOrthographic();

        Create();

        Window::AddProcedure(this);
    }
    ~Camera()
    {
        Window::RemoveProcedure(this);
    }
    void SetupPerspective(float fieldOfView = 60.0f, float nearClip = 0.1f, float farClip = 1000.0f)
    {
        _is3D = true;
        _fieldOfView = fieldOfView;
        _nearClip = nearClip;
        _farClip = farClip;
        float aspectRatio = float(Window::GetSize().x) / Window::GetSize().y;
        _constant.projection = DirectX::XMMatrixTranspose(
            DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(fieldOfView), aspectRatio, nearClip, farClip)
        );
    }
    void SetupOrthographic(float size = (float)Window::GetSize().y, bool isAdjust = true, float nearClip = -std::numeric_limits<float>::max(), float farClip = std::numeric_limits<float>::max())
    {
        _is3D = false;
        _size = size;
        _isAdjust = isAdjust;
        _nearClip = nearClip;
        _farClip = farClip;
        float aspectRatio = float(Window::GetSize().x) / Window::GetSize().y;
        _constant.projection = DirectX::XMMatrixTranspose(
            DirectX::XMMatrixOrthographicLH(size * aspectRatio, size, nearClip, farClip)
        );
    }
    void Update()
    {
        _constant.view = DirectX::XMMatrixTranspose(
            DirectX::XMMatrixInverse(
                nullptr,
                DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(angles.x)) *
                DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(angles.y)) *
                DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(angles.z)) *
                DirectX::XMMatrixTranslation(position.x, position.y, position.z)
            )
        );

        Graphics::GetContext3D().UpdateSubresource(_constantBuffer.Get(), 0, nullptr, &_constant, 0, 0);
        Graphics::GetContext3D().VSSetConstantBuffers(0, 1, _constantBuffer.GetAddressOf());
        Graphics::GetContext3D().HSSetConstantBuffers(0, 1, _constantBuffer.GetAddressOf());
        Graphics::GetContext3D().DSSetConstantBuffers(0, 1, _constantBuffer.GetAddressOf());
        Graphics::GetContext3D().GSSetConstantBuffers(0, 1, _constantBuffer.GetAddressOf());
        Graphics::GetContext3D().PSSetConstantBuffers(0, 1, _constantBuffer.GetAddressOf());

        if (clear)
        {
            float clearColor[4] = { color.x, color.y, color.z, color.w };
            Graphics::GetContext3D().ClearRenderTargetView(_renderTargetView.Get(), clearColor);
        }

        if (_is3D)
        {
            Graphics::GetContext3D().ClearDepthStencilView(_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
            Graphics::GetContext3D().OMSetRenderTargets(1, _renderTargetView.GetAddressOf(), _depthStencilView.Get());
        }
        else
        {
            Graphics::GetContext3D().OMSetRenderTargets(1, _renderTargetView.GetAddressOf(), nullptr);
        }
    }

private:
    struct Constant
    {
        DirectX::XMMATRIX view;
        DirectX::XMMATRIX projection;
    };

    bool _is3D;
    float _fieldOfView;
    float _size;
    bool _isAdjust;
    float _nearClip;
    float _farClip;
    Constant _constant;
    ComPtr<ID3D11RenderTargetView> _renderTargetView = nullptr;
    ComPtr<ID3D11DepthStencilView> _depthStencilView = nullptr;
    ComPtr<ID3D11Texture2D> _renderTexture = nullptr;
    ComPtr<ID3D11Texture2D> _depthTexture = nullptr;
    ComPtr<ID3D11Buffer> _constantBuffer = nullptr;

    void Create()
    {
        _renderTexture.Reset();
        Graphics::GetSwapChain().GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(_renderTexture.GetAddressOf()));
        _renderTargetView.Reset();
        Graphics::GetDevice3D().CreateRenderTargetView(_renderTexture.Get(), nullptr, _renderTargetView.GetAddressOf());

        DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
        Graphics::GetSwapChain().GetDesc(&swapChainDesc);

        _depthTexture.Reset();
        D3D11_TEXTURE2D_DESC textureDesc = {};
        textureDesc.Width = (UINT)Window::GetSize().x;
        textureDesc.Height = (UINT)Window::GetSize().y;
        textureDesc.MipLevels = 1;
        textureDesc.ArraySize = 1;
        textureDesc.Format = DXGI_FORMAT_R32_TYPELESS;
        textureDesc.SampleDesc.Count = swapChainDesc.SampleDesc.Count;
        textureDesc.SampleDesc.Quality = swapChainDesc.SampleDesc.Quality;
        textureDesc.Usage = D3D11_USAGE_DEFAULT;
        textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        textureDesc.CPUAccessFlags = 0;
        textureDesc.MiscFlags = 0;
        Graphics::GetDevice3D().CreateTexture2D(&textureDesc, nullptr, _depthTexture.GetAddressOf());

        _depthStencilView.Reset();
        D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc = {};
        depthStencilViewDesc.Format = DXGI_FORMAT_D32_FLOAT;
        if (swapChainDesc.SampleDesc.Count == 0)
        {
            depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
            depthStencilViewDesc.Texture2D.MipSlice = 0;
        }
        else
        {
            depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
        }
        Graphics::GetDevice3D().CreateDepthStencilView(_depthTexture.Get(), &depthStencilViewDesc, _depthStencilView.GetAddressOf());

        _constantBuffer.Reset();
        D3D11_BUFFER_DESC constantBufferDesc = {};
        constantBufferDesc.ByteWidth = sizeof(Constant);
        constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
        constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        constantBufferDesc.CPUAccessFlags = 0;
        Graphics::GetDevice3D().CreateBuffer(&constantBufferDesc, nullptr, _constantBuffer.GetAddressOf());
    }
    void OnProceedMessage(HWND, UINT message, WPARAM, LPARAM) override
    {
        if (message != WM_SIZE)
            return;

        if (Window::GetSize().x <= 0.0f || Window::GetSize().y <= 0.0f)
            return;

        if (_is3D)
        {
            SetupPerspective(_fieldOfView, _nearClip, _farClip);
        }
        else
        {
            if (_isAdjust)
                SetupOrthographic((float)Window::GetSize().y, _isAdjust, _nearClip, _farClip);
            else
                SetupOrthographic(_size, _isAdjust, _nearClip, _farClip);
        }

        Create();
    }
};