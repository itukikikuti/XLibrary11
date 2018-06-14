class Input
{
public:
    static bool GetKey(int VK_CODE)
    {
        return GetInstance().keyState[VK_CODE] & 0x80;
    }
    static bool GetKeyUp(int VK_CODE)
    {
        return !(GetInstance().keyState[VK_CODE] & 0x80) && (GetInstance().preKeyState[VK_CODE] & 0x80);
    }
    static bool GetKeyDown(int VK_CODE)
    {
        return (GetInstance().keyState[VK_CODE] & 0x80) && !(GetInstance().preKeyState[VK_CODE] & 0x80);
    }
    static Float2 GetMousePosition()
    {
        return GetInstance().mousePosition;
    }
    static void SetMousePosition(float x, float y)
    {
        if (GetActiveWindow() != Window::GetHandle())
            return;

        POINT point = {};
        point.x = static_cast<int>(x) + Window::GetSize().x / 2;
        point.y = static_cast<int>(-y) + Window::GetSize().y / 2;
        ClientToScreen(Window::GetHandle(), &point);
        SetCursorPos(point.x, point.y);

        GetInstance().mousePosition.x = x;
        GetInstance().mousePosition.y = y;
    }
    static void SetShowCursor(bool isShowCursor)
    {
        if (GetInstance().isShowCursor == isShowCursor)
            return;

        GetInstance().isShowCursor = isShowCursor;
        ShowCursor(isShowCursor);
    }
    static void Update()
    {
        POINT point = {};
        GetCursorPos(&point);
        ScreenToClient(Window::GetHandle(), &point);

        GetInstance().mousePosition.x = static_cast<float>(point.x - Window::GetSize().x / 2);
        GetInstance().mousePosition.y = static_cast<float>(-point.y + Window::GetSize().y / 2);

        for (int i = 0; i < 256; i++)
        {
            GetInstance().preKeyState[i] = GetInstance().keyState[i];
        }

        GetKeyboardState(GetInstance().keyState);
    }

private:
    friend std::unique_ptr<Input>::deleter_type;

    Float2 mousePosition;
    BYTE preKeyState[256];
    BYTE keyState[256];
    bool isShowCursor = true;

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