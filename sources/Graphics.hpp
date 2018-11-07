/// Direct3D 11のオブジェクトにアクセスできます🤔
class Graphics
{
public:
    static ID3D11Device& GetDevice3D()
    {
        return *Get().device3D.Get();
    }
    static ID3D11DeviceContext& GetContext3D()
    {
        return *Get().context3D.Get();
    }
    static ID2D1Device& GetDevice2D()
    {
        return *Get().device2D.Get();
    }
    static ID2D1DeviceContext& GetContext2D()
    {
        return *Get().context2D.Get();
    }
    static IDXGISwapChain& GetSwapChain()
    {
        return *Get().swapChain.Get();
    }
    static IWICImagingFactory& GetTextureFactory()
    {
        return *Get().textureFactory.Get();
    }
    static IDWriteFactory& GetTextFactory()
    {
        return *Get().textFactory.Get();
    }
    static void Update()
    {
        if (Input::GetKey(VK_MENU) && Input::GetKeyDown(VK_RETURN))
        {
            Window::ToggleMode();
        }

        Get().swapChain->Present(1, 0);
    }

private:
    struct Property : public Window::Proceedable
    {
        ComPtr<ID3D11Device> device3D = nullptr;
        ComPtr<ID3D11DeviceContext> context3D = nullptr;
        ComPtr<ID2D1Device> device2D = nullptr;
        ComPtr<ID2D1DeviceContext> context2D = nullptr;
        ComPtr<IDXGISwapChain> swapChain = nullptr;
        ComPtr<IWICImagingFactory> textureFactory = nullptr;
        ComPtr<IDWriteFactory> textFactory = nullptr;

        void OnProceedMessage(HWND, UINT message, WPARAM, LPARAM) override
        {
            if (message != WM_SIZE)
                return;

            if (Window::GetSize().x <= 0.0f || Window::GetSize().y <= 0.0f)
                return;

            Create();
        }
    };

    static Property& Get()
    {
        static std::unique_ptr<Property> prop;

        if (prop == nullptr)
        {
            prop.reset(new Property());

            InitializeApplication();

            UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined(_DEBUG)
            flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

            std::vector<D3D_DRIVER_TYPE> driverTypes
            {
                D3D_DRIVER_TYPE_HARDWARE,
                D3D_DRIVER_TYPE_WARP,
                D3D_DRIVER_TYPE_REFERENCE,
                D3D_DRIVER_TYPE_SOFTWARE,
            };

            std::vector<D3D_FEATURE_LEVEL> featureLevels
            {
                D3D_FEATURE_LEVEL_11_0,
                D3D_FEATURE_LEVEL_10_1,
                D3D_FEATURE_LEVEL_10_0,
            };

            for (size_t i = 0; i < driverTypes.size(); i++)
            {
                HRESULT r = D3D11CreateDevice(nullptr, driverTypes[i], nullptr, flags, featureLevels.data(), (UINT)featureLevels.size(), D3D11_SDK_VERSION, Get().device3D.GetAddressOf(), nullptr, Get().context3D.GetAddressOf());

                if (SUCCEEDED(r))
                    break;
            }

            Get().context3D->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

            ComPtr<ID3D11BlendState> blendState = nullptr;
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
            Get().device3D->CreateBlendState(&blendDesc, &blendState);
            Get().context3D->OMSetBlendState(blendState.Get(), blendFactor, 0xffffffff);

            D2D1_FACTORY_OPTIONS options = {};
#if defined(_DEBUG)
            options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
#endif

            ComPtr<ID2D1Factory1> factory = nullptr;
            D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, options, factory.GetAddressOf());

            ComPtr<IDXGIDevice> device = nullptr;
            Get().device3D->QueryInterface(device.GetAddressOf());

            factory->CreateDevice(device.Get(), Get().device2D.GetAddressOf());

            Get().device2D->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, Get().context2D.GetAddressOf());

            CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, reinterpret_cast<void**>(Get().textureFactory.GetAddressOf()));

            DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(Get().textFactory.GetAddressOf()));

            Create();

            Window::AddProcedure(&Get());
        }

        return *prop;
    }
    static void Create()
    {
        ComPtr<IDXGIDevice> dxgi = nullptr;
        Get().device3D->QueryInterface(dxgi.GetAddressOf());

        ComPtr<IDXGIAdapter> adapter = nullptr;
        dxgi->GetAdapter(&adapter);

        ComPtr<IDXGIFactory> factory = nullptr;
        adapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(factory.GetAddressOf()));

        DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
        swapChainDesc.BufferDesc.Width = Window::GetSize().x;
        swapChainDesc.BufferDesc.Height = Window::GetSize().y;
        swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
        swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
        swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.SampleDesc.Quality = 0;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.BufferCount = 1;
        swapChainDesc.OutputWindow = Window::GetHandle();
        swapChainDesc.Windowed = true;

        Get().swapChain.Reset();
        factory->CreateSwapChain(Get().device3D.Get(), &swapChainDesc, Get().swapChain.GetAddressOf());
        factory->MakeWindowAssociation(Window::GetHandle(), DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER);

        D3D11_VIEWPORT viewPort = {};
        viewPort.Width = (float)Window::GetSize().x;
        viewPort.Height = (float)Window::GetSize().y;
        viewPort.MaxDepth = 1.0f;
        Get().context3D->RSSetViewports(1, &viewPort);
    }
};