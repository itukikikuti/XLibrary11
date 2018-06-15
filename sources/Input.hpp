class Input
{
public:
    static bool GetKey(int VK_CODE)
    {
        return GetInstance()._keyState[VK_CODE] & 0x80;
    }
    static bool GetKeyUp(int VK_CODE)
    {
        return !(GetInstance()._keyState[VK_CODE] & 0x80) && (GetInstance()._preKeyState[VK_CODE] & 0x80);
    }
    static bool GetKeyDown(int VK_CODE)
    {
        return (GetInstance()._keyState[VK_CODE] & 0x80) && !(GetInstance()._preKeyState[VK_CODE] & 0x80);
    }
    static Float2 GetMousePosition()
    {
        return GetInstance()._mousePosition;
    }
    static void SetMousePosition(float x, float y)
    {
        if (GetActiveWindow() != Window::GetHandle())
            return;

        POINT point = {};
        point.x = (int)x + Window::GetSize().x / 2;
        point.y = (int)-y + Window::GetSize().y / 2;
        ClientToScreen(Window::GetHandle(), &point);
        SetCursorPos(point.x, point.y);

        GetInstance()._mousePosition.x = x;
        GetInstance()._mousePosition.y = y;
    }
    static void SetShowCursor(bool isShowCursor)
    {
        if (GetInstance()._isShowCursor == isShowCursor)
            return;

        GetInstance()._isShowCursor = isShowCursor;
        ShowCursor(isShowCursor);
    }
    static void Update()
    {
        POINT point = {};
        GetCursorPos(&point);
        ScreenToClient(Window::GetHandle(), &point);

        GetInstance()._mousePosition.x = (float)point.x - Window::GetSize().x / 2;
        GetInstance()._mousePosition.y = (float)-point.y + Window::GetSize().y / 2;

        for (int i = 0; i < 256; i++)
        {
            GetInstance()._preKeyState[i] = GetInstance()._keyState[i];
        }

        GetKeyboardState(GetInstance()._keyState);
    }

private:
    friend std::unique_ptr<Input>::deleter_type;

    Float2 _mousePosition;
    BYTE _preKeyState[256];
    BYTE _keyState[256];
    bool _isShowCursor = true;

    Input(const Input&) = delete;
    Input& operator=(const Input&) = delete;
    Input()
    {
        InitializeApplication();
    }
    ~Input()
    {
    }
    static Input& GetInstance()
    {
        static std::unique_ptr<Input> instance;

        if (instance == nullptr)
        {
            instance.reset(Instantiate());
            Update();
        }

        return *instance;
    }
    static Input* Instantiate()
    {
        return new Input();
    }
};