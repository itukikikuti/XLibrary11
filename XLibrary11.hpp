/*! © 2017 itukikikuti | MIT License | gitlab.com/itukikikuti/XLibrary11 */
#pragma once

#define NOMINMAX
#define OEMRESOURCE
#include <array>
#include <chrono>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <limits>
#include <list>
#include <memory>
#include <random>
#include <string>
#include <system_error>
#include <thread>
#include <vector>
#include <Windows.h>
#include <d2d1_1.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <dsound.h>
#include <dwrite.h>
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <Shlwapi.h>
#include <wincodec.h>
#include <wrl.h>
#include <Xinput.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "mfuuid.lib")
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "Xinput.lib")

#define MAIN() APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)

/// XLibraryの名前空間です。
namespace XLibrary
{

using namespace DirectX;
using Microsoft::WRL::ComPtr;

inline void InitializeApplication()
{
    static bool isInitialized = false;

    if (!isInitialized)
    {
        CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
        isInitialized = true;
    }
}

struct Float2 : public DirectX::XMFLOAT2
{
    Float2() : DirectX::XMFLOAT2()
    {
    }
    Float2(float x, float y) : DirectX::XMFLOAT2(x, y)
    {
    }
    Float2(float value) : DirectX::XMFLOAT2(value, value)
    {
    }
    Float2(const DirectX::XMVECTOR& vector) : DirectX::XMFLOAT2()
    {
        DirectX::XMStoreFloat2(this, vector);
    }
    Float2& operator=(const DirectX::XMVECTOR& vector)
    {
        DirectX::XMStoreFloat2(this, vector);
        return *this;
    }
    operator DirectX::XMVECTOR() const
    {
        return DirectX::XMLoadFloat2(this);
    }
    Float2 operator+() const
    {
        return Float2(x, y);
    }
    Float2 operator-() const
    {
        return Float2(-x, -y);
    }
    Float2& operator=(const Float2& value)
    {
        x = value.x;
        y = value.y;
        return *this;
    }
    Float2& operator=(const float& value)
    {
        x = value;
        y = value;
        return *this;
    }
    Float2& operator+=(const Float2& value)
    {
        x += value.x;
        y += value.y;
        return *this;
    }
    Float2& operator+=(const float& value)
    {
        x += value;
        y += value;
        return *this;
    }
    Float2& operator-=(const Float2& value)
    {
        x -= value.x;
        y -= value.y;
        return *this;
    }
    Float2& operator-=(const float& value)
    {
        x -= value;
        y -= value;
        return *this;
    }
    Float2& operator*=(const Float2& value)
    {
        x *= value.x;
        y *= value.y;
        return *this;
    }
    Float2& operator*=(const float& value)
    {
        x *= value;
        y *= value;
        return *this;
    }
    Float2& operator/=(const Float2& value)
    {
        x /= value.x;
        y /= value.y;
        return *this;
    }
    Float2& operator/=(const float& value)
    {
        x /= value;
        y /= value;
        return *this;
    }
};

inline Float2 operator+(const Float2& t1, const Float2& t2)
{
    return Float2(t1) += t2;
}
inline Float2 operator+(const Float2& t1, const float& t2)
{
    return Float2(t1) += t2;
}
inline Float2 operator-(const Float2& t1, const Float2& t2)
{
    return Float2(t1) -= t2;
}
inline Float2 operator-(const Float2& t1, const float& t2)
{
    return Float2(t1) -= t2;
}
inline Float2 operator*(const Float2& t1, const Float2& t2)
{
    return Float2(t1) *= t2;
}
inline Float2 operator*(const Float2& t1, const float& t2)
{
    return Float2(t1) *= t2;
}
inline Float2 operator/(const Float2& t1, const Float2& t2)
{
    return Float2(t1) /= t2;
}
inline Float2 operator/(const Float2& t1, const float& t2)
{
    return Float2(t1) /= t2;
}

struct Float3 : public DirectX::XMFLOAT3
{
    Float3() : DirectX::XMFLOAT3()
    {
    }
    Float3(float x, float y, float z) : DirectX::XMFLOAT3(x, y, z)
    {
    }
    Float3(float value) : DirectX::XMFLOAT3(value, value, value)
    {
    }
    Float3(const DirectX::XMVECTOR& vector) : DirectX::XMFLOAT3()
    {
        DirectX::XMStoreFloat3(this, vector);
    }
    Float3& operator=(const DirectX::XMVECTOR& vector)
    {
        DirectX::XMStoreFloat3(this, vector);
        return *this;
    }
    operator DirectX::XMVECTOR() const
    {
        return DirectX::XMLoadFloat3(this);
    }
    Float3 operator+() const
    {
        return Float3(x, y, z);
    }
    Float3 operator-() const
    {
        return Float3(-x, -y, -z);
    }
    Float3& operator=(const Float3& value)
    {
        x = value.x;
        y = value.y;
        z = value.z;
        return *this;
    }
    Float3& operator=(const float& value)
    {
        x = value;
        y = value;
        z = value;
        return *this;
    }
    Float3& operator+=(const Float3& value)
    {
        x += value.x;
        y += value.y;
        z += value.z;
        return *this;
    }
    Float3& operator+=(const float& value)
    {
        x += value;
        y += value;
        z += value;
        return *this;
    }
    Float3& operator-=(const Float3& value)
    {
        x -= value.x;
        y -= value.y;
        z -= value.z;
        return *this;
    }
    Float3& operator-=(const float& value)
    {
        x -= value;
        y -= value;
        z -= value;
        return *this;
    }
    Float3& operator*=(const Float3& value)
    {
        x *= value.x;
        y *= value.y;
        z *= value.z;
        return *this;
    }
    Float3& operator*=(const float& value)
    {
        x *= value;
        y *= value;
        z *= value;
        return *this;
    }
    Float3& operator/=(const Float3& value)
    {
        x /= value.x;
        y /= value.y;
        z /= value.z;
        return *this;
    }
    Float3& operator/=(const float& value)
    {
        x /= value;
        y /= value;
        z /= value;
        return *this;
    }
};

inline Float3 operator+(const Float3& t1, const Float3& t2)
{
    return Float3(t1) += t2;
}
inline Float3 operator+(const Float3& t1, const float& t2)
{
    return Float3(t1) += t2;
}
inline Float3 operator-(const Float3& t1, const Float3& t2)
{
    return Float3(t1) -= t2;
}
inline Float3 operator-(const Float3& t1, const float& t2)
{
    return Float3(t1) -= t2;
}
inline Float3 operator*(const Float3& t1, const Float3& t2)
{
    return Float3(t1) *= t2;
}
inline Float3 operator*(const Float3& t1, const float& t2)
{
    return Float3(t1) *= t2;
}
inline Float3 operator/(const Float3& t1, const Float3& t2)
{
    return Float3(t1) /= t2;
}
inline Float3 operator/(const Float3& t1, const float& t2)
{
    return Float3(t1) /= t2;
}

struct Float4 : public DirectX::XMFLOAT4
{
    Float4() : DirectX::XMFLOAT4()
    {
    }
    Float4(float x, float y, float z, float w) : DirectX::XMFLOAT4(x, y, z, w)
    {
    }
    Float4(float value) : DirectX::XMFLOAT4(value, value, value, value)
    {
    }
    Float4(const DirectX::XMVECTOR& vector) : DirectX::XMFLOAT4()
    {
        DirectX::XMStoreFloat4(this, vector);
    }
    Float4& operator=(const DirectX::XMVECTOR& vector)
    {
        DirectX::XMStoreFloat4(this, vector);
        return *this;
    }
    operator DirectX::XMVECTOR() const
    {
        return DirectX::XMLoadFloat4(this);
    }
    Float4 operator+() const
    {
        return Float4(x, y, z, w);
    }
    Float4 operator-() const
    {
        return Float4(-x, -y, -z, -w);
    }
    Float4& operator=(const Float4& value)
    {
        x = value.x;
        y = value.y;
        z = value.z;
        w = value.w;
        return *this;
    }
    Float4& operator=(const float& value)
    {
        x = value;
        y = value;
        z = value;
        w = value;
        return *this;
    }
    Float4& operator+=(const Float4& value)
    {
        x += value.x;
        y += value.y;
        z += value.z;
        w += value.w;
        return *this;
    }
    Float4& operator+=(const float& value)
    {
        x += value;
        y += value;
        z += value;
        w += value;
        return *this;
    }
    Float4& operator-=(const Float4& value)
    {
        x -= value.x;
        y -= value.y;
        z -= value.z;
        w -= value.w;
        return *this;
    }
    Float4& operator-=(const float& value)
    {
        x -= value;
        y -= value;
        z -= value;
        w -= value;
        return *this;
    }
    Float4& operator*=(const Float4& value)
    {
        x *= value.x;
        y *= value.y;
        z *= value.z;
        w *= value.w;
        return *this;
    }
    Float4& operator*=(const float& value)
    {
        x *= value;
        y *= value;
        z *= value;
        w *= value;
        return *this;
    }
    Float4& operator/=(const Float4& value)
    {
        x /= value.x;
        y /= value.y;
        z /= value.z;
        w /= value.w;
        return *this;
    }
    Float4& operator/=(const float& value)
    {
        x /= value;
        y /= value;
        z /= value;
        w /= value;
        return *this;
    }
};

inline Float4 operator+(const Float4& t1, const Float4& t2)
{
    return Float4(t1) += t2;
}
inline Float4 operator+(const Float4& t1, const float& t2)
{
    return Float4(t1) += t2;
}
inline Float4 operator-(const Float4& t1, const Float4& t2)
{
    return Float4(t1) -= t2;
}
inline Float4 operator-(const Float4& t1, const float& t2)
{
    return Float4(t1) -= t2;
}
inline Float4 operator*(const Float4& t1, const Float4& t2)
{
    return Float4(t1) *= t2;
}
inline Float4 operator*(const Float4& t1, const float& t2)
{
    return Float4(t1) *= t2;
}
inline Float4 operator/(const Float4& t1, const Float4& t2)
{
    return Float4(t1) /= t2;
}
inline Float4 operator/(const Float4& t1, const float& t2)
{
    return Float4(t1) /= t2;
}

struct Vertex
{
    Float3 position;
    Float3 normal;
    Float2 uv;
    uint32_t blendIndices[8] = { 999, 999, 999, 999, 999, 999, 999, 999 };
    float blendWeights[8] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

    Vertex()
    {
    }
    Vertex(Float3 position, Float3 normal, Float2 uv)
    {
        this->position = position;
        this->normal = normal;
        this->uv = uv;
    }
};

class Utility
{
public:
    static std::string Format(const char* const format, ...)
    {
        va_list arguments;

        va_start(arguments, format);
        int size = vprintf_s(format, arguments);
        va_end(arguments);

        std::unique_ptr<char[]> buffer(new char[size + 1]);
        va_start(arguments, format);
        vsprintf_s(buffer.get(), size + 1, format, arguments);
        va_end(arguments);

        return std::string(buffer.get());
    }
    static std::wstring WFormat(const wchar_t* const format, ...)
    {
        va_list arguments;

        va_start(arguments, format);
        int size = vwprintf_s(format, arguments);
        va_end(arguments);

        std::unique_ptr<wchar_t[]> buffer(new wchar_t[size + 1]);
        va_start(arguments, format);
        vswprintf_s(buffer.get(), size + 1, format, arguments);
        va_end(arguments);

        return std::wstring(buffer.get());
    }
    static void Alert(DWORD errorCodeValue)
    {
        std::error_code errorCode(errorCodeValue, std::system_category());
        MessageBoxA(nullptr, errorCode.message().c_str(), Utility::Format("Error code 0x%x(%d)", errorCode.value(), errorCode.value()).c_str(), MB_ICONERROR | MB_OK);
#if defined(_DEBUG)
        throw std::system_error(errorCode);
#else
        std::exit(errorCode.value());
#endif
    }
};

/// ウィンドウに関する操作ができます。
class Window
{
public:
    /// 継承するとウィンドウのメッセージを受け取れます。
    class Proceedable
    {
    public:
        virtual void OnProceedMessage(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) = 0;
    };
    /// ウィンドウの種類
    enum class Mode
    {
        Windowed,   ///< ウィンドウモード
        FullScreen, ///< フルスクリーンモード
    };

    /// ウィンドウのハンドルを取得します。
    static HWND GetHandle()
    {
        return Get().handle;
    }
    /// ウィンドウのサイズをピクセル単位で取得します。
    static DirectX::XMINT2 GetSize()
    {
        RECT clientRect = {};
        GetClientRect(Get().handle, &clientRect);

        return DirectX::XMINT2(clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
    }
    /// ウィンドウのサイズをピクセル単位で設定します。
    static void SetSize(int width, int height)
    {
        RECT windowRect = {};
        RECT clientRect = {};
        GetWindowRect(Get().handle, &windowRect);
        GetClientRect(Get().handle, &clientRect);

        int w = (windowRect.right - windowRect.left) - (clientRect.right - clientRect.left) + width;
        int h = (windowRect.bottom - windowRect.top) - (clientRect.bottom - clientRect.top) + height;
        int x = (GetSystemMetrics(SM_CXSCREEN) - w) / 2;
        int y = (GetSystemMetrics(SM_CYSCREEN) - h) / 2;

        SetWindowPos(Get().handle, nullptr, x, y, w, h, SWP_FRAMECHANGED);
    }
    /// ウィンドウのタイトルを取得します。
    static wchar_t* const GetTitle()
    {
        wchar_t* title = nullptr;
        GetWindowTextW(Get().handle, title, GetWindowTextLengthW(Get().handle));
        return title;
    }
    /// ウィンドウのタイトルを設定します。
    static void SetTitle(const wchar_t* const title)
    {
        SetWindowTextW(Get().handle, title);
    }
    /// ウィンドウモードを取得します。
    static Mode GetMode()
    {
        return Get().mode;
    }
    /// ウィンドウモードを設定します。
    static void SetMode(Mode mode)
    {
        if (Get().mode == mode)
            return;

        Get().mode = mode;

        static DirectX::XMINT2 size = GetSize();
        if (mode == Mode::FullScreen)
        {
            size = GetSize();
            int w = GetSystemMetrics(SM_CXSCREEN);
            int h = GetSystemMetrics(SM_CYSCREEN);
            SetWindowLongPtrW(Get().handle, GWL_STYLE, WS_VISIBLE | WS_POPUP);
            SetWindowPos(Get().handle, HWND_TOP, 0, 0, w, h, SWP_FRAMECHANGED);
        }
        else
        {
            SetWindowLongPtrW(Get().handle, GWL_STYLE, WS_VISIBLE | WS_OVERLAPPEDWINDOW);
            SetWindowPos(Get().handle, nullptr, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);
            SetSize(size.x, size.y);
        }
    }
    /// ウィンドウモードを切り替えます。
    static void ToggleMode()
    {
        if (Get().mode == Mode::Windowed)
            SetMode(Mode::FullScreen);
        else
            SetMode(Mode::Windowed);
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

        PostMessageW(Get().handle, WM_APP, 0, 0);

        if (GetSize().x <= 0.0f || GetSize().y <= 0.0f)
            std::this_thread::sleep_for(std::chrono::milliseconds(100));

        return true;
    }
    /// ウィンドウプロシージャを追加します。
    static void AddProcedure(Proceedable* const procedure)
    {
        Get().procedures.push_back(procedure);
    }
    /// ウィンドウプロシージャを削除します。
    static void RemoveProcedure(Proceedable* const procedure)
    {
        Get().procedures.remove(procedure);
    }

private:
    struct Property
    {
        const wchar_t* className = L"XLibrary11";
        HWND handle;
        Mode mode = Mode::Windowed;
        std::list<Proceedable*> procedures;
    };

    static Property& Get()
    {
        static std::unique_ptr<Property> prop;

        if (prop == nullptr)
        {
            prop.reset(new Property());

            InitializeApplication();

            HINSTANCE instance = GetModuleHandleW(nullptr);

            WNDCLASSW windowClass = {};
            windowClass.lpfnWndProc = ProceedMessage;
            windowClass.hInstance = instance;
            windowClass.hCursor = (HCURSOR)LoadImageW(nullptr, MAKEINTRESOURCEW(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_SHARED);
            windowClass.lpszClassName = Get().className;
            RegisterClassW(&windowClass);

            Get().handle = CreateWindowW(Get().className, Get().className, WS_OVERLAPPEDWINDOW, 0, 0, 0, 0, nullptr, nullptr, instance, nullptr);

            SetSize(640, 480);

            ShowWindow(Get().handle, SW_SHOWNORMAL);
        }

        return *prop;
    }
    static LRESULT CALLBACK ProceedMessage(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
    {
        for (Proceedable* procedure : Get().procedures)
        {
            procedure->OnProceedMessage(window, message, wParam, lParam);
        }

        if (message == WM_DESTROY)
            PostQuitMessage(0);

        return DefWindowProcW(window, message, wParam, lParam);
    }
};
/// 入力を受け取れます。
class Input
{
public:
    /// キーが押されているかを取得します。VK_CODEにはAキーなら'A'を、スペースキーならVK_SPACEを指定します。詳しくは[こちら](https://docs.microsoft.com/ja-jp/windows/desktop/inputdev/virtual-key-codes)を参照してください。
    static bool GetKey(int VK_CODE)
    {
        return Get().keyState[VK_CODE] & 0x80;
    }
    /// キーが離された瞬間かを取得します。
    static bool GetKeyUp(int VK_CODE)
    {
        return !(Get().keyState[VK_CODE] & 0x80) && (Get().prevKeyState[VK_CODE] & 0x80);
    }
    /// キーが押された瞬間かを取得します。
    static bool GetKeyDown(int VK_CODE)
    {
        return (Get().keyState[VK_CODE] & 0x80) && !(Get().prevKeyState[VK_CODE] & 0x80);
    }
    /// マウスの座標を取得します。
    static Float2 GetMousePosition()
    {
        return Get().mousePosition;
    }
    /// マウスの座標を設定します。
    static void SetMousePosition(float x, float y)
    {
        if (GetActiveWindow() != Window::GetHandle())
            return;

        POINT point = {};
        point.x = int(x + Window::GetSize().x / 2);
        point.y = int(-y + Window::GetSize().y / 2);
        ClientToScreen(Window::GetHandle(), &point);
        SetCursorPos(point.x, point.y);

        Get().mousePosition.x = x;
        Get().mousePosition.y = y;
    }
    /// マウスホイールの回転量を取得します。
    static int GetMouseWheel()
    {
        return Get().mouseWheel;
    }
    /// マウスカーソルの表示を切り替えます。
    static void SetShowCursor(bool isShowCursor)
    {
        if (Get().isShowCursor == isShowCursor)
            return;

        Get().isShowCursor = isShowCursor;
        ShowCursor(isShowCursor);
    }
    /// ゲームパッドのボタンが押されているかを取得します。idには0から3を指定します。XINPUT_GAMEPAD_CODEは[こちら](https://docs.microsoft.com/ja-jp/windows/desktop/api/xinput/ns-xinput-_xinput_gamepad)を参照してください。
    static bool GetPadButton(int id, int XINPUT_GAMEPAD_CODE)
    {
        return Get().padState[id].Gamepad.wButtons & XINPUT_GAMEPAD_CODE;
    }
    /// ゲームパッドのボタンが離された瞬間かを取得します。
    static bool GetPadButtonUp(int id, int XINPUT_GAMEPAD_CODE)
    {
        return !(Get().padState[id].Gamepad.wButtons & XINPUT_GAMEPAD_CODE) && (Get().prevPadState[id].Gamepad.wButtons & XINPUT_GAMEPAD_CODE);
    }
    /// ゲームパッドのボタンが押された瞬間かを取得します。
    static bool GetPadButtonDown(int id, int XINPUT_GAMEPAD_CODE)
    {
        return (Get().padState[id].Gamepad.wButtons & XINPUT_GAMEPAD_CODE) && !(Get().prevPadState[id].Gamepad.wButtons & XINPUT_GAMEPAD_CODE);
    }
    /// ゲームパッドの左トリガーの値を取得します。
    static float GetPadLeftTrigger(int id)
    {
        return float(Get().padState[id].Gamepad.bLeftTrigger) / std::numeric_limits<BYTE>::max();
    }
    /// ゲームパッドの右トリガーの値を取得します。
    static float GetPadRightTrigger(int id)
    {
        return float(Get().padState[id].Gamepad.bRightTrigger) / std::numeric_limits<BYTE>::max();
    }
    /// ゲームパッドの左スティックの値を取得します。
    static Float2 GetPadLeftThumb(int id)
    {
        static const float deadZone = float(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) / std::numeric_limits<SHORT>::max();

        Float2 value;
        value.x = float(Get().padState[id].Gamepad.sThumbLX) / std::numeric_limits<SHORT>::max();
        value.y = float(Get().padState[id].Gamepad.sThumbLY) / std::numeric_limits<SHORT>::max();

        if (-deadZone < value.x && value.x < deadZone)
            value.x = 0.0f;
        if (-deadZone < value.y && value.y < deadZone)
            value.y = 0.0f;

        return value;
    }
    /// ゲームパッドの右スティックの値を取得します。
    static Float2 GetPadRightThumb(int id)
    {
        static const float deadZone = float(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) / std::numeric_limits<SHORT>::max();

        Float2 value;
        value.x = float(Get().padState[id].Gamepad.sThumbRX) / std::numeric_limits<SHORT>::max();
        value.y = float(Get().padState[id].Gamepad.sThumbRY) / std::numeric_limits<SHORT>::max();

        if (-deadZone < value.x && value.x < deadZone)
            value.x = 0.0f;
        if (-deadZone < value.y && value.y < deadZone)
            value.y = 0.0f;

        return value;
    }
    static void Update()
    {
        Get().mouseWheel = 0;

        POINT point = {};
        GetCursorPos(&point);
        ScreenToClient(Window::GetHandle(), &point);

        Get().mousePosition.x = float(point.x - Window::GetSize().x / 2);
        Get().mousePosition.y = float(-point.y + Window::GetSize().y / 2);

        for (int i = 0; i < 256; i++)
        {
            Get().prevKeyState[i] = Get().keyState[i];
        }

        GetKeyboardState(Get().keyState);

        for (int i = 0; i < 4; i++)
        {
            Get().prevPadState[i] = Get().padState[i];
            XInputGetState(i, &Get().padState[i]);
        }
    }

private:
    struct Property : public Window::Proceedable
    {
        Float2 mousePosition;
        int mouseWheel = 0;
        BYTE prevKeyState[256];
        BYTE keyState[256];
        bool isShowCursor = true;
        XINPUT_STATE prevPadState[4];
        XINPUT_STATE padState[4];

        void OnProceedMessage(HWND, UINT message, WPARAM wParam, LPARAM) override
        {
            if (message == WM_MOUSEWHEEL)
            {
                mouseWheel = -GET_WHEEL_DELTA_WPARAM(wParam);
            }
        }
    };

    static Property& Get()
    {
        static std::unique_ptr<Property> prop;

        if (prop == nullptr)
        {
            prop.reset(new Property());

            InitializeApplication();
            Window::AddProcedure(&Get());

            Update();
        }

        return *prop;
    }
};
/// DirectX 11の機能にアクセスできます。
class Graphics
{
public:
    /// ID3D11Deviceを取得します。
    static ID3D11Device& GetDevice3D()
    {
        return *Get().device3D.Get();
    }
    /// ID3D11DeviceContextを取得します。
    static ID3D11DeviceContext& GetContext3D()
    {
        return *Get().context3D.Get();
    }
    /// ID2D1Deviceを取得します。
    static ID2D1Device& GetDevice2D()
    {
        return *Get().device2D.Get();
    }
    /// ID2D1DeviceContextを取得します。
    static ID2D1DeviceContext& GetContext2D()
    {
        return *Get().context2D.Get();
    }
    /// IDXGISwapChainを取得します。
    static IDXGISwapChain& GetSwapChain()
    {
        return *Get().swapChain.Get();
    }
    /// IWICImagingFactoryを取得します。
    static IWICImagingFactory& GetTextureFactory()
    {
        return *Get().textureFactory.Get();
    }
    /// IDWriteFactoryを取得します。
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
class LightManager
{
public:
    struct Constant
    {
        int type;
        Float3 position;
        Float3 direction;
        float range;
        Float4 color;
    };

    static const int limit = 100;

    static void AddLight(Constant* const constant)
    {
        Get().lights.push_back(constant);
    }
    static void RemoveLight(Constant* const constant)
    {
        std::vector<Constant*>& v = Get().lights;
        v.erase(remove(v.begin(), v.end(), constant), v.end());
    }
    static void Update()
    {
        for (size_t i = 0; i < limit; i++)
        {
            if (Get().lights.size() > i)
                Get().constant[i] = *Get().lights[i];
            else
                Get().constant[i].type = -1;
        }

        Graphics::GetContext3D().UpdateSubresource(Get().constantBuffer.Get(), 0, nullptr, Get().constant, 0, 0);
        Graphics::GetContext3D().VSSetConstantBuffers(1, 1, Get().constantBuffer.GetAddressOf());
        Graphics::GetContext3D().PSSetConstantBuffers(1, 1, Get().constantBuffer.GetAddressOf());
    }

private:
    struct Property
    {
        std::vector<Constant*> lights;
        Constant constant[limit];
        ComPtr<ID3D11Buffer> constantBuffer = nullptr;
    };

    static Property& Get()
    {
        static std::unique_ptr<Property> prop;

        if (prop == nullptr)
        {
            prop.reset(new Property());

            D3D11_BUFFER_DESC constantBufferDesc = {};
            constantBufferDesc.ByteWidth = sizeof(Constant) * limit;
            constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
            constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
            Graphics::GetDevice3D().CreateBuffer(&constantBufferDesc, nullptr, Get().constantBuffer.GetAddressOf());
        }

        return *prop;
    }
};
/// IDirectSound8を取得できます。
class SoundManager
{
public:
    /// IDirectSound8を取得します。
    static IDirectSound8& GetDevice()
    {
        return *Get().device.Get();
    }

private:
    struct Property
    {
        ComPtr<IDirectSound8> device = nullptr;
    };

    static Property& Get()
    {
        static std::unique_ptr<Property> prop;

        if (prop == nullptr)
        {
            prop.reset(new Property());

            InitializeApplication();

            DirectSoundCreate8(nullptr, &Get().device, nullptr);

            Get().device->SetCooperativeLevel(Window::GetHandle(), DSSCL_NORMAL);

            MFStartup(MF_VERSION);
        }

        return *prop;
    }
};
/// 時間に関する情報を取得できます。
class Timer
{
public:
    /// アプリケーションが起動してからの時間を取得します。
    static float GetTime()
    {
        return Get().time;
    }
    /// 前のフレームからの時間を取得します。
    static float GetDeltaTime()
    {
        return Get().deltaTime;
    }
    /// フレームレートを取得します。
    static int GetFrameRate()
    {
        return Get().frameRate;
    }
    static void Update()
    {
        std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
        Get().deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - Get().prev).count() / 1000.0f;
        Get().prev = now;

        Get().time = std::chrono::duration_cast<std::chrono::milliseconds>(now - Get().begin).count() / 1000.0f;

        Get().frameCount++;
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - Get().second).count() >= 1000)
        {
            Get().frameRate = Get().frameCount;
            Get().frameCount = 0;
            Get().second = now;
        }
    }

private:
    struct Property
    {
        float time = 0.0f;
        float deltaTime = 0.0f;
        int frameRate = 0;
        int frameCount = 0;
        std::chrono::high_resolution_clock::time_point begin;
        std::chrono::high_resolution_clock::time_point prev;
        std::chrono::high_resolution_clock::time_point second;
    };

    static Property& Get()
    {
        static std::unique_ptr<Property> prop;

        if (prop == nullptr)
        {
            prop.reset(new Property());

            InitializeApplication();

            Get().begin = std::chrono::high_resolution_clock::now();
            Get().prev = std::chrono::high_resolution_clock::now();
            Get().second = std::chrono::high_resolution_clock::now();
        }

        return *prop;
    }
};
/// 乱数を使えます。
class Random
{
public:
    /// 乱数のシードを設定します。
    static void SetSeed(int seed)
    {
        Get().mt.seed(seed);
    }
    /// 0.0から1.0の小数の乱数を取得します。
    static float GetValue()
    {
        std::uniform_real_distribution<float> range(0.0f, 1.0f);

        return range(Get().mt);
    }
    /// 整数の乱数を最小値と最大値を指定して取得します。
    static int Range(int min, int max)
    {
        std::uniform_int_distribution<int> range(min, max);

        return range(Get().mt);
    }
    /// 小数の乱数を最小値と最大値を指定して取得します。
    static float Range(float min, float max)
    {
        std::uniform_real_distribution<float> range(min, max);

        return range(Get().mt);
    }

private:
    struct Property
    {
        std::mt19937 mt;
    };

    static Property& Get()
    {
        static std::unique_ptr<Property> prop;

        if (prop == nullptr)
        {
            prop.reset(new Property());

            InitializeApplication();

            std::random_device device;
            Get().mt.seed(device());
        }

        return *prop;
    }
};


class Texture
{
public:
    Texture()
    {
        InitializeApplication();
    }
    Texture(const wchar_t* const filePath)
    {
        InitializeApplication();
        Load(filePath);
    }
    Texture(const BYTE* const buffer, int width, int height)
    {
        InitializeApplication();
        Create(buffer, width, height);
    }
    ~Texture()
    {
    }
    void Load(const wchar_t* const filePath)
    {
        ComPtr<IWICBitmapDecoder> decoder = nullptr;

        HRESULT result = Graphics::GetTextureFactory().CreateDecoderFromFilename(filePath, 0, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &decoder);

        if (decoder == nullptr)
            Utility::Alert(result);

        ComPtr<IWICBitmapFrameDecode> frame = nullptr;
        decoder->GetFrame(0, &frame);
        UINT width, height;
        frame->GetSize(&width, &height);

        WICPixelFormatGUID pixelFormat;
        frame->GetPixelFormat(&pixelFormat);
        std::unique_ptr<BYTE[]> buffer(new BYTE[width * height * 4]);

        if (pixelFormat != GUID_WICPixelFormat32bppBGRA)
        {
            ComPtr<IWICFormatConverter> formatConverter = nullptr;
            Graphics::GetTextureFactory().CreateFormatConverter(&formatConverter);

            formatConverter->Initialize(frame.Get(), GUID_WICPixelFormat32bppBGRA, WICBitmapDitherTypeErrorDiffusion, 0, 0, WICBitmapPaletteTypeCustom);

            formatConverter->CopyPixels(0, width * 4, width * height * 4, buffer.get());
        }
        else
        {
            frame->CopyPixels(0, width * 4, width * height * 4, buffer.get());
        }

        Create(buffer.get(), width, height);
    }
    void Create(const BYTE* const buffer, int width, int height)
    {
        _size = DirectX::XMINT2(width, height);

        _texture.Reset();
        D3D11_TEXTURE2D_DESC textureDesc = {};
        textureDesc.Width = width;
        textureDesc.Height = height;
        textureDesc.MipLevels = 1;
        textureDesc.ArraySize = 1;
        textureDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        textureDesc.SampleDesc.Count = 1;
        textureDesc.SampleDesc.Quality = 0;
        textureDesc.Usage = D3D11_USAGE_DEFAULT;
        textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
        textureDesc.CPUAccessFlags = 0;
        textureDesc.MiscFlags = 0;

        D3D11_SUBRESOURCE_DATA textureSubresourceData = {};
        textureSubresourceData.pSysMem = buffer;
        textureSubresourceData.SysMemPitch = width * 4;
        textureSubresourceData.SysMemSlicePitch = width * height * 4;
        Graphics::GetDevice3D().CreateTexture2D(&textureDesc, &textureSubresourceData, _texture.GetAddressOf());

        _shaderResourceView.Reset();
        D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc = {};
        shaderResourceViewDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        shaderResourceViewDesc.Texture2D.MipLevels = 1;
        Graphics::GetDevice3D().CreateShaderResourceView(_texture.Get(), &shaderResourceViewDesc, _shaderResourceView.GetAddressOf());

        _samplerState.Reset();
        D3D11_SAMPLER_DESC samplerDesc = {};
        samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
        samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.MipLODBias = 0.0f;
        samplerDesc.MaxAnisotropy = 1;
        samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
        samplerDesc.BorderColor[0] = 0.0f;
        samplerDesc.BorderColor[1] = 0.0f;
        samplerDesc.BorderColor[2] = 0.0f;
        samplerDesc.BorderColor[3] = 0.0f;
        samplerDesc.MinLOD = 0.0f;
        samplerDesc.MaxLOD = std::numeric_limits<float>::max();
        Graphics::GetDevice3D().CreateSamplerState(&samplerDesc, _samplerState.GetAddressOf());
    }
    DirectX::XMINT2 GetSize() const
    {
        return _size;
    }
    void Attach(int slot)
    {
        if (_texture == nullptr)
            return;

        Graphics::GetContext3D().PSSetShaderResources(slot, 1, _shaderResourceView.GetAddressOf());
        Graphics::GetContext3D().PSSetSamplers(slot, 1, _samplerState.GetAddressOf());
    }
    ID3D11Texture2D& GetInterface()
    {
        return *_texture.Get();
    }

private:
    DirectX::XMINT2 _size;
    ComPtr<ID3D11Texture2D> _texture = nullptr;
    ComPtr<ID3D11ShaderResourceView> _shaderResourceView = nullptr;
    ComPtr<ID3D11SamplerState> _samplerState = nullptr;
};
template <class T>
class CBuffer
{
public:
    CBuffer()
    {
        data = std::make_unique<T>();

        buffer.Reset();
        D3D11_BUFFER_DESC constantBufferDesc = {};
        constantBufferDesc.ByteWidth = sizeof(T);
        constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
        constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        HRESULT result = Graphics::GetDevice3D().CreateBuffer(&constantBufferDesc, nullptr, buffer.GetAddressOf());

        if (buffer == nullptr)
            Utility::Alert(result);
    }
    ~CBuffer()
    {
    }
    T& GetData()
    {
        return *data.get();
    }
    void Attach(int slot)
    {
        Graphics::GetContext3D().UpdateSubresource(buffer.Get(), 0, nullptr, data.get(), 0, 0);
        Graphics::GetContext3D().VSSetConstantBuffers(slot, 1, buffer.GetAddressOf());
        Graphics::GetContext3D().PSSetConstantBuffers(slot, 1, buffer.GetAddressOf());
    }

private:
    ComPtr<ID3D11Buffer> buffer = nullptr;
    std::unique_ptr<T> data;
};
class Material
{
public:
    Material()
    {
        InitializeApplication();
    }
    Material(const wchar_t* const filePath)
    {
        InitializeApplication();
        Load(filePath);
    }
    Material(const std::string& source)
    {
        InitializeApplication();
        Create(source);
    }
    ~Material()
    {
    }
    void Load(const wchar_t* const filePath)
    {
        std::ifstream sourceFile(filePath);
        std::istreambuf_iterator<char> iterator(sourceFile);
        std::istreambuf_iterator<char> last;
        std::string source(iterator, last);
        sourceFile.close();

        Create(source);
    }
    void Create(const std::string& source)
    {
        _vertexShader.Reset();
        ComPtr<ID3DBlob> vertexShaderBlob = nullptr;
        CompileShader(source, "VS", "vs_5_0", vertexShaderBlob.GetAddressOf());
        Graphics::GetDevice3D().CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), nullptr, _vertexShader.GetAddressOf());

        _pixelShader.Reset();
        ComPtr<ID3DBlob> pixelShaderBlob = nullptr;
        CompileShader(source, "PS", "ps_5_0", pixelShaderBlob.GetAddressOf());
        Graphics::GetDevice3D().CreatePixelShader(pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize(), nullptr, _pixelShader.GetAddressOf());

        _inputLayout.Reset();
        std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDesc;
        inputElementDesc.push_back({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 });
        inputElementDesc.push_back({ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 });
        inputElementDesc.push_back({ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 });
        inputElementDesc.push_back({ "BLENDINDICES", 0, DXGI_FORMAT_R32G32B32A32_UINT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 });
        inputElementDesc.push_back({ "BLENDINDICES", 1, DXGI_FORMAT_R32G32B32A32_UINT, 0, 48, D3D11_INPUT_PER_VERTEX_DATA, 0 });
        inputElementDesc.push_back({ "BLENDWEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 64, D3D11_INPUT_PER_VERTEX_DATA, 0 });
        inputElementDesc.push_back({ "BLENDWEIGHT", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 80, D3D11_INPUT_PER_VERTEX_DATA, 0 });

        Graphics::GetDevice3D().CreateInputLayout(inputElementDesc.data(), (UINT)inputElementDesc.size(), vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), _inputLayout.GetAddressOf());
    }
    void Attach()
    {
        if (_vertexShader != nullptr)
            Graphics::GetContext3D().VSSetShader(_vertexShader.Get(), nullptr, 0);

        if (_pixelShader != nullptr)
            Graphics::GetContext3D().PSSetShader(_pixelShader.Get(), nullptr, 0);

        if (_inputLayout != nullptr)
            Graphics::GetContext3D().IASetInputLayout(_inputLayout.Get());
    }
    static Material GetDiffuseMaterial()
    {
        static std::unique_ptr<Material> diffuseMaterial;

        if (diffuseMaterial == nullptr)
        {
            diffuseMaterial.reset(new Material(
                "struct Vertex"
                "{"
                "    float4 position : POSITION;"
                "    float3 normal : NORMAL;"
                "    float2 uv : TEXCOORD;"
                "};"
                "struct Pixel"
                "{"
                "    float4 position : SV_POSITION;"
                "    float3 normal : NORMAL;"
                "    float2 uv : TEXCOORD0;"
                "    float3 worldPosition : TEXCOORD1;"
                "};"
                "struct Light"
                "{"
                "    int type;"
                "    float3 position;"
                "    float3 direction;"
                "    float range;"
                "    float4 color;"
                "};"
                "cbuffer Camera : register(b0)"
                "{"
                "    matrix view;"
                "    matrix projection;"
                "};"
                "cbuffer Light : register(b1)"
                "{"
                "    Light lights[100];"
                "};"
                "cbuffer Object : register(b5)"
                "{"
                "    matrix world;"
                "};"
                "Texture2D texture0 : register(t0);"
                "SamplerState sampler0 : register(s0);"
                "Pixel VS(Vertex vertex)"
                "{"
                "    Pixel output;"
                "    output.position = mul(vertex.position, world);"
                "    output.position = mul(output.position, view);"
                "    output.position = mul(output.position, projection);"
                "    output.normal = mul(vertex.normal, (float3x3)world);"
                "    output.uv = vertex.uv;"
                "    output.worldPosition = mul(vertex.position, world).xyz;"
                "    return output;"
                "}"
                "float4 PS(Pixel pixel) : SV_TARGET"
                "{"
                "    float3 diffuseColor = texture0.Sample(sampler0, pixel.uv).rgb;"
                "    float3 normal = normalize(pixel.normal);"
                "    float3 lightColor = float3(0.0, 0.0, 0.0);"
                "    for (int i = 0; i < 100; i++)"
                "    {"
                "        if (lights[i].type == 0)"
                "        {"
                "            float shade = max(0, dot(-lights[i].direction, normal));"
                "            lightColor += lights[i].color.xyz * shade;"
                "        }"
                "        if (lights[i].type == 1)"
                "        {"
                "            float3 lightDirection = normalize(lights[i].position.xyz - pixel.worldPosition);"
                "            float shade = max(0, dot(normal, lightDirection));"
                "            float attenuation = max(0, (lights[i].range - length(lights[i].position.xyz - pixel.worldPosition)) / lights[i].range);"
                "            lightColor += lights[i].color.xyz * shade * attenuation;"
                "        }"
                "    }"
                "    float3 ambientColor = float3(1.0, 1.0, 1.0) * 0.1;"
                "    return float4(diffuseColor * (lightColor + ambientColor), 1);"
                "}"
            ));
        }

        return *diffuseMaterial.get();
    }
    static Material GetSpriteMaterial()
    {
        static std::unique_ptr<Material> spriteMaterial;

        if (spriteMaterial == nullptr)
        {
            spriteMaterial.reset(new Material(
                "cbuffer Camera : register(b0)"
                "{"
                "    matrix view;"
                "    matrix projection;"
                "};"
                "cbuffer Object : register(b5)"
                "{"
                "    matrix world;"
                "};"
                "cbuffer Sprite : register(b6)"
                "{"
                "    float4 color;"
                "};"
                "Texture2D texture0 : register(t0);"
                "SamplerState sampler0 : register(s0);"
                "struct Vertex"
                "{"
                "    float4 position : POSITION;"
                "    float2 uv : TEXCOORD;"
                "};"
                "struct Pixel"
                "{"
                "    float4 position : SV_POSITION;"
                "    float2 uv : TEXCOORD;"
                "};"
                "Pixel VS(Vertex vertex)"
                "{"
                "    Pixel output;"
                "    output.position = mul(vertex.position, world);"
                "    output.position = mul(output.position, view);"
                "    output.position = mul(output.position, projection);"
                "    output.uv = vertex.uv;"
                "    return output;"
                "}"
                "float4 PS(Pixel pixel) : SV_TARGET"
                "{"
                "    float4 textureColor = texture0.Sample(sampler0, pixel.uv);"
                "    if (textureColor.a <= 0)"
                "        discard;"
                "    return textureColor * color;"
                "}"
            ));
        }

        return *spriteMaterial.get();
    }

private:
    ComPtr<ID3D11VertexShader> _vertexShader = nullptr;
    ComPtr<ID3D11PixelShader> _pixelShader = nullptr;
    ComPtr<ID3D11InputLayout> _inputLayout = nullptr;

    static void CompileShader(const std::string& source, const char* const entryPoint, const char* const shaderModel, ID3DBlob** out)
    {
        UINT shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(_DEBUG)
        shaderFlags |= D3DCOMPILE_DEBUG;
#endif

        ComPtr<ID3DBlob> errorBlob = nullptr;
        D3DCompile(source.c_str(), source.length(), nullptr, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint, shaderModel, shaderFlags, 0, out, errorBlob.GetAddressOf());

        if (errorBlob != nullptr)
        {
            OutputDebugStringA((char*)errorBlob->GetBufferPointer());
            MessageBoxA(Window::GetHandle(), (char*)errorBlob->GetBufferPointer(), "Shader error", MB_ICONERROR | MB_OK);
            std::exit(EXIT_FAILURE);
        }
    }
};
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
        _cbuffer.GetData().projection = DirectX::XMMatrixTranspose(
            DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(fieldOfView), aspectRatio, nearClip, farClip)
        );
    }
    void SetupOrthographic(float size = (float)Window::GetSize().y, bool isAdjust = true, float nearClip = std::numeric_limits<float>::lowest(), float farClip = std::numeric_limits<float>::max())
    {
        _is3D = false;
        _size = size;
        _isAdjust = isAdjust;
        _nearClip = nearClip;
        _farClip = farClip;
        float aspectRatio = float(Window::GetSize().x) / Window::GetSize().y;
        _cbuffer.GetData().projection = DirectX::XMMatrixTranspose(
            DirectX::XMMatrixOrthographicLH(size * aspectRatio, size, nearClip, farClip)
        );
    }
    void Update()
    {
        _cbuffer.GetData().view = DirectX::XMMatrixTranspose(
            DirectX::XMMatrixInverse(
                nullptr,
                DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(angles.x)) *
                DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(angles.z)) *
                DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(angles.y)) *
                DirectX::XMMatrixTranslation(position.x, position.y, position.z)
            )
        );

        _cbuffer.Attach(0);

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
    CBuffer<Constant> _cbuffer;
    ComPtr<ID3D11RenderTargetView> _renderTargetView = nullptr;
    ComPtr<ID3D11DepthStencilView> _depthStencilView = nullptr;
    ComPtr<ID3D11Texture2D> _renderTexture = nullptr;
    ComPtr<ID3D11Texture2D> _depthTexture = nullptr;

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
class Light
{
public:
    enum class Type : int
    {
        Directional,
        Point,
    };

    Type type;
    Float3 position;
    Float3 angles;
    Float3 color;
    float range;
    float intensity;

    Light()
    {
        type = Type::Directional;
        color = Float3(1.0f, 1.0f, 1.0f);
        range = 5.0f;
        intensity = 1.0f;

        LightManager::AddLight(&_constant);
    }
    ~Light()
    {
        LightManager::RemoveLight(&_constant);
    }
    void Update()
    {
        _constant.direction = Float3(
            cosf(XMConvertToRadians(angles.x)) * cosf(XMConvertToRadians(angles.y + 90.0f)),
            sinf(XMConvertToRadians(angles.x)),
            cosf(XMConvertToRadians(angles.x)) * sinf(XMConvertToRadians(angles.y + 90.0f))
        );

        _constant.type = (int)type;
        _constant.position = position;
        _constant.color = color * intensity;
        _constant.range = range;
    }

private:
    LightManager::Constant _constant;
};
class Mesh
{
public:
    Float3 position;
    Float3 angles;
    Float3 scale;
    std::vector<Vertex> vertices;
    std::vector<UINT> indices;
    Material material = Material::GetDiffuseMaterial();

    Mesh()
    {
        InitializeApplication();

        position = Float3(0.0f, 0.0f, 0.0f);
        angles = Float3(0.0f, 0.0f, 0.0f);
        scale = Float3(1.0f, 1.0f, 1.0f);

        SetCullingMode(D3D11_CULL_BACK);

        CreateCube();
    }
    ~Mesh()
    {
    }
    void CreatePlane(Float2 size, Float3 offset = Float3(0.0f, 0.0f, 0.0f), bool shouldClear = true, Float3 leftDirection = Float3(1.0f, 0.0f, 0.0f), Float3 upDirection = Float3(0.0f, 1.0f, 0.0f), Float3 forwardDirection = Float3(0.0f, 0.0f, 1.0f))
    {
        if (shouldClear)
        {
            vertices.clear();
            indices.clear();
        }

        size /= 2.0f;

        leftDirection = DirectX::XMVector3Normalize(leftDirection);
        upDirection = DirectX::XMVector3Normalize(upDirection);
        forwardDirection = DirectX::XMVector3Normalize(forwardDirection);

        vertices.push_back(Vertex(leftDirection * -size.x + upDirection * size.y + offset, -forwardDirection, Float2(0.0f, 0.0f)));
        vertices.push_back(Vertex(leftDirection * size.x + upDirection * size.y + offset, -forwardDirection, Float2(1.0f, 0.0f)));
        vertices.push_back(Vertex(leftDirection * -size.x + upDirection * -size.y + offset, -forwardDirection, Float2(0.0f, 1.0f)));
        vertices.push_back(Vertex(leftDirection * size.x + upDirection * -size.y + offset, -forwardDirection, Float2(1.0f, 1.0f)));

        int indexOffset = (int)vertices.size() - 4;
        indices.push_back(indexOffset + 0);
        indices.push_back(indexOffset + 1);
        indices.push_back(indexOffset + 2);
        indices.push_back(indexOffset + 3);
        indices.push_back(indexOffset + 2);
        indices.push_back(indexOffset + 1);

        if (shouldClear)
            Apply();
    }
    void CreateCube(Float3 size = Float3(1.0f, 1.0f, 1.0f), bool shouldClear = true)
    {
        if (shouldClear)
        {
            vertices.clear();
            indices.clear();
        }

        CreatePlane(Float2(size.x, size.y), Float3(0.0f, 0.0f, -size.z / 2.0f), false, Float3(1.0f, 0.0f, 0.0f), Float3(0.0f, 1.0f, 0.0f), Float3(0.0f, 0.0f, 1.0f));	// front
        CreatePlane(Float2(size.x, size.y), Float3(0.0f, 0.0f, size.z / 2.0f), false, Float3(-1.0f, 0.0f, 0.0f), Float3(0.0f, 1.0f, 0.0f), Float3(0.0f, 0.0f, -1.0f));	// back
        CreatePlane(Float2(size.z, size.y), Float3(size.x / 2.0f, 0.0f, 0.0f), false, Float3(0.0f, 0.0f, 1.0f), Float3(0.0f, 1.0f, 0.0f), Float3(-1.0f, 0.0f, 0.0f));	// left
        CreatePlane(Float2(size.z, size.y), Float3(-size.x / 2.0f, 0.0f, 0.0f), false, Float3(0.0f, 0.0f, -1.0f), Float3(0.0f, 1.0f, 0.0f), Float3(1.0f, 0.0f, 0.0f));	// right
        CreatePlane(Float2(size.x, size.z), Float3(0.0f, size.y / 2.0f, 0.0f), false, Float3(1.0f, 0.0f, 0.0f), Float3(0.0f, 0.0f, 1.0f), Float3(0.0f, -1.0f, 0.0f));	// up
        CreatePlane(Float2(size.x, size.z), Float3(0.0f, -size.y / 2.0f, 0.0f), false, Float3(1.0f, 0.0f, 0.0f), Float3(0.0f, 0.0f, -1.0f), Float3(0.0f, 1.0f, 0.0f));	// down

        if (shouldClear)
            Apply();
    }
    void CreateSphere(float diameter = 1.0f, int tessellation = 10, bool shouldClear = true)
    {
        if (shouldClear)
        {
            vertices.clear();
            indices.clear();
        }

        int verticalSegments = tessellation;
        int horizontalSegments = tessellation * 2;

        float radius = diameter / 2;

        for (int i = 0; i <= verticalSegments; i++)
        {
            float v = float(i) / verticalSegments;

            float latitude = (i * XM_PI / verticalSegments) - XM_PIDIV2;
            float dy, dxz;

            XMScalarSinCos(&dy, &dxz, latitude);

            for (int j = 0; j <= horizontalSegments; j++)
            {
                float u = float(j) / horizontalSegments;

                float longitude = j * XM_2PI / horizontalSegments + XM_PI;
                float dx, dz;

                XMScalarSinCos(&dx, &dz, longitude);

                dx *= dxz;
                dz *= dxz;

                Float3 normal(dx, dy, dz);
                Float2 uv(u, v);

                vertices.push_back(Vertex(XMVectorScale(-normal, radius), -normal, uv));
            }
        }

        int stride = horizontalSegments + 1;

        for (int i = 0; i < verticalSegments; i++)
        {
            for (int j = 0; j <= horizontalSegments; j++)
            {
                int nextI = i + 1;
                int nextJ = (j + 1) % stride;

                indices.push_back(i * stride + j);
                indices.push_back(nextI * stride + j);
                indices.push_back(i * stride + nextJ);

                indices.push_back(i * stride + nextJ);
                indices.push_back(nextI * stride + j);
                indices.push_back(nextI * stride + nextJ);
            }
        }

        if (shouldClear)
            Apply();
    }
    void SetTexture(Texture* const texture)
    {
        _texture = texture;
    }
    void SetCullingMode(D3D11_CULL_MODE cullingMode)
    {
        D3D11_RASTERIZER_DESC rasterizerDesc = {};
        rasterizerDesc.FillMode = D3D11_FILL_SOLID;
        rasterizerDesc.CullMode = cullingMode;
        _rasterizerState.Reset();
        Graphics::GetDevice3D().CreateRasterizerState(&rasterizerDesc, _rasterizerState.GetAddressOf());
    }
    void Apply()
    {
        _vertexBuffer.Reset();
        if (vertices.size() > 0)
        {
            D3D11_BUFFER_DESC vertexBufferDesc = {};
            vertexBufferDesc.ByteWidth = sizeof(Vertex) * UINT(vertices.size());
            vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
            vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
            D3D11_SUBRESOURCE_DATA vertexSubresourceData = {};
            vertexSubresourceData.pSysMem = vertices.data();
            Graphics::GetDevice3D().CreateBuffer(&vertexBufferDesc, &vertexSubresourceData, _vertexBuffer.GetAddressOf());
        }

        _indexBuffer.Reset();
        if (indices.size() > 0)
        {
            D3D11_BUFFER_DESC indexBufferDesc = {};
            indexBufferDesc.ByteWidth = sizeof(UINT) * UINT(indices.size());
            indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
            indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
            D3D11_SUBRESOURCE_DATA indexSubresourceData = {};
            indexSubresourceData.pSysMem = indices.data();
            Graphics::GetDevice3D().CreateBuffer(&indexBufferDesc, &indexSubresourceData, _indexBuffer.GetAddressOf());
        }
    }
    void Draw()
    {
        if (_vertexBuffer == nullptr)
            return;

        if (_texture != nullptr)
            _texture->Attach(0);

        _cbuffer.GetData().world = DirectX::XMMatrixTranspose(
            DirectX::XMMatrixScaling(scale.x, scale.y, scale.z) *
            DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(angles.x)) *
            DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(angles.z)) *
            DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(angles.y)) *
            DirectX::XMMatrixTranslation(position.x, position.y, position.z)
        );

        _cbuffer.Attach(5);

        material.Attach();

        Graphics::GetContext3D().RSSetState(_rasterizerState.Get());

        UINT stride = sizeof(Vertex);
        UINT offset = 0;
        Graphics::GetContext3D().IASetVertexBuffers(0, 1, _vertexBuffer.GetAddressOf(), &stride, &offset);

        if (_indexBuffer == nullptr)
        {
            Graphics::GetContext3D().Draw((UINT)vertices.size(), 0);
        }
        else
        {
            Graphics::GetContext3D().IASetIndexBuffer(_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
            Graphics::GetContext3D().DrawIndexed((UINT)indices.size(), 0, 0);
        }
    }

private:
    struct Constant
    {
        DirectX::XMMATRIX world;
    };

    Texture* _texture;
    CBuffer<Constant> _cbuffer;
    ComPtr<ID3D11Buffer> _vertexBuffer = nullptr;
    ComPtr<ID3D11Buffer> _indexBuffer = nullptr;
    ComPtr<ID3D11RasterizerState> _rasterizerState = nullptr;
};
class Sprite
{
public:
    Float3 position;
    Float3 angles;
    Float3 scale;
    Float4 color;
    Material material = Material::GetSpriteMaterial();

    Sprite()
    {
        Initialize();
    }
    Sprite(const wchar_t* const filePath)
    {
        Initialize();
        Load(filePath);
    }
    Sprite(const BYTE* const buffer, int width, int height)
    {
        Initialize();
        Create(buffer, width, height);
    }
    ~Sprite()
    {
    }
    void Load(const wchar_t* const filePath)
    {
        _texture.Load(filePath);

        _mesh.SetTexture(&_texture);

        SetPivot(0.0f);
    }
    void Create(const BYTE* const buffer, int width, int height)
    {
        _texture.Create(buffer, width, height);

        _mesh.SetTexture(&_texture);

        SetPivot(0.0f);
    }
    DirectX::XMINT2 GetSize() const
    {
        return _texture.GetSize();
    }
    void SetPivot(Float2 pivot)
    {
        Float2 textureSize((float)_texture.GetSize().x, (float)_texture.GetSize().y);
        Float2 offset = textureSize / 2.0f * -pivot;

        _mesh.CreatePlane(textureSize, Float3(offset.x, offset.y, 0.0f));
    }
    void Draw()
    {
        _cbuffer.GetData() = color;
        _cbuffer.Attach(6);

        _mesh.position = position;
        _mesh.angles = angles;
        _mesh.scale = scale;
        _mesh.material = material;
        _mesh.Draw();
    }

protected:
    Mesh _mesh;
    Texture _texture;
    CBuffer<Float4> _cbuffer;

    void Initialize()
    {
        InitializeApplication();

        position = Float3(0.0f, 0.0f, 0.0f);
        angles = Float3(0.0f, 0.0f, 0.0f);
        scale = Float3(1.0f, 1.0f, 1.0f);
        color = Float4(1.0f, 1.0f, 1.0f, 1.0f);

        _mesh.SetCullingMode(D3D11_CULL_NONE);
    }
};
class Text : public Sprite
{
public:
    bool antialias = true;

    Text(const std::wstring& text = L"", float fontSize = 16.0f, DWRITE_TEXT_ALIGNMENT align = DWRITE_TEXT_ALIGNMENT_CENTER, const wchar_t* const fontFace = L"ＭＳ ゴシック")
    {
        Sprite::Initialize();
        color = Float4(0.0f, 0.0f, 0.0f, 1.0f);
        Create(text, fontSize, align, fontFace);
    }
    void Create(const std::wstring& text = L"", float fontSize = 16.0f, DWRITE_TEXT_ALIGNMENT align = DWRITE_TEXT_ALIGNMENT_CENTER, const wchar_t* const fontFace = L"ＭＳ ゴシック")
    {
        if (text == L"")
            return;

        _brush.Reset();
        Graphics::GetContext2D().CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), _brush.GetAddressOf());

        ComPtr<IDWriteTextFormat> textFormat = nullptr;
        Graphics::GetTextFactory().CreateTextFormat(fontFace, nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, fontSize, L"ja-jp", textFormat.GetAddressOf());

        textFormat->SetTextAlignment(align);
        textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

        _textLayout.Reset();
        Graphics::GetTextFactory().CreateTextLayout(text.c_str(), (UINT32)text.length(), textFormat.Get(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), _textLayout.GetAddressOf());
        
        DWRITE_TEXT_METRICS textMetrics;
        _textLayout->GetMetrics(&textMetrics);

        _textLayout.Reset();
        Graphics::GetTextFactory().CreateTextLayout(text.c_str(), (UINT32)text.length(), textFormat.Get(), textMetrics.width, textMetrics.height, _textLayout.GetAddressOf());

        std::unique_ptr<BYTE[]> buffer(new BYTE[int(textMetrics.width * textMetrics.height) * 4]);
        _texture.Create(buffer.get(), (int)textMetrics.width, (int)textMetrics.height);

        ComPtr<IDXGISurface> surface = nullptr;
        _texture.GetInterface().QueryInterface(surface.GetAddressOf());

        D2D1_BITMAP_PROPERTIES1 bitmapProperties = {};
        bitmapProperties.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
        bitmapProperties.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
        bitmapProperties.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET;

        _bitmap.Reset();
        Graphics::GetContext2D().CreateBitmapFromDxgiSurface(surface.Get(), bitmapProperties, _bitmap.GetAddressOf());

        _mesh.SetTexture(&_texture);

        SetPivot(0.0f);
    }
    void Draw()
    {
        if (antialias)
            Graphics::GetContext2D().SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_DEFAULT);
        else
            Graphics::GetContext2D().SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_ALIASED);

        Graphics::GetContext2D().SetTarget(_bitmap.Get());

        Graphics::GetContext2D().BeginDraw();

        Graphics::GetContext2D().Clear(D2D1::ColorF(1.0f, 1.0f, 1.0f, 0.0f));
        Graphics::GetContext2D().DrawTextLayout(D2D1::Point2F(0.0f, 0.0f), _textLayout.Get(), _brush.Get());

        Graphics::GetContext2D().EndDraw();

        Sprite::Draw();
    }
    void Load(const wchar_t* const filePath) = delete;
    void Create(const BYTE* const buffer, int width, int height) = delete;

private:
    ComPtr<ID2D1Bitmap1> _bitmap = nullptr;
    ComPtr<ID2D1SolidColorBrush> _brush = nullptr;
    ComPtr<IDWriteTextLayout> _textLayout = nullptr;
};
class Sound : public Window::Proceedable
{
public:
    enum class State
    {
        Playing,
        Paused,
        Stopped,
    };

    Sound()
    {
        Initialize();
    }
    Sound(const wchar_t* const filePath)
    {
        Initialize();
        Load(filePath);
    }
    virtual ~Sound()
    {
        Window::RemoveProcedure(this);
    }
    void Load(const wchar_t* const filePath)
    {
        SoundManager::GetDevice();

        ComPtr<IStream> stream = nullptr;
        HRESULT result = SHCreateStreamOnFileW(filePath, STGM_READ, stream.GetAddressOf());

        if (stream == nullptr)
            Utility::Alert(result);

        ComPtr<IMFByteStream> byteStream = nullptr;
        MFCreateMFByteStreamOnStream(stream.Get(), byteStream.GetAddressOf());

        ComPtr<IMFAttributes> attributes = nullptr;
        MFCreateAttributes(attributes.GetAddressOf(), 1);

        _sourceReader.Reset();
        MFCreateSourceReaderFromByteStream(byteStream.Get(), attributes.Get(), _sourceReader.GetAddressOf());

        ComPtr<IMFMediaType> mediaType = nullptr;
        MFCreateMediaType(mediaType.GetAddressOf());
        mediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
        mediaType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);

        _sourceReader->SetCurrentMediaType((DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, nullptr, mediaType.Get());
        mediaType.Reset();
        _sourceReader->GetCurrentMediaType((DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, mediaType.GetAddressOf());

        UINT32 waveFormatSize = sizeof(WAVEFORMATEX);
        MFCreateWaveFormatExFromMFMediaType(mediaType.Get(), &_format, &waveFormatSize);

        ComPtr<IMFSample> sample = nullptr;
        DWORD flags = 0;
        _sourceReader->ReadSample((DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, &flags, nullptr, sample.GetAddressOf());

        ComPtr<IMFMediaBuffer> mediaBuffer = nullptr;
        sample->ConvertToContiguousBuffer(mediaBuffer.GetAddressOf());

        mediaBuffer->GetMaxLength(&_bufferSize);
        _bufferSize -= _format->nBlockAlign;

        DSBUFFERDESC bufferDesc = {};
        bufferDesc.dwSize = sizeof(DSBUFFERDESC);
        bufferDesc.dwFlags = DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY | DSBCAPS_GETCURRENTPOSITION2;
        bufferDesc.dwBufferBytes = _bufferSize * 2;
        bufferDesc.lpwfxFormat = _format;

        _soundBuffer.Reset();
        SoundManager::GetDevice().CreateSoundBuffer(&bufferDesc, _soundBuffer.GetAddressOf(), nullptr);
    }
    void SetLoop(bool isLoop)
    {
        _isLoop = isLoop;
    }
    void SetVolume(float volume)
    {
        if (volume < std::numeric_limits<float>::min())
            volume = std::numeric_limits<float>::min();

        LONG decibel = LONG(log10f(volume) * 20.0f * 100.0f);

        if (decibel < DSBVOLUME_MIN)
            decibel = DSBVOLUME_MIN;

        if (decibel > DSBVOLUME_MAX)
            decibel = DSBVOLUME_MAX;

        _soundBuffer->SetVolume(decibel);
    }
    void SetPan(float pan)
    {
        int sign = (pan > 0) - (pan < 0);

        pan = 1.0f - fabsf(pan);
        if (pan < std::numeric_limits<float>::min())
            pan = std::numeric_limits<float>::min();

        LONG decibel = LONG(log10f(pan) * 20.0f * 100.0f) * -sign;

        if (decibel < DSBPAN_LEFT)
            decibel = DSBPAN_LEFT;

        if (decibel > DSBPAN_RIGHT)
            decibel = DSBPAN_RIGHT;

        _soundBuffer->SetPan(decibel);
    }
    void SetPitch(float pitch)
    {
        if (pitch < 0.0f)
            pitch = 0.0f;

        DWORD frequency = DWORD(_format->nSamplesPerSec * pitch);

        if (frequency < DSBFREQUENCY_MIN)
            frequency = DSBFREQUENCY_MIN;

        if (frequency > DSBFREQUENCY_MAX)
            frequency = DSBFREQUENCY_MAX;

        _soundBuffer->SetFrequency(frequency);
    }
    State GetState()
    {
        return _state;
    }
    void Play()
    {
        if (!_isLoop)
        {
            Stop();
        }

        _state = State::Playing;
        _soundBuffer->Play(0, 0, DSBPLAY_LOOPING);
    }
    void Pause()
    {
        _state = State::Paused;
        _soundBuffer->Stop();
    }
    void Stop()
    {
        _state = State::Stopped;
        Reset();

        _bufferIndex = 0;
        _soundBuffer->SetCurrentPosition(0);

        void* buffer = nullptr;
        DWORD bufferSize = 0;
        _soundBuffer->Lock(0, 0, &buffer, &bufferSize, nullptr, nullptr, DSBLOCK_ENTIREBUFFER);
        memset(buffer, 256, bufferSize);
        _soundBuffer->Unlock(buffer, bufferSize, nullptr, 0);
    }

private:
    ComPtr<IMFSourceReader> _sourceReader = nullptr;
    ComPtr<IDirectSoundBuffer> _soundBuffer = nullptr;
    DWORD _bufferSize;
    int _bufferIndex = 0;
    WAVEFORMATEX* _format;
    State _state = State::Stopped;
    bool _isLoop = false;

    void Initialize()
    {
        InitializeApplication();

        Window::AddProcedure(this);
    }
    void Reset()
    {
        PROPVARIANT position = {};
        position.vt = VT_I8;
        position.hVal.QuadPart = 0;
        _sourceReader->SetCurrentPosition(GUID_NULL, position);
    }
    void Push(void* buffer, DWORD size)
    {
        if (buffer == nullptr)
            return;

        memset(buffer, 256, size);

        ComPtr<IMFSample> sample = nullptr;
        DWORD flags = 0;
        _sourceReader->ReadSample((DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, &flags, nullptr, sample.GetAddressOf());

        if (flags & MF_SOURCE_READERF_ENDOFSTREAM)
        {
            if (!_isLoop)
            {
                Stop();
                return;
            }

            Reset();

            sample.Reset();
            _sourceReader->ReadSample((DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, &flags, nullptr, sample.GetAddressOf());
        }

        ComPtr<IMFMediaBuffer> mediaBuffer = nullptr;
        sample->ConvertToContiguousBuffer(mediaBuffer.GetAddressOf());
        mediaBuffer->SetCurrentLength(size);

        BYTE* temp = nullptr;
        mediaBuffer->Lock(&temp, nullptr, &size);
        memcpy(buffer, temp, size);
        mediaBuffer->Unlock();
    }
    void OnProceedMessage(HWND, UINT message, WPARAM, LPARAM) override
    {
        if (message != WM_APP)
            return;

        DWORD position;
        _soundBuffer->GetCurrentPosition(&position, 0);

        if (_state == State::Stopped)
        {
            void* buffer = nullptr;
            DWORD bufferSize = 0;
            _soundBuffer->Lock(0, 0, &buffer, &bufferSize, nullptr, nullptr, DSBLOCK_ENTIREBUFFER);
            memset(buffer, 256, bufferSize);
            _soundBuffer->Unlock(buffer, bufferSize, nullptr, 0);
        }
        else
        {
            void* buffer1 = nullptr;
            DWORD bufferSize1 = 0;
            void* buffer2 = nullptr;
            DWORD bufferSize2 = 0;

            if (_bufferIndex == 0 && position < _bufferSize)
            {
                _soundBuffer->Lock(_bufferSize, _bufferSize * 2, &buffer1, &bufferSize1, &buffer2, &bufferSize2, 0);
                Push(buffer1, bufferSize1);
                _soundBuffer->Unlock(buffer1, bufferSize1, buffer2, bufferSize2);
                _bufferIndex = 1;
            }
            if (_bufferIndex == 1 && position >= _bufferSize)
            {
                _soundBuffer->Lock(0, _bufferSize, &buffer1, &bufferSize1, &buffer2, &bufferSize2, 0);
                Push(buffer1, bufferSize1);
                _soundBuffer->Unlock(buffer1, bufferSize1, buffer2, bufferSize2);
                _bufferIndex = 0;
            }
        }
    }
};


/// アプリケーションを更新します。while文の中に書いてください。
inline bool Refresh()
{
    Graphics::Update();
    LightManager::Update();
    Input::Update();
    Timer::Update();
    return Window::Update();
}

}
