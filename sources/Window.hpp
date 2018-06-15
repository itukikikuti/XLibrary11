class Window
{
public:
    class Proceedable
    {
    public:
        virtual void OnProceed(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) = 0;
    };

    static HWND GetHandle()
    {
        return GetInstance()._handle;
    }
    static DirectX::XMINT2 GetSize()
    {
        RECT clientRect = {};
        GetClientRect(GetInstance()._handle, &clientRect);

        return DirectX::XMINT2(clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
    }
    static void SetSize(int width, int height)
    {
        RECT windowRect = {};
        RECT clientRect = {};
        GetWindowRect(GetInstance()._handle, &windowRect);
        GetClientRect(GetInstance()._handle, &clientRect);

        int w = (windowRect.right - windowRect.left) - (clientRect.right - clientRect.left) + width;
        int h = (windowRect.bottom - windowRect.top) - (clientRect.bottom - clientRect.top) + height;
        int x = (GetSystemMetrics(SM_CXSCREEN) - w) / 2;
        int y = (GetSystemMetrics(SM_CYSCREEN) - h) / 2;

        SetWindowPos(GetInstance()._handle, nullptr, x, y, w, h, SWP_FRAMECHANGED);
    }
    static wchar_t* const GetTitle()
    {
        wchar_t* title = nullptr;
        GetWindowTextW(GetInstance()._handle, title, GetWindowTextLengthW(GetInstance()._handle));
        return title;
    }
    static void SetTitle(const wchar_t* const title)
    {
        SetWindowTextW(GetInstance()._handle, title);
    }
    static void SetFullScreen(bool isFullScreen)
    {
        static DirectX::XMINT2 size = GetSize();

        if (isFullScreen)
        {
            size = GetSize();
            int w = GetSystemMetrics(SM_CXSCREEN);
            int h = GetSystemMetrics(SM_CYSCREEN);
            SetWindowLongPtrW(GetInstance()._handle, GWL_STYLE, WS_VISIBLE | WS_POPUP);
            SetWindowPos(GetInstance()._handle, HWND_TOP, 0, 0, w, h, SWP_FRAMECHANGED);
        }
        else
        {
            SetWindowLongPtrW(GetInstance()._handle, GWL_STYLE, WS_VISIBLE | WS_OVERLAPPEDWINDOW);
            SetWindowPos(GetInstance()._handle, nullptr, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);
            SetSize(size.x, size.y);
        }
    }
    static bool Update()
    {
        MSG message = {};

        while (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE))
        {
            if (message.message == WM_QUIT)
                return false;

            TranslateMessage(&message);
            DispatchMessageW(&message);
        }

        PostMessageW(GetInstance()._handle, WM_APP, 0, 0);

        if (GetSize().x <= 0.0f || GetSize().y <= 0.0f)
            Sleep(100);

        return true;
    }
    static void AddProcedure(Proceedable* const procedure)
    {
        GetInstance()._procedures.push_back(procedure);
    }
    static void RemoveProcedure(Proceedable* const procedure)
    {
        GetInstance()._procedures.remove(procedure);
    }

private:
    friend std::unique_ptr<Window>::deleter_type;

    const wchar_t* _className = L"XLibrary11";
    HWND _handle;
    std::list<Proceedable*> _procedures;

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    Window()
    {
        InitializeApplication();

        HINSTANCE instance = GetModuleHandleW(nullptr);

        WNDCLASSW windowClass = {};
        windowClass.lpfnWndProc = DefWindowProcW;
        windowClass.hInstance = instance;
        windowClass.hCursor = (HCURSOR)LoadImageW(nullptr, MAKEINTRESOURCEW(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_SHARED);
        windowClass.lpszClassName = _className;
        RegisterClassW(&windowClass);

        _handle = CreateWindowW(_className, _className, WS_OVERLAPPEDWINDOW, 0, 0, 0, 0, nullptr, nullptr, instance, nullptr);

        ShowWindow(_handle, SW_SHOWNORMAL);
    }
    ~Window()
    {
        CoUninitialize();
    }
    static Window& GetInstance()
    {
        static std::unique_ptr<Window> instance;

        if (instance == nullptr)
        {
            instance.reset(Instantiate());
            SetSize(640, 480);
            SetWindowLongPtrW(GetHandle(), GWLP_WNDPROC, (LONG_PTR)ProceedMessage);
        }

        return *instance;
    }
    static Window* Instantiate()
    {
        return new Window();
    }
    static LRESULT CALLBACK ProceedMessage(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
    {
        for (Proceedable* procedure : GetInstance()._procedures)
        {
            procedure->OnProceed(window, message, wParam, lParam);
        }

        if (message == WM_DESTROY)
            PostQuitMessage(0);

        return DefWindowProcW(window, message, wParam, lParam);
    }
};