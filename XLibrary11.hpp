/*! © 2017 itukikikuti | MIT License | gitlab.com/itukikikuti/XLibrary11 */
#pragma once

#define OEMRESOURCE
#include <cstdio>
#include <fstream>
#include <iostream>
#include <list>
#include <memory>
#include <random>
#include <string>
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

#define MAIN() APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)

namespace XLibrary
{

using namespace DirectX;
using Microsoft::WRL::ComPtr;

static void InitializeApplication()
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
        return Float2(this->x, this->y);
    }
    Float2 operator-() const
    {
        return Float2(-this->x, -this->y);
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
        return Float3(this->x, this->y, this->z);
    }
    Float3 operator-() const
    {
        return Float3(-this->x, -this->y, -this->z);
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
        return Float4(this->x, this->y, this->z, this->w);
    }
    Float4 operator-() const
    {
        return Float4(-this->x, -this->y, -this->z, -this->w);
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
        return GetInstance().handle;
    }
    static DirectX::XMINT2 GetSize()
    {
        RECT clientRect = {};
        GetClientRect(GetInstance().handle, &clientRect);

        return DirectX::XMINT2(clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
    }
    static void SetSize(int width, int height)
    {
        RECT windowRect = {};
        RECT clientRect = {};
        GetWindowRect(GetInstance().handle, &windowRect);
        GetClientRect(GetInstance().handle, &clientRect);

        int w = (windowRect.right - windowRect.left) - (clientRect.right - clientRect.left) + width;
        int h = (windowRect.bottom - windowRect.top) - (clientRect.bottom - clientRect.top) + height;
        int x = (GetSystemMetrics(SM_CXSCREEN) - w) / 2;
        int y = (GetSystemMetrics(SM_CYSCREEN) - h) / 2;

        SetWindowPos(GetInstance().handle, nullptr, x, y, w, h, SWP_FRAMECHANGED);
    }
    static wchar_t* const GetTitle()
    {
        wchar_t* title = nullptr;
        GetWindowTextW(GetInstance().handle, title, GetWindowTextLengthW(GetInstance().handle));
        return title;
    }
    static void SetTitle(const wchar_t* const title)
    {
        SetWindowTextW(GetInstance().handle, title);
    }
    static void SetFullScreen(bool isFullScreen)
    {
        static DirectX::XMINT2 size = GetSize();

        if (isFullScreen)
        {
            size = GetSize();
            int w = GetSystemMetrics(SM_CXSCREEN);
            int h = GetSystemMetrics(SM_CYSCREEN);
            SetWindowLongPtrW(GetInstance().handle, GWL_STYLE, WS_VISIBLE | WS_POPUP);
            SetWindowPos(GetInstance().handle, HWND_TOP, 0, 0, w, h, SWP_FRAMECHANGED);
        }
        else
        {
            SetWindowLongPtrW(GetInstance().handle, GWL_STYLE, WS_VISIBLE | WS_OVERLAPPEDWINDOW);
            SetWindowPos(GetInstance().handle, nullptr, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);
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

        PostMessageW(GetInstance().handle, WM_APP, 0, 0);

        if (GetSize().x <= 0.0f || GetSize().y <= 0.0f)
            Sleep(100);

        return true;
    }
    static void AddProcedure(Proceedable* const procedure)
    {
        GetInstance().procedures.push_back(procedure);
    }
    static void RemoveProcedure(Proceedable* const procedure)
    {
        GetInstance().procedures.remove(procedure);
    }

private:
    friend std::unique_ptr<Window>::deleter_type;

    const wchar_t* className = L"XLibrary11";
    HWND handle;
    std::list<Proceedable*> procedures;

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    Window()
    {
        InitializeApplication();

        HINSTANCE instance = GetModuleHandleW(nullptr);

        WNDCLASSW windowClass = {};
        windowClass.lpfnWndProc = DefWindowProcW;
        windowClass.hInstance = instance;
        windowClass.hCursor = static_cast<HCURSOR>(LoadImageW(nullptr, MAKEINTRESOURCEW(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_SHARED));
        windowClass.lpszClassName = className;
        RegisterClassW(&windowClass);

        handle = CreateWindowW(className, className, WS_OVERLAPPEDWINDOW, 0, 0, 0, 0, nullptr, nullptr, instance, nullptr);

        ShowWindow(handle, SW_SHOWNORMAL);
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
        for (Proceedable* procedure : GetInstance().procedures)
        {
            procedure->OnProceed(window, message, wParam, lParam);
        }

        if (message == WM_DESTROY)
            PostQuitMessage(0);

        return DefWindowProcW(window, message, wParam, lParam);
    }
};
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
class Graphics : public Window::Proceedable
{
public:
    static ID3D11Device& GetDevice3D()
    {
        return *GetInstance().device3D.Get();
    }
    static ID3D11DeviceContext& GetContext3D()
    {
        return *GetInstance().context3D.Get();
    }
    static ID2D1Device& GetDevice2D()
    {
        return *GetInstance().device2D.Get();
    }
    static ID2D1DeviceContext& GetContext2D()
    {
        return *GetInstance().context2D.Get();
    }
    static IDXGISwapChain& GetSwapChain()
    {
        return *GetInstance().swapChain.Get();
    }
    static IWICImagingFactory& GetTextureFactory()
    {
        return *GetInstance().textureFactory.Get();
    }
    static IDWriteFactory& GetTextFactory()
    {
        return *GetInstance().textFactory.Get();
    }
    static void Update()
    {
        if (Input::GetKey(VK_MENU) && Input::GetKeyDown(VK_RETURN))
        {
            GetInstance().isFullScreen = !GetInstance().isFullScreen;
            Window::SetFullScreen(GetInstance().isFullScreen);
        }

        GetInstance().swapChain->Present(1, 0);
    }

private:
    friend std::unique_ptr<Graphics>::deleter_type;

    ComPtr<ID3D11Device> device3D = nullptr;
    ComPtr<ID3D11DeviceContext> context3D = nullptr;
    ComPtr<ID2D1Device> device2D = nullptr;
    ComPtr<ID2D1DeviceContext> context2D = nullptr;
    ComPtr<IDXGISwapChain> swapChain = nullptr;
    ComPtr<IWICImagingFactory> textureFactory = nullptr;
    ComPtr<IDWriteFactory> textFactory = nullptr;
    bool isFullScreen = false;

    Graphics(const Graphics&) = delete;
    Graphics& operator=(const Graphics&) = delete;
    Graphics()
    {
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
            HRESULT r = D3D11CreateDevice(nullptr, driverTypes[i], nullptr, flags, featureLevels.data(), (UINT)featureLevels.size(), D3D11_SDK_VERSION, device3D.GetAddressOf(), nullptr, context3D.GetAddressOf());

            if (SUCCEEDED(r))
                break;
        }

        context3D->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

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
        device3D->CreateBlendState(&blendDesc, &blendState);
        context3D->OMSetBlendState(blendState.Get(), blendFactor, 0xffffffff);

        D2D1_FACTORY_OPTIONS options = {};
#if defined(_DEBUG)
        options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
#endif

        ComPtr<ID2D1Factory1> factory = nullptr;
        D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, options, factory.GetAddressOf());

        ComPtr<IDXGIDevice> device = nullptr;
        device3D->QueryInterface(device.GetAddressOf());

        factory->CreateDevice(device.Get(), device2D.GetAddressOf());

        device2D->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, context2D.GetAddressOf());

        CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, reinterpret_cast<void**>(textureFactory.GetAddressOf()));

        DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(textFactory.GetAddressOf()));

        Create();

        Window::AddProcedure(this);
    }
    virtual ~Graphics()
    {
        Window::RemoveProcedure(this);
    }
    static Graphics& GetInstance()
    {
        static std::unique_ptr<Graphics> instance;

        if (instance == nullptr)
        {
            instance.reset(Instantiate());
        }

        return *instance;
    }
    static Graphics* Instantiate()
    {
        return new Graphics();
    }
    void Create()
    {
        ComPtr<IDXGIDevice> dxgi = nullptr;
        device3D->QueryInterface(dxgi.GetAddressOf());

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

        swapChain.Reset();
        factory->CreateSwapChain(device3D.Get(), &swapChainDesc, swapChain.GetAddressOf());
        factory->MakeWindowAssociation(Window::GetHandle(), DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER);

        D3D11_VIEWPORT viewPort = {};
        viewPort.Width = static_cast<float>(Window::GetSize().x);
        viewPort.Height = static_cast<float>(Window::GetSize().y);
        viewPort.MaxDepth = 1.0f;
        context3D->RSSetViewports(1, &viewPort);
    }
    void OnProceed(HWND, UINT message, WPARAM, LPARAM) override
    {
        if (message != WM_SIZE)
            return;

        if (Window::GetSize().x <= 0.0f || Window::GetSize().y <= 0.0f)
            return;

        Create();
    }
};
class Audio
{
public:
    static IDirectSound8& GetDevice()
    {
        return *GetInstance().device.Get();
    }

private:
    friend std::unique_ptr<Audio>::deleter_type;

    ComPtr<IDirectSound8> device = nullptr;

    Audio(const Audio&) = delete;
    Audio& operator=(const Audio&) = delete;
    Audio()
    {
        InitializeApplication();

        DirectSoundCreate8(nullptr, &device, nullptr);

        device->SetCooperativeLevel(Window::GetHandle(), DSSCL_NORMAL);

        MFStartup(MF_VERSION);
    }
    ~Audio()
    {
        MFShutdown();
    }
    static Audio& GetInstance()
    {
        static std::unique_ptr<Audio> instance;

        if (instance == nullptr)
        {
            instance.reset(Instantiate());
        }

        return *instance;
    }
    static Audio* Instantiate()
    {
        return new Audio();
    }
};
class Timer
{
public:
    static float GetTime()
    {
        return GetInstance().time;
    }
    static float GetDeltaTime()
    {
        return GetInstance().deltaTime;
    }
    static int GetFrameRate()
    {
        return GetInstance().frameRate;
    }
    static void Update()
    {
        LARGE_INTEGER count = GetInstance().GetCounter();
        GetInstance().deltaTime = static_cast<float>(count.QuadPart - GetInstance().preCount.QuadPart) / GetInstance().frequency.QuadPart;
        GetInstance().preCount = GetInstance().GetCounter();

        GetInstance().time += GetInstance().deltaTime;

        GetInstance().frameCount++;
        GetInstance().second += GetInstance().deltaTime;
        if (GetInstance().second >= 1.0f)
        {
            GetInstance().frameRate = GetInstance().frameCount;
            GetInstance().frameCount = 0;
            GetInstance().second -= 1.0f;
        }
    }

private:
    friend std::unique_ptr<Timer>::deleter_type;

    float time = 0.0f;
    float deltaTime = 0.0f;
    int frameRate = 0;
    float second = 0.0f;
    int frameCount = 0;
    LARGE_INTEGER preCount;
    LARGE_INTEGER frequency;

    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;
    Timer()
    {
        InitializeApplication();

        preCount = GetCounter();
        frequency = GetCountFrequency();
    }
    ~Timer()
    {
    }
    static Timer& GetInstance()
    {
        static std::unique_ptr<Timer> instance;

        if (instance == nullptr)
        {
            instance.reset(Instantiate());
        }

        return *instance;
    }
    static Timer* Instantiate()
    {
        return new Timer();
    }
    LARGE_INTEGER GetCounter()
    {
        LARGE_INTEGER counter;
        QueryPerformanceCounter(&counter);
        return counter;
    }
    LARGE_INTEGER GetCountFrequency()
    {
        LARGE_INTEGER _frequency;
        QueryPerformanceFrequency(&_frequency);
        return _frequency;
    }
};
class Random
{
public:
    static void SetSeed(int seed)
    {
        GetInstance().mt.seed(seed);
    }
    static float Get()
    {
        std::uniform_real_distribution<float> range(0.0f, 1.0f);

        return range(GetInstance().mt);
    }

private:
    friend std::unique_ptr<Random>::deleter_type;

    std::mt19937 mt;

    Random(const Random&) = delete;
    Random& operator=(const Random&) = delete;
    Random()
    {
        InitializeApplication();

        std::random_device device;
        mt.seed(device());
    }
    ~Random()
    {
    }
    static Random& GetInstance()
    {
        static std::unique_ptr<Random> instance;

        if (instance == nullptr)
        {
            instance.reset(Instantiate());
        }

        return *instance;
    }
    static Random* Instantiate()
    {
        return new Random();
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

        Graphics::GetTextureFactory().CreateDecoderFromFilename(filePath, 0, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &decoder);
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
        size = DirectX::XMINT2(width, height);

        texture.Reset();
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
        Graphics::GetDevice3D().CreateTexture2D(&textureDesc, &textureSubresourceData, texture.GetAddressOf());

        shaderResourceView.Reset();
        D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc = {};
        shaderResourceViewDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        shaderResourceViewDesc.Texture2D.MipLevels = 1;
        Graphics::GetDevice3D().CreateShaderResourceView(texture.Get(), &shaderResourceViewDesc, shaderResourceView.GetAddressOf());

        samplerState.Reset();
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
        samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
        Graphics::GetDevice3D().CreateSamplerState(&samplerDesc, samplerState.GetAddressOf());
    }
    DirectX::XMINT2 GetSize() const
    {
        return size;
    }
    void Attach(int slot)
    {
        if (texture == nullptr)
            return;

        Graphics::GetContext3D().PSSetShaderResources(slot, 1, shaderResourceView.GetAddressOf());
        Graphics::GetContext3D().PSSetSamplers(slot, 1, samplerState.GetAddressOf());
    }
    ID3D11Texture2D& GetInterface()
    {
        return *texture.Get();
    }

private:
    DirectX::XMINT2 size;
    ComPtr<ID3D11Texture2D> texture = nullptr;
    ComPtr<ID3D11ShaderResourceView> shaderResourceView = nullptr;
    ComPtr<ID3D11SamplerState> samplerState = nullptr;
};
class Material
{
public:
    Material()
    {
        Initialize();
    }
    Material(const wchar_t* const filePath)
    {
        Initialize();
        Load(filePath);
    }
    Material(const std::string& source)
    {
        Initialize();
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
        vertexShader.Reset();
        ComPtr<ID3DBlob> vertexShaderBlob = nullptr;
        CompileShader(source, "VS", "vs_5_0", vertexShaderBlob.GetAddressOf());
        Graphics::GetDevice3D().CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), nullptr, vertexShader.GetAddressOf());

        pixelShader.Reset();
        ComPtr<ID3DBlob> pixelShaderBlob = nullptr;
        CompileShader(source, "PS", "ps_5_0", pixelShaderBlob.GetAddressOf());
        Graphics::GetDevice3D().CreatePixelShader(pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize(), nullptr, pixelShader.GetAddressOf());

        inputLayout.Reset();
        std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDesc;
        inputElementDesc.push_back({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 });
        inputElementDesc.push_back({ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 });
        inputElementDesc.push_back({ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 });
        inputElementDesc.push_back({ "BLENDINDICES", 0, DXGI_FORMAT_R32G32B32A32_UINT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 });
        inputElementDesc.push_back({ "BLENDINDICES", 1, DXGI_FORMAT_R32G32B32A32_UINT, 0, 48, D3D11_INPUT_PER_VERTEX_DATA, 0 });
        inputElementDesc.push_back({ "BLENDWEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 64, D3D11_INPUT_PER_VERTEX_DATA, 0 });
        inputElementDesc.push_back({ "BLENDWEIGHT", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 80, D3D11_INPUT_PER_VERTEX_DATA, 0 });

        Graphics::GetDevice3D().CreateInputLayout(inputElementDesc.data(), (UINT)inputElementDesc.size(), vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), inputLayout.GetAddressOf());
    }
    void SetBuffer(int slot, void* cbuffer, size_t size)
    {
        constantBuffer[slot].ptr = cbuffer;

        constantBuffer[slot].buffer.Reset();
        D3D11_BUFFER_DESC constantBufferDesc = {};
        constantBufferDesc.ByteWidth = (UINT)size;
        constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
        constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        Graphics::GetDevice3D().CreateBuffer(&constantBufferDesc, nullptr, constantBuffer[slot].buffer.GetAddressOf());
    }
    void SetTexture(int slot, Texture* texture)
    {
        textures[slot] = texture;
    }
    void Attach()
    {
        if (vertexShader != nullptr)
            Graphics::GetContext3D().VSSetShader(vertexShader.Get(), nullptr, 0);

        if (pixelShader != nullptr)
            Graphics::GetContext3D().PSSetShader(pixelShader.Get(), nullptr, 0);

        if (inputLayout != nullptr)
            Graphics::GetContext3D().IASetInputLayout(inputLayout.Get());

        for (int i = 0; i < 10; i++)
        {
            if (constantBuffer[i].ptr != nullptr)
            {
                Graphics::GetContext3D().UpdateSubresource(constantBuffer[i].buffer.Get(), 0, nullptr, constantBuffer[i].ptr, 0, 0);
                Graphics::GetContext3D().VSSetConstantBuffers(i, 1, constantBuffer[i].buffer.GetAddressOf());
                Graphics::GetContext3D().HSSetConstantBuffers(i, 1, constantBuffer[i].buffer.GetAddressOf());
                Graphics::GetContext3D().DSSetConstantBuffers(i, 1, constantBuffer[i].buffer.GetAddressOf());
                Graphics::GetContext3D().GSSetConstantBuffers(i, 1, constantBuffer[i].buffer.GetAddressOf());
                Graphics::GetContext3D().PSSetConstantBuffers(i, 1, constantBuffer[i].buffer.GetAddressOf());
            }
        }

        for (int i = 0; i < 10; i++)
        {
            if (textures[i] != nullptr)
            {
                textures[i]->Attach(i);
            }
        }
    }

private:
    struct ConstantBuffer
    {
        void* ptr = nullptr;
        ComPtr<ID3D11Buffer> buffer = nullptr;
    };

    ConstantBuffer constantBuffer[10];
    Texture* textures[10];
    ComPtr<ID3D11VertexShader> vertexShader = nullptr;
    ComPtr<ID3D11PixelShader> pixelShader = nullptr;
    ComPtr<ID3D11InputLayout> inputLayout = nullptr;

    void Initialize()
    {
        InitializeApplication();

        for (int i = 0; i < 10; i++)
        {
            textures[i] = nullptr;
        }
    }
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
            OutputDebugStringA(static_cast<char*>(errorBlob->GetBufferPointer()));
            MessageBoxA(Window::GetHandle(), static_cast<char*>(errorBlob->GetBufferPointer()), "Shader Error", MB_OK);
        }
    }
};
class Camera : public Window::Proceedable
{
public:
    Float3 position;
    Float3 angles;
    Float4 color;

    Camera()
    {
        InitializeApplication();

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

        Graphics::GetContext3D().UpdateSubresource(constantBuffer.Get(), 0, nullptr, &constant, 0, 0);
        Graphics::GetContext3D().VSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());
        Graphics::GetContext3D().HSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());
        Graphics::GetContext3D().DSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());
        Graphics::GetContext3D().GSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());
        Graphics::GetContext3D().PSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());

        if (shouldClear)
        {
            float clearColor[4] = { color.x, color.y, color.z, color.w };
            Graphics::GetContext3D().ClearRenderTargetView(renderTargetView.Get(), clearColor);
        }

        if (isDepthTest)
        {
            Graphics::GetContext3D().ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
            Graphics::GetContext3D().OMSetRenderTargets(1, renderTargetView.GetAddressOf(), depthStencilView.Get());
        }
        else
        {
            Graphics::GetContext3D().OMSetRenderTargets(1, renderTargetView.GetAddressOf(), nullptr);
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
    ComPtr<ID3D11RenderTargetView> renderTargetView = nullptr;
    ComPtr<ID3D11DepthStencilView> depthStencilView = nullptr;
    ComPtr<ID3D11Texture2D> renderTexture = nullptr;
    ComPtr<ID3D11Texture2D> depthTexture = nullptr;
    ComPtr<ID3D11Buffer> constantBuffer = nullptr;

    void Create()
    {
        renderTexture.Reset();
        Graphics::GetSwapChain().GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(renderTexture.GetAddressOf()));
        renderTargetView.Reset();
        Graphics::GetDevice3D().CreateRenderTargetView(renderTexture.Get(), nullptr, renderTargetView.GetAddressOf());

        DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
        Graphics::GetSwapChain().GetDesc(&swapChainDesc);

        depthTexture.Reset();
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
        Graphics::GetDevice3D().CreateTexture2D(&textureDesc, nullptr, depthTexture.GetAddressOf());

        depthStencilView.Reset();
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
        Graphics::GetDevice3D().CreateDepthStencilView(depthTexture.Get(), &depthStencilViewDesc, depthStencilView.GetAddressOf());

        constantBuffer.Reset();
        D3D11_BUFFER_DESC constantBufferDesc = {};
        constantBufferDesc.ByteWidth = static_cast<UINT>(sizeof(Constant));
        constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
        constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        constantBufferDesc.CPUAccessFlags = 0;
        Graphics::GetDevice3D().CreateBuffer(&constantBufferDesc, nullptr, constantBuffer.GetAddressOf());
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
class Mesh
{
public:
    Float3 position;
    Float3 angles;
    Float3 scale;
    std::vector<Vertex> vertices;
    std::vector<UINT> indices;

    Mesh()
    {
        InitializeApplication();

        position = Float3(0.0f, 0.0f, 0.0f);
        angles = Float3(0.0f, 0.0f, 0.0f);
        scale = Float3(1.0f, 1.0f, 1.0f);

        material.Create(
            "cbuffer Camera : register(b0)"
            "{"
            "    matrix view;"
            "    matrix projection;"
            "};"
            "cbuffer Object : register(b1)"
            "{"
            "    matrix world;"
            "};"
            "Texture2D texture0 : register(t0);"
            "SamplerState sampler0 : register(s0);"
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
            "    float2 uv : TEXCOORD;"
            "};"
            "Pixel VS(Vertex vertex)"
            "{"
            "    Pixel output;"
            "    output.position = mul(vertex.position, world);"
            "    output.position = mul(output.position, view);"
            "    output.position = mul(output.position, projection);"
            "    output.normal = mul(vertex.normal, (float3x3)world);"
            "    output.uv = vertex.uv;"
            "    return output;"
            "}"
            "float4 PS(Pixel pixel) : SV_TARGET"
            "{"
            "    float3 normal = normalize(pixel.normal);"
            "    float3 lightDirection = normalize(float3(0.25, -1.0, 0.5));"
            "    float3 lightColor = float3(1.0, 1.0, 1.0);"
            "    float4 diffuseColor = texture0.Sample(sampler0, pixel.uv);"
            "    float3 diffuseIntensity = dot(-lightDirection, normal) * lightColor;"
            "    float3 ambientIntensity = lightColor * 0.2;"
            "    return diffuseColor * float4(diffuseIntensity + ambientIntensity, 1);"
            "}"
        );

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
    void CreateCube(Float3 size = Float3(0.5f, 0.5f, 0.5f), bool shouldClear = true)
    {
        if (shouldClear)
        {
            vertices.clear();
            indices.clear();
        }

        CreatePlane(Float2(size.x, size.y), Float3(0.0f, 0.0f, -size.z), false, Float3(1.0f, 0.0f, 0.0f), Float3(0.0f, 1.0f, 0.0f), Float3(0.0f, 0.0f, 1.0f));	// front
        CreatePlane(Float2(size.x, size.y), Float3(0.0f, 0.0f, size.z), false, Float3(-1.0f, 0.0f, 0.0f), Float3(0.0f, 1.0f, 0.0f), Float3(0.0f, 0.0f, -1.0f));	// back
        CreatePlane(Float2(size.z, size.y), Float3(size.x, 0.0f, 0.0f), false, Float3(0.0f, 0.0f, 1.0f), Float3(0.0f, 1.0f, 0.0f), Float3(-1.0f, 0.0f, 0.0f));	// left
        CreatePlane(Float2(size.z, size.y), Float3(-size.x, 0.0f, 0.0f), false, Float3(0.0f, 0.0f, -1.0f), Float3(0.0f, 1.0f, 0.0f), Float3(1.0f, 0.0f, 0.0f));	// right
        CreatePlane(Float2(size.x, size.z), Float3(0.0f, size.y, 0.0f), false, Float3(1.0f, 0.0f, 0.0f), Float3(0.0f, 0.0f, 1.0f), Float3(0.0f, -1.0f, 0.0f));	// up
        CreatePlane(Float2(size.x, size.z), Float3(0.0f, -size.y, 0.0f), false, Float3(1.0f, 0.0f, 0.0f), Float3(0.0f, 0.0f, -1.0f), Float3(0.0f, 1.0f, 0.0f));	// down

        if (shouldClear)
            Apply();
    }
    Material& GetMaterial()
    {
        return material;
    }
    void SetCullingMode(D3D11_CULL_MODE cullingMode)
    {
        D3D11_RASTERIZER_DESC rasterizerDesc = {};
        rasterizerDesc.FillMode = D3D11_FILL_SOLID;
        rasterizerDesc.CullMode = cullingMode;
        rasterizerState.Reset();
        Graphics::GetDevice3D().CreateRasterizerState(&rasterizerDesc, rasterizerState.GetAddressOf());
    }
    void Apply()
    {
        vertexBuffer.Reset();
        if (vertices.size() > 0)
        {
            D3D11_BUFFER_DESC vertexBufferDesc = {};
            vertexBufferDesc.ByteWidth = sizeof(Vertex) * (UINT)vertices.size();
            vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
            vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
            D3D11_SUBRESOURCE_DATA vertexSubresourceData = {};
            vertexSubresourceData.pSysMem = vertices.data();
            Graphics::GetDevice3D().CreateBuffer(&vertexBufferDesc, &vertexSubresourceData, vertexBuffer.GetAddressOf());
        }

        indexBuffer.Reset();
        if (indices.size() > 0)
        {
            D3D11_BUFFER_DESC indexBufferDesc = {};
            indexBufferDesc.ByteWidth = sizeof(int) * (UINT)indices.size();
            indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
            indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
            D3D11_SUBRESOURCE_DATA indexSubresourceData = {};
            indexSubresourceData.pSysMem = indices.data();
            Graphics::GetDevice3D().CreateBuffer(&indexBufferDesc, &indexSubresourceData, indexBuffer.GetAddressOf());
        }

        material.SetBuffer(1, &constant, sizeof(Constant));
    }
    void Draw()
    {
        if (vertexBuffer == nullptr)
            return;

        constant.world = DirectX::XMMatrixTranspose(
            DirectX::XMMatrixScaling(scale.x, scale.y, scale.z) *
            DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(angles.x)) *
            DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(angles.y)) *
            DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(angles.z)) *
            DirectX::XMMatrixTranslation(position.x, position.y, position.z)
        );

        material.Attach();

        Graphics::GetContext3D().RSSetState(rasterizerState.Get());

        UINT stride = sizeof(Vertex);
        UINT offset = 0;
        Graphics::GetContext3D().IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);

        if (indexBuffer == nullptr)
        {
            Graphics::GetContext3D().Draw((UINT)vertices.size(), 0);
        }
        else
        {
            Graphics::GetContext3D().IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
            Graphics::GetContext3D().DrawIndexed((UINT)indices.size(), 0, 0);
        }
    }

private:
    struct Constant
    {
        DirectX::XMMATRIX world;
    };

    Material material;
    Constant constant;
    ComPtr<ID3D11Buffer> vertexBuffer = nullptr;
    ComPtr<ID3D11Buffer> indexBuffer = nullptr;
    ComPtr<ID3D11RasterizerState> rasterizerState = nullptr;
};
class Sprite
{
public:
    Float3 position;
    Float3 angles;
    Float3 scale;
    Float4 color;

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
        texture.Load(filePath);

        mesh.GetMaterial().SetTexture(0, &texture);

        SetPivot(0.0f);
    }
    void Create(const BYTE* const buffer, int width, int height)
    {
        texture.Create(buffer, width, height);

        mesh.GetMaterial().SetTexture(0, &texture);

        SetPivot(0.0f);
    }
    DirectX::XMINT2 GetSize() const
    {
        return texture.GetSize();
    }
    void SetPivot(Float2 pivot)
    {
        Float2 textureSize(static_cast<float>(texture.GetSize().x), static_cast<float>(texture.GetSize().y));
        Float2 offset = textureSize / 2.0f * -pivot;

        mesh.CreatePlane(textureSize / 2.0f, Float3(offset.x, offset.y, 0.0f));
    }
    Material& GetMaterial()
    {
        return mesh.GetMaterial();
    }
    void Draw()
    {
        mesh.position = position;
        mesh.angles = angles;
        mesh.scale = scale;
        mesh.Draw();
    }

protected:
    Mesh mesh;
    Texture texture;

    void Initialize()
    {
        InitializeApplication();

        position = Float3(0.0f, 0.0f, 0.0f);
        angles = Float3(0.0f, 0.0f, 0.0f);
        scale = Float3(1.0f, 1.0f, 1.0f);
        color = Float4(1.0f, 1.0f, 1.0f, 1.0f);

        mesh.GetMaterial().Create(
            "cbuffer Camera : register(b0)"
            "{"
            "    matrix view;"
            "    matrix projection;"
            "};"
            "cbuffer Object : register(b1)"
            "{"
            "    matrix world;"
            "};"
            "cbuffer Sprite : register(b2)"
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
        );

        mesh.GetMaterial().SetBuffer(2, &color, sizeof(Float4));
        mesh.SetCullingMode(D3D11_CULL_NONE);
    }
};
class Text : public Sprite
{
public:
    Text(const std::wstring& text = L"", float fontSize = 16.0f, const wchar_t* const fontFace = L"ＭＳ ゴシック")
    {
        Sprite::Initialize();
        color = Float4(0.0f, 0.0f, 0.0f, 1.0f);
        Create(text, fontSize, fontFace);
    }
    void Create(const std::wstring& text = L"", float fontSize = 16.0f, const wchar_t* const fontFace = L"ＭＳ ゴシック")
    {
        if (text == L"")
            return;

        brush.Reset();
        Graphics::GetContext2D().CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), brush.GetAddressOf());
        Graphics::GetContext2D().SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_ALIASED);

        ComPtr<IDWriteTextFormat> textFormat = nullptr;
        Graphics::GetTextFactory().CreateTextFormat(fontFace, nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, fontSize, L"ja-jp", textFormat.GetAddressOf());

        textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
        textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

        textLayout.Reset();
        Graphics::GetTextFactory().CreateTextLayout(text.c_str(), (UINT32)text.length(), textFormat.Get(), FLT_MAX, FLT_MAX, textLayout.GetAddressOf());
        
        DWRITE_TEXT_METRICS textMetrics;
        textLayout->GetMetrics(&textMetrics);

        textLayout.Reset();
        Graphics::GetTextFactory().CreateTextLayout(text.c_str(), (UINT32)text.length(), textFormat.Get(), textMetrics.width, textMetrics.height, textLayout.GetAddressOf());

        std::unique_ptr<BYTE[]> buffer(new BYTE[(int)textMetrics.width * (int)textMetrics.height * 4]);
        texture.Create(buffer.get(), (int)textMetrics.width, (int)textMetrics.height);

        ComPtr<IDXGISurface> surface = nullptr;
        texture.GetInterface().QueryInterface(surface.GetAddressOf());

        D2D1_BITMAP_PROPERTIES1 bitmapProperties = {};
        bitmapProperties.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
        bitmapProperties.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
        bitmapProperties.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET;

        bitmap.Reset();
        Graphics::GetContext2D().CreateBitmapFromDxgiSurface(surface.Get(), bitmapProperties, bitmap.GetAddressOf());

        mesh.GetMaterial().SetTexture(0, &texture);

        SetPivot(0.0f);
    }
    void Draw()
    {
        Graphics::GetContext2D().SetTarget(bitmap.Get());

        Graphics::GetContext2D().BeginDraw();

        Graphics::GetContext2D().Clear(D2D1::ColorF(1.0f, 1.0f, 1.0f, 0.0f));
        Graphics::GetContext2D().DrawTextLayout(D2D1::Point2F(0.0f, 0.0f), textLayout.Get(), brush.Get());

        Graphics::GetContext2D().EndDraw();

        Sprite::Draw();
    }
    void Load(const wchar_t* const filePath) = delete;
    void Create(const BYTE* const buffer, int width, int height) = delete;

private:
    ComPtr<ID2D1Bitmap1> bitmap = nullptr;
    ComPtr<ID2D1SolidColorBrush> brush = nullptr;
    ComPtr<IDWriteTextLayout> textLayout = nullptr;
};
class Sound : public Window::Proceedable
{
public:
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
        Audio::GetDevice();

        ComPtr<IStream> stream = nullptr;
        SHCreateStreamOnFileW(filePath, STGM_READ, stream.GetAddressOf());

        ComPtr<IMFByteStream> byteStream = nullptr;
        MFCreateMFByteStreamOnStream(stream.Get(), byteStream.GetAddressOf());

        ComPtr<IMFAttributes> attributes = nullptr;
        MFCreateAttributes(attributes.GetAddressOf(), 1);

        sourceReader.Reset();
        MFCreateSourceReaderFromByteStream(byteStream.Get(), attributes.Get(), sourceReader.GetAddressOf());

        ComPtr<IMFMediaType> mediaType = nullptr;
        MFCreateMediaType(mediaType.GetAddressOf());
        mediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
        mediaType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);

        sourceReader->SetCurrentMediaType((DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, nullptr, mediaType.Get());
        mediaType.Reset();
        sourceReader->GetCurrentMediaType((DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, mediaType.GetAddressOf());

        UINT32 waveFormatSize = sizeof(WAVEFORMATEX);
        MFCreateWaveFormatExFromMFMediaType(mediaType.Get(), &format, &waveFormatSize);

        ComPtr<IMFSample> sample = nullptr;
        DWORD flags = 0;
        sourceReader->ReadSample((DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, &flags, nullptr, sample.GetAddressOf());

        ComPtr<IMFMediaBuffer> mediaBuffer = nullptr;
        sample->ConvertToContiguousBuffer(mediaBuffer.GetAddressOf());

        mediaBuffer->GetMaxLength(&bufferSize);
        bufferSize -= format->nBlockAlign;

        DSBUFFERDESC bufferDesc = {};
        bufferDesc.dwSize = sizeof(DSBUFFERDESC);
        bufferDesc.dwFlags = DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY | DSBCAPS_GETCURRENTPOSITION2;
        bufferDesc.dwBufferBytes = bufferSize * 2;
        bufferDesc.lpwfxFormat = format;

        soundBuffer.Reset();
        Audio::GetDevice().CreateSoundBuffer(&bufferDesc, soundBuffer.GetAddressOf(), nullptr);
    }
    void SetLoop(bool isLoop)
    {
        properties.isLoop = isLoop;
    }
    void SetVolume(float volume)
    {
        if (volume < 0.00000001f)
            volume = 0.00000001f;

        LONG decibel = (LONG)(log10f(volume) * 20.0f * 100.0f);

        if (decibel < DSBVOLUME_MIN)
            decibel = DSBVOLUME_MIN;

        if (decibel > DSBVOLUME_MAX)
            decibel = DSBVOLUME_MAX;

        soundBuffer->SetVolume(decibel);
    }
    void SetPan(float pan)
    {
        int sign = (pan > 0) - (pan < 0);

        pan = 1.0f - fabsf(pan);
        if (pan < 0.00000001f)
            pan = 0.00000001f;

        LONG decibel = (LONG)(log10f(pan) * 20.0f * 100.0f) * -sign;

        if (decibel < DSBPAN_LEFT)
            decibel = DSBPAN_LEFT;

        if (decibel > DSBPAN_RIGHT)
            decibel = DSBPAN_RIGHT;

        soundBuffer->SetPan(decibel);
    }
    void SetPitch(float pitch)
    {
        if (pitch < 0.0f)
            pitch = 0.0f;

        DWORD frequency = (DWORD)(format->nSamplesPerSec * pitch);

        if (frequency < DSBFREQUENCY_MIN)
            frequency = DSBFREQUENCY_MIN;

        if (frequency > DSBFREQUENCY_MAX)
            frequency = DSBFREQUENCY_MAX;

        soundBuffer->SetFrequency(frequency);
    }
    void Play()
    {
        if (!properties.isLoop)
        {
            Stop();
        }

        state = play;
        soundBuffer->Play(0, 0, DSBPLAY_LOOPING);
    }
    void Pause()
    {
        state = pause;
        soundBuffer->Stop();
    }
    void Stop()
    {
        state = stop;
        Reset();

        bufferIndex = 0;
        soundBuffer->SetCurrentPosition(0);

        void* buffer = nullptr;
        DWORD bufferSize = 0;
        soundBuffer->Lock(0, 0, &buffer, &bufferSize, nullptr, nullptr, DSBLOCK_ENTIREBUFFER);
        memset(buffer, 256, bufferSize);
        soundBuffer->Unlock(buffer, bufferSize, nullptr, 0);
    }

private:
    enum State
    {
        play,
        pause,
        stop,
    };

    struct Properties
    {
        bool isLoop = false;
    }
    properties;

    ComPtr<IMFSourceReader> sourceReader = nullptr;
    ComPtr<IDirectSoundBuffer> soundBuffer = nullptr;
    DWORD bufferSize;
    int bufferIndex = 0;
    WAVEFORMATEX* format;
    State state = stop;

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
        sourceReader->SetCurrentPosition(GUID_NULL, position);
    }
    void Push(void* buffer, DWORD size)
    {
        if (buffer == nullptr)
            return;

        memset(buffer, 256, size);

        ComPtr<IMFSample> sample = nullptr;
        DWORD flags = 0;
        sourceReader->ReadSample((DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, &flags, nullptr, sample.GetAddressOf());

        if (flags & MF_SOURCE_READERF_ENDOFSTREAM)
        {
            if (!properties.isLoop)
            {
                Stop();
                return;
            }

            Reset();

            sample.Reset();
            sourceReader->ReadSample((DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, &flags, nullptr, sample.GetAddressOf());
        }

        ComPtr<IMFMediaBuffer> mediaBuffer = nullptr;
        sample->ConvertToContiguousBuffer(mediaBuffer.GetAddressOf());
        mediaBuffer->SetCurrentLength(size);

        BYTE* temp = nullptr;
        mediaBuffer->Lock(&temp, nullptr, &size);
        memcpy(buffer, temp, size);
        mediaBuffer->Unlock();
    }
    void OnProceed(HWND, UINT message, WPARAM, LPARAM) override
    {
        if (message != WM_APP)
            return;

        DWORD position;
        soundBuffer->GetCurrentPosition(&position, 0);

        if (state == stop)
        {
            void* buffer = nullptr;
            DWORD bufferSize = 0;
            soundBuffer->Lock(0, 0, &buffer, &bufferSize, nullptr, nullptr, DSBLOCK_ENTIREBUFFER);
            memset(buffer, 256, bufferSize);
            soundBuffer->Unlock(buffer, bufferSize, nullptr, 0);
        }
        else
        {
            void* buffer1 = nullptr;
            DWORD bufferSize1 = 0;
            void* buffer2 = nullptr;
            DWORD bufferSize2 = 0;

            if (bufferIndex == 0 && position < bufferSize)
            {
                soundBuffer->Lock(bufferSize, bufferSize * 2, &buffer1, &bufferSize1, &buffer2, &bufferSize2, 0);
                Push(buffer1, bufferSize1);
                soundBuffer->Unlock(buffer1, bufferSize1, buffer2, bufferSize2);
                bufferIndex = 1;
            }
            if (bufferIndex == 1 && position >= bufferSize)
            {
                soundBuffer->Lock(0, bufferSize, &buffer1, &bufferSize1, &buffer2, &bufferSize2, 0);
                Push(buffer1, bufferSize1);
                soundBuffer->Unlock(buffer1, bufferSize1, buffer2, bufferSize2);
                bufferIndex = 0;
            }
        }
    }
};


static bool Refresh()
{
    Graphics::Update();
    Input::Update();
    Timer::Update();
    return Window::Update();
}

}
