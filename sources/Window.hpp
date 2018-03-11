class Window
{
public:
    class Proceedable
    {
    public:
        virtual void OnProceed(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) = 0;
    };

    Window()
    {
        App::Initialize();

        HINSTANCE instance = GetModuleHandleW(nullptr);

        WNDCLASSW windowClass = {};
        windowClass.lpfnWndProc = ProceedMessage;
        windowClass.hInstance = instance;
        windowClass.hCursor = (HCURSOR)LoadImageW(nullptr, MAKEINTRESOURCEW(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_SHARED);
        windowClass.lpszClassName = App::NAME;
        RegisterClassW(&windowClass);

        handle = CreateWindowW(App::NAME, App::NAME, WS_OVERLAPPEDWINDOW, 0, 0, 0, 0, nullptr, nullptr, instance, nullptr);

        SetSize(1280, 720);
        ShowWindow(handle, SW_SHOWNORMAL);
    }
    ~Window()
    {
        UnregisterClassW(App::NAME, GetModuleHandleW(nullptr));
    }
    HWND GetHandle() const
    {
        return handle;
    }
    DirectX::XMINT2 GetSize() const
    {
        RECT clientRect = {};
        GetClientRect(handle, &clientRect);

        return DirectX::XMINT2(clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
    }
    void SetSize(int width, int height)
    {
        RECT windowRect = {};
        RECT clientRect = {};
        GetWindowRect(handle, &windowRect);
        GetClientRect(handle, &clientRect);

        int w = (windowRect.right - windowRect.left) - (clientRect.right - clientRect.left) + width;
        int h = (windowRect.bottom - windowRect.top) - (clientRect.bottom - clientRect.top) + height;
        int x = (GetSystemMetrics(SM_CXSCREEN) - w) / 2;
        int y = (GetSystemMetrics(SM_CYSCREEN) - h) / 2;

        SetWindowPos(handle, nullptr, x, y, w, h, SWP_FRAMECHANGED);
    }
    wchar_t* const GetTitle() const
    {
        wchar_t* title = nullptr;
        GetWindowTextW(handle, title, GetWindowTextLengthW(handle));
        return title;
    }
    void SetTitle(const wchar_t* const title)
    {
        SetWindowTextW(handle, title);
    }
    void SetFullScreen(bool isFullScreen)
    {
        static DirectX::XMINT2 size = GetSize();

        if (isFullScreen)
        {
            size = GetSize();
            int w = GetSystemMetrics(SM_CXSCREEN);
            int h = GetSystemMetrics(SM_CYSCREEN);
            SetWindowLongPtrW(handle, GWL_STYLE, WS_VISIBLE | WS_POPUP);
            SetWindowPos(handle, HWND_TOP, 0, 0, w, h, SWP_FRAMECHANGED);
        }
        else
        {
            SetWindowLongPtrW(handle, GWL_STYLE, WS_VISIBLE | WS_OVERLAPPEDWINDOW);
            SetWindowPos(handle, nullptr, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);
            SetSize(size.x, size.y);
        }
    }
    void AddProcedure(Proceedable* const procedure)
    {
        GetProcedures().push_front(procedure);
    }
    void RemoveProcedure(Proceedable* const procedure)
    {
        GetProcedures().remove(procedure);
    }
    bool Update()
    {
        MSG message = {};

        while (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE))
        {
            if (message.message == WM_QUIT)
                return false;

            TranslateMessage(&message);
            DispatchMessageW(&message);
        }

        return true;
    }

private:
    HWND handle;

    static std::forward_list<Proceedable*>& GetProcedures()
    {
        static std::forward_list<Proceedable*> procedures;
        return procedures;
    }
    static LRESULT CALLBACK ProceedMessage(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
    {
        for (Proceedable* procedure : GetProcedures())
        {
            procedure->OnProceed(window, message, wParam, lParam);
        }

        if (message == WM_DESTROY)
            PostQuitMessage(0);

        return DefWindowProcW(window, message, wParam, lParam);
    }
};