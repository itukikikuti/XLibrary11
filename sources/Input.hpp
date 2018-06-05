class Input
{
public:
    Input()
    {
        XLibraryInitialize();

        Update();
    }
    ~Input()
    {
    }
    bool GetKey(int keyCode) const
    {
        return keyState[keyCode] & 0x80;
    }
    bool GetKeyUp(int keyCode) const
    {
        return !(keyState[keyCode] & 0x80) && (preKeyState[keyCode] & 0x80);
    }
    bool GetKeyDown(int keyCode) const
    {
        return (keyState[keyCode] & 0x80) && !(preKeyState[keyCode] & 0x80);
    }
    Float2 GetMousePosition() const
    {
        return mousePosition;
    }
    void SetMousePosition(float x, float y)
    {
        if (GetActiveWindow() != Window::GetHandle())
            return;

        POINT point = {};
        point.x = static_cast<int>(x) + Window::GetSize().x / 2;
        point.y = static_cast<int>(-y) + Window::GetSize().y / 2;
        ClientToScreen(Window::GetHandle(), &point);
        SetCursorPos(point.x, point.y);

        mousePosition.x = x;
        mousePosition.y = y;
    }
    void SetShowCursor(bool isShowCursor)
    {
        if (this->isShowCursor == isShowCursor)
            return;

        this->isShowCursor = isShowCursor;
        ShowCursor(isShowCursor);
    }
    void Update()
    {
        POINT point = {};
        GetCursorPos(&point);
        ScreenToClient(Window::GetHandle(), &point);

        mousePosition.x = static_cast<float>(point.x - Window::GetSize().x / 2);
        mousePosition.y = static_cast<float>(-point.y + Window::GetSize().y / 2);

        for (int i = 0; i < 256; i++)
        {
            preKeyState[i] = keyState[i];
        }

        GetKeyboardState(keyState);
    }

private:
    Float2 mousePosition;
    BYTE preKeyState[256];
    BYTE keyState[256];
    bool isShowCursor = true;
};