class Camera : public Window::Proceedable
{
public:
    Float3 position;
    Float3 angles;
    Float4 color;

    Camera()
    {
        XLibraryInitialize();

        position = Float3(0.0f, 0.0f, 0.0f);
        angles = Float3(0.0f, 0.0f, 0.0f);
        color = Float4(1.0f, 1.0f, 1.0f, 1.0f);

        isDepthTest = false;
        SetOrthographic(1.0f, -D3D11_FLOAT32_MAX, D3D11_FLOAT32_MAX);

        Create();

        Window::AddProcedure(this);
    }
    ~Camera()
    {
        Window::RemoveProcedure(this);
    }
    void SetPerspective(float fieldOfView, float nearClip, float farClip)
    {
        isPerspective = true;
        this->fieldOfView = fieldOfView;
        this->nearClip = nearClip;
        this->farClip = farClip;
        float aspectRatio = Window::GetSize().x / (float)Window::GetSize().y;
        constant.projection = DirectX::XMMatrixTranspose(
            DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(fieldOfView), aspectRatio, nearClip, farClip)
        );
    }
    void SetOrthographic(float size, float nearClip, float farClip)
    {
        isPerspective = false;
        this->size = size;
        this->nearClip = nearClip;
        this->farClip = farClip;
        constant.projection = DirectX::XMMatrixTranspose(
            DirectX::XMMatrixOrthographicLH(Window::GetSize().x * size, Window::GetSize().y * size, nearClip, farClip)
        );
    }
    void SetDepthTest(bool isDepthTest)
    {
        this->isDepthTest = isDepthTest;
    }
    void Update(bool shouldClear = true)
    {
        constant.view = DirectX::XMMatrixTranspose(
            DirectX::XMMatrixInverse(
                nullptr,
                DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(angles.x)) *
                DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(angles.y)) *
                DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(angles.z)) *
                DirectX::XMMatrixTranslation(position.x, position.y, position.z)
            )
        );

        Graphics::GetContext3D().UpdateSubresource(constantBuffer, 0, nullptr, &constant, 0, 0);
        Graphics::GetContext3D().VSSetConstantBuffers(0, 1, &constantBuffer.p);
        Graphics::GetContext3D().HSSetConstantBuffers(0, 1, &constantBuffer.p);
        Graphics::GetContext3D().DSSetConstantBuffers(0, 1, &constantBuffer.p);
        Graphics::GetContext3D().GSSetConstantBuffers(0, 1, &constantBuffer.p);
        Graphics::GetContext3D().PSSetConstantBuffers(0, 1, &constantBuffer.p);

        if (shouldClear)
        {
            float clearColor[4] = { color.x, color.y, color.z, color.w };
            Graphics::GetContext3D().ClearRenderTargetView(renderTargetView, clearColor);
        }

        if (isDepthTest)
        {
            Graphics::GetContext3D().ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
            Graphics::GetContext3D().OMSetRenderTargets(1, &renderTargetView.p, depthStencilView);
        }
        else
        {
            Graphics::GetContext3D().OMSetRenderTargets(1, &renderTargetView.p, nullptr);
        }
    }

private:
    struct Constant
    {
        DirectX::XMMATRIX view;
        DirectX::XMMATRIX projection;
    };

    bool isPerspective;
    float fieldOfView;
    float size;
    float nearClip;
    float farClip;
    bool isDepthTest;
    Constant constant;
    ATL::CComPtr<ID3D11RenderTargetView> renderTargetView = nullptr;
    ATL::CComPtr<ID3D11DepthStencilView> depthStencilView = nullptr;
    ATL::CComPtr<ID3D11Texture2D> renderTexture = nullptr;
    ATL::CComPtr<ID3D11Texture2D> depthTexture = nullptr;
    ATL::CComPtr<ID3D11Buffer> constantBuffer = nullptr;

    void Create()
    {
        renderTexture.Release();
        Graphics::GetSwapChain().GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&renderTexture));
        renderTargetView.Release();
        Graphics::GetDevice3D().CreateRenderTargetView(renderTexture, nullptr, &renderTargetView);

        DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
        Graphics::GetSwapChain().GetDesc(&swapChainDesc);

        depthTexture.Release();
        D3D11_TEXTURE2D_DESC textureDesc = {};
        textureDesc.Width = static_cast<UINT>(Window::GetSize().x);
        textureDesc.Height = static_cast<UINT>(Window::GetSize().y);
        textureDesc.MipLevels = 1;
        textureDesc.ArraySize = 1;
        textureDesc.Format = DXGI_FORMAT_R32_TYPELESS;
        textureDesc.SampleDesc.Count = swapChainDesc.SampleDesc.Count;
        textureDesc.SampleDesc.Quality = swapChainDesc.SampleDesc.Quality;
        textureDesc.Usage = D3D11_USAGE_DEFAULT;
        textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        textureDesc.CPUAccessFlags = 0;
        textureDesc.MiscFlags = 0;
        Graphics::GetDevice3D().CreateTexture2D(&textureDesc, nullptr, &depthTexture);

        depthStencilView.Release();
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
        Graphics::GetDevice3D().CreateDepthStencilView(depthTexture, &depthStencilViewDesc, &depthStencilView);

        constantBuffer.Release();
        D3D11_BUFFER_DESC constantBufferDesc = {};
        constantBufferDesc.ByteWidth = static_cast<UINT>(sizeof(Constant));
        constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
        constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        constantBufferDesc.CPUAccessFlags = 0;
        Graphics::GetDevice3D().CreateBuffer(&constantBufferDesc, nullptr, &constantBuffer);
    }
    void OnProceed(HWND, UINT message, WPARAM, LPARAM) override
    {
        if (message != WM_SIZE)
            return;

        if (Window::GetSize().x <= 0.0f || Window::GetSize().y <= 0.0f)
            return;

        if (isPerspective)
            SetPerspective(fieldOfView, nearClip, farClip);
        else
            SetOrthographic(size, nearClip, farClip);

        Create();
    }
};