class Window
{
public:
    class Proceedable
    {
    public:
        virtual void OnProceedMessage(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) = 0;
    };

    static HWND GetHandle()
    {
        return Get()._handle;
    }
    static DirectX::XMINT2 GetSize()
    {
        RECT clientRect = {};
        GetClientRect(Get()._handle, &clientRect);

        return DirectX::XMINT2(clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
    }
    static void SetSize(int width, int height)
    {
        RECT windowRect = {};
        RECT clientRect = {};
        GetWindowRect(Get()._handle, &windowRect);
        GetClientRect(Get()._handle, &clientRect);

        int w = (windowRect.right - windowRect.left) - (clientRect.right - clientRect.left) + width;
        int h = (windowRect.bottom - windowRect.top) - (clientRect.bottom - clientRect.top) + height;
        int x = (GetSystemMetrics(SM_CXSCREEN) - w) / 2;
        int y = (GetSystemMetrics(SM_CYSCREEN) - h) / 2;

        SetWindowPos(Get()._handle, nullptr, x, y, w, h, SWP_FRAMECHANGED);
    }
    static wchar_t* const GetTitle()
    {
        wchar_t* title = nullptr;
        GetWindowTextW(Get()._handle, title, GetWindowTextLengthW(Get()._handle));
        return title;
    }
    static void SetTitle(const wchar_t* const title)
    {
        SetWindowTextW(Get()._handle, title);
    }
    static void SetFullScreen(bool isFullScreen)
    {
        static DirectX::XMINT2 size = GetSize();

        if (isFullScreen)
        {
            size = GetSize();
            int w = GetSystemMetrics(SM_CXSCREEN);
            int h = GetSystemMetrics(SM_CYSCREEN);
            SetWindowLongPtrW(Get()._handle, GWL_STYLE, WS_VISIBLE | WS_POPUP);
            SetWindowPos(Get()._handle, HWND_TOP, 0, 0, w, h, SWP_FRAMECHANGED);
        }
        else
        {
            SetWindowLongPtrW(Get()._handle, GWL_STYLE, WS_VISIBLE | WS_OVERLAPPEDWINDOW);
            SetWindowPos(Get()._handle, nullptr, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);
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

        PostMessageW(Get()._handle, WM_APP, 0, 0);

        if (GetSize().x <= 0.0f || GetSize().y <= 0.0f)
            Sleep(100);

        return true;
    }
    static void AddProcedure(Proceedable* const procedure)
    {
        Get()._procedures.push_back(procedure);
    }
    static void RemoveProcedure(Proceedable* const procedure)
    {
        Get()._procedures.remove(procedure);
    }

private:
    struct Property
    {
        const wchar_t* _className = L"XLibrary11";
        HWND _handle;
        std::list<Proceedable*> _procedures;
    };

    static Property& Get()
    {
        static std::unique_ptr<Property> prop;

        if (prop == nullptr)
        {
            prop.reset(new Property());

            InitializeApplication();

            HINSTANCE hInstance = GetModuleHandleW(nullptr);

            WNDCLASSW windowClass = {};
            windowClass.lpfnWndProc = ProceedMessage;
            windowClass.hInstance = hInstance;
            windowClass.hCursor = (HCURSOR)LoadImageW(nullptr, MAKEINTRESOURCEW(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_SHARED);
            windowClass.lpszClassName = Get()._className;
            RegisterClassW(&windowClass);

            Get()._handle = CreateWindowW(Get()._className, Get()._className, WS_OVERLAPPEDWINDOW, 0, 0, 0, 0, nullptr, nullptr, hInstance, nullptr);

            SetSize(640, 480);

            ShowWindow(Get()._handle, SW_SHOWNORMAL);
        }

        return *prop;
    }
    static LRESULT CALLBACK ProceedMessage(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
    {
        for (Proceedable* procedure : Get()._procedures)
        {
            procedure->OnProceedMessage(window, message, wParam, lParam);
        }

        if (message == WM_DESTROY)
            PostQuitMessage(0);

        return DefWindowProcW(window, message, wParam, lParam);
    }
};