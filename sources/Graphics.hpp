class Graphics : public App::Window::Proceedable
{
public:
    Graphics()
    {
        App::Initialize();

        UINT flags = 0;
#if defined(_DEBUG)
        flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

        std::vector<D3D_FEATURE_LEVEL> featureLevels
        {
            D3D_FEATURE_LEVEL_11_0,
            D3D_FEATURE_LEVEL_10_1,
            D3D_FEATURE_LEVEL_10_0,
        };

        DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
        swapChainDesc.BufferDesc.Width = App::GetWindowSize().x;
        swapChainDesc.BufferDesc.Height = App::GetWindowSize().y;
        swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
        swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
        swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.SampleDesc.Quality = 0;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.BufferCount = 1;
        swapChainDesc.OutputWindow = App::GetWindowHandle();
        swapChainDesc.Windowed = true;
        D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flags, featureLevels.data(), featureLevels.size(), D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device, nullptr, &context);

        context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        ATL::CComPtr<ID3D11BlendState> blendState = nullptr;
        D3D11_BLEND_DESC blendDesc = {};
        blendDesc.RenderTarget[0].BlendEnable = true;
        blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
        blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
        blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
        blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
        blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
        blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
        blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

        float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
        device->CreateBlendState(&blendDesc, &blendState);
        context->OMSetBlendState(blendState, blendFactor, 0xffffffff);

        D3D11_BUFFER_DESC constantBufferDesc = {};
        constantBufferDesc.ByteWidth = sizeof(Constant);
        constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
        constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        device->CreateBuffer(&constantBufferDesc, nullptr, &constantBuffer);

        App::AddProcedure(this);

        CreateRenderTarget();
    }
    ~Graphics()
    {
        App::RemoveProcedure(this);
    }
    ID3D11Device& GetDevice() const
    {
        return *device;
    }
    IDXGISwapChain& GetMemory() const
    {
        return *swapChain;
    }
    ID3D11DeviceContext& GetContext() const
    {
        return *context;
    }
    void Update()
    {
        swapChain->Present(1, 0);

        context->UpdateSubresource(constantBuffer, 0, nullptr, &constant, 0, 0);
        context->VSSetConstantBuffers(1, 1, &constantBuffer.p);
        context->HSSetConstantBuffers(1, 1, &constantBuffer.p);
        context->DSSetConstantBuffers(1, 1, &constantBuffer.p);
        context->GSSetConstantBuffers(1, 1, &constantBuffer.p);
        context->PSSetConstantBuffers(1, 1, &constantBuffer.p);

        context->OMSetRenderTargets(1, &renderTargetView.p, nullptr);

        static float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        context->ClearRenderTargetView(renderTargetView, color);
    }

private:
    struct Constant
    {
        DirectX::XMMATRIX view;
        DirectX::XMMATRIX projection;
    };

    Constant constant;
    ATL::CComPtr<ID3D11Device> device = nullptr;
    ATL::CComPtr<IDXGISwapChain> swapChain = nullptr;
    ATL::CComPtr<ID3D11DeviceContext> context = nullptr;
    ATL::CComPtr<ID3D11RenderTargetView> renderTargetView = nullptr;
    ATL::CComPtr<ID3D11Texture2D> renderTexture = nullptr;
    ATL::CComPtr<ID3D11Buffer> constantBuffer = nullptr;

    void CreateRenderTarget()
    {
        D3D11_VIEWPORT viewPort = {};
        viewPort.Width = static_cast<float>(App::GetWindowSize().x);
        viewPort.Height = static_cast<float>(App::GetWindowSize().y);
        context->RSSetViewports(1, &viewPort);

        swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&renderTexture));
        device->CreateRenderTargetView(renderTexture, nullptr, &renderTargetView);

        constant.view = DirectX::XMMatrixIdentity();
        constant.projection = DirectX::XMMatrixOrthographicLH(static_cast<float>(App::GetWindowSize().x), static_cast<float>(App::GetWindowSize().y), -10000.0f, 10000.0f);
    }
    void OnProceed(HWND, UINT message, WPARAM, LPARAM) override
    {
        if (message != WM_SIZE)
            return;

        if (App::GetWindowSize().x <= 0.0f || App::GetWindowSize().y <= 0.0f)
            return;

        DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
        swapChain->GetDesc(&swapChainDesc);

        ATL::CComPtr<ID3D11RenderTargetView> nullRenderTarget = nullptr;
        context->OMSetRenderTargets(1, &nullRenderTarget, nullptr);
        renderTargetView.Release();
        renderTexture.Release();
        context->Flush();
        swapChain->ResizeBuffers(swapChainDesc.BufferCount, App::GetWindowSize().x, App::GetWindowSize().y, swapChainDesc.BufferDesc.Format, 0);

        CreateRenderTarget();
    }
};