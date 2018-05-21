// © 2017 itukikikuti
// https://github.com/itukikikuti/XLibrary11
// MIT License
#pragma once

#define OEMRESOURCE
#include <cstdio>
#include <forward_list>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <Windows.h>
#include <atlbase.h>
#include <d2d1_1.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <dsound.h>
#include <dwrite.h>
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
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

#define MAIN() APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)

namespace XLibrary11
{

using namespace DirectX;

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

Float2 operator+(const Float2& t1, const Float2& t2)
{
    return Float2(t1) += t2;
}
Float2 operator+(const Float2& t1, const float& t2)
{
    return Float2(t1) += t2;
}
Float2 operator-(const Float2& t1, const Float2& t2)
{
    return Float2(t1) -= t2;
}
Float2 operator-(const Float2& t1, const float& t2)
{
    return Float2(t1) -= t2;
}
Float2 operator*(const Float2& t1, const Float2& t2)
{
    return Float2(t1) *= t2;
}
Float2 operator*(const Float2& t1, const float& t2)
{
    return Float2(t1) *= t2;
}
Float2 operator/(const Float2& t1, const Float2& t2)
{
    return Float2(t1) /= t2;
}
Float2 operator/(const Float2& t1, const float& t2)
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

Float3 operator+(const Float3& t1, const Float3& t2)
{
    return Float3(t1) += t2;
}
Float3 operator+(const Float3& t1, const float& t2)
{
    return Float3(t1) += t2;
}
Float3 operator-(const Float3& t1, const Float3& t2)
{
    return Float3(t1) -= t2;
}
Float3 operator-(const Float3& t1, const float& t2)
{
    return Float3(t1) -= t2;
}
Float3 operator*(const Float3& t1, const Float3& t2)
{
    return Float3(t1) *= t2;
}
Float3 operator*(const Float3& t1, const float& t2)
{
    return Float3(t1) *= t2;
}
Float3 operator/(const Float3& t1, const Float3& t2)
{
    return Float3(t1) /= t2;
}
Float3 operator/(const Float3& t1, const float& t2)
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

Float4 operator+(const Float4& t1, const Float4& t2)
{
    return Float4(t1) += t2;
}
Float4 operator+(const Float4& t1, const float& t2)
{
    return Float4(t1) += t2;
}
Float4 operator-(const Float4& t1, const Float4& t2)
{
    return Float4(t1) -= t2;
}
Float4 operator-(const Float4& t1, const float& t2)
{
    return Float4(t1) -= t2;
}
Float4 operator*(const Float4& t1, const Float4& t2)
{
    return Float4(t1) *= t2;
}
Float4 operator*(const Float4& t1, const float& t2)
{
    return Float4(t1) *= t2;
}
Float4 operator/(const Float4& t1, const Float4& t2)
{
    return Float4(t1) /= t2;
}
Float4 operator/(const Float4& t1, const float& t2)
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

class App final
{
public:
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
        windowClass.hCursor = static_cast<HCURSOR>(LoadImageW(nullptr, MAKEINTRESOURCEW(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_SHARED));
        windowClass.lpszClassName = className;
        RegisterClassW(&windowClass);

        handle = CreateWindowW(className, className, WS_OVERLAPPEDWINDOW, 0, 0, 0, 0, nullptr, nullptr, instance, nullptr);

        SetSize(640, 480);
        ShowWindow(handle, SW_SHOWNORMAL);
    }
    ~Window()
    {
        UnregisterClassW(className, GetModuleHandleW(nullptr));
        CoUninitialize();
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

        PostMessageW(handle, WM_APP, 0, 0);

        return true;
    }
    static void AddProcedure(Proceedable* const procedure)
    {
        GetProcedures().push_front(procedure);
    }
    static void RemoveProcedure(Proceedable* const procedure)
    {
        GetProcedures().remove(procedure);
    }

private:
    const wchar_t* className = L"XLibrary11";
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
class Graphics : public App::Window::Proceedable
{
public:
    Graphics()
    {
        App::Initialize();

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

        for (size_t i = 0; i < driverTypes.size(); i++)
        {
            HRESULT r = D3D11CreateDeviceAndSwapChain(nullptr, driverTypes[i], nullptr, flags, featureLevels.data(), featureLevels.size(), D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device3D, nullptr, &context3D);

            if (SUCCEEDED(r))
                break;
        }

        context3D->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

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
        device3D->CreateBlendState(&blendDesc, &blendState);
        context3D->OMSetBlendState(blendState, blendFactor, 0xffffffff);

        D2D1_FACTORY_OPTIONS options = {};
#if defined(_DEBUG)
        options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
#endif

        ATL::CComPtr<ID2D1Factory1> factory = nullptr;
        D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, options, &factory);

        ATL::CComPtr<IDXGIDevice> device = nullptr;
        device3D.QueryInterface(&device);

        factory->CreateDevice(device, &device2D);

        device2D->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &context2D);

        textureFactory.CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER);

        DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), &textFactory);

        App::Window::AddProcedure(this);

        SetViewport();
    }
    virtual ~Graphics()
    {
        App::Window::RemoveProcedure(this);
    }
    ID3D11Device& GetDevice3D() const
    {
        return *device3D;
    }
    ID3D11DeviceContext& GetContext3D() const
    {
        return *context3D;
    }
    ID2D1Device& GetDevice2D() const
    {
        return *device2D;
    }
    ID2D1DeviceContext& GetContext2D() const
    {
        return *context2D;
    }
    IDXGISwapChain& GetSwapChain() const
    {
        return *swapChain;
    }
    IWICImagingFactory& GetTextureFactory() const
    {
        return *textureFactory;
    }
    IDWriteFactory& GetTextFactory() const
    {
        return *textFactory.Get();
    }
    void Update()
    {
        swapChain->Present(1, 0);
    }

private:
    ATL::CComPtr<ID3D11Device> device3D = nullptr;
    ATL::CComPtr<ID3D11DeviceContext> context3D = nullptr;
    ATL::CComPtr<ID2D1Device> device2D = nullptr;
    ATL::CComPtr<ID2D1DeviceContext> context2D = nullptr;
    ATL::CComPtr<IDXGISwapChain> swapChain = nullptr;
    ATL::CComPtr<IWICImagingFactory> textureFactory = nullptr;
    Microsoft::WRL::ComPtr<IDWriteFactory> textFactory = nullptr;

    void SetViewport()
    {
        D3D11_VIEWPORT viewPort = {};
        viewPort.Width = static_cast<float>(App::GetWindowSize().x);
        viewPort.Height = static_cast<float>(App::GetWindowSize().y);
        viewPort.MaxDepth = 1.0f;
        context3D->RSSetViewports(1, &viewPort);
    }
    void OnProceed(HWND, UINT message, WPARAM, LPARAM) override
    {
        if (message != WM_SIZE)
            return;

        if (App::GetWindowSize().x <= 0.0f || App::GetWindowSize().y <= 0.0f)
            return;

        SetViewport();
    }
};
class Audio
{
public:
    Audio()
    {
        App::Initialize();

        DirectSoundCreate8(nullptr, &device, nullptr);

        device->SetCooperativeLevel(App::GetWindowHandle(), DSSCL_NORMAL);

        MFStartup(MF_VERSION);
    }
    ~Audio()
    {
        MFShutdown();
    }
    IDirectSound8& GetDevice() const
    {
        return *device;
    }

private:
    ATL::CComPtr<IDirectSound8> device = nullptr;
};
class Input
{
public:
    Input()
    {
        App::Initialize();

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
        if (GetActiveWindow() != App::GetWindowHandle())
            return;

        POINT point = {};
        point.x = static_cast<int>(x) + App::GetWindowSize().x / 2;
        point.y = static_cast<int>(-y) + App::GetWindowSize().y / 2;
        ClientToScreen(App::GetWindowHandle(), &point);
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
        ScreenToClient(App::GetWindowHandle(), &point);

        mousePosition.x = static_cast<float>(point.x - App::GetWindowSize().x / 2);
        mousePosition.y = static_cast<float>(-point.y + App::GetWindowSize().y / 2);

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
class Timer
{
public:
    Timer()
    {
        App::Initialize();

        preCount = GetCounter();
        frequency = GetCountFrequency();
    }
    ~Timer()
    {
    }
    float GetTime() const
    {
        return time;
    }
    float GetDeltaTime() const
    {
        return deltaTime;
    }
    int GetFrameRate() const
    {
        return frameRate;
    }
    void Update()
    {
        LARGE_INTEGER count = GetCounter();
        deltaTime = static_cast<float>(count.QuadPart - preCount.QuadPart) / frequency.QuadPart;
        preCount = GetCounter();

        time += deltaTime;

        frameCount++;
        second += deltaTime;
        if (second >= 1.0f)
        {
            frameRate = frameCount;
            frameCount = 0;
            second -= 1.0f;
        }
    }

private:
    float time = 0.0f;
    float deltaTime = 0.0f;
    int frameRate = 0;
    float second = 0.0f;
    int frameCount = 0;
    LARGE_INTEGER preCount;
    LARGE_INTEGER frequency;

    LARGE_INTEGER GetCounter() const
    {
        LARGE_INTEGER counter;
        QueryPerformanceCounter(&counter);
        return counter;
    }
    LARGE_INTEGER GetCountFrequency() const
    {
        LARGE_INTEGER frequency;
        QueryPerformanceFrequency(&frequency);
        return frequency;
    }
};

    App() = delete;
    static bool Refresh()
    {
        GetGraphics().Update();
        GetInput().Update();
        GetTimer().Update();
        return GetWindow().Update();
    }
    static void Initialize()
    {
        static bool isInitialized = false;

        if (!isInitialized)
        {
            CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
            _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
            isInitialized = true;
        }
    }
    static HWND GetWindowHandle()
    {
        return GetWindow().GetHandle();
    }
    static DirectX::XMINT2 GetWindowSize()
    {
        return GetWindow().GetSize();
    }
    static void SetWindowSize(int width, int height)
    {
        GetWindow().SetSize(width, height);
    }
    static wchar_t* const GetTitle()
    {
        return GetWindow().GetTitle();
    }
    static void SetTitle(const wchar_t* const title)
    {
        GetWindow().SetTitle(title);
    }
    static void SetFullScreen(bool isFullScreen)
    {
        GetWindow().SetFullScreen(isFullScreen);
    }
    static ID3D11Device& GetGraphicsDevice3D()
    {
        return GetGraphics().GetDevice3D();
    }
    static ID3D11DeviceContext& GetGraphicsContext3D()
    {
        return GetGraphics().GetContext3D();
    }
    static ID2D1Device& GetGraphicsDevice2D()
    {
        return GetGraphics().GetDevice2D();
    }
    static ID2D1DeviceContext& GetGraphicsContext2D()
    {
        return GetGraphics().GetContext2D();
    }
    static IDXGISwapChain& GetGraphicsSwapChain()
    {
        return GetGraphics().GetSwapChain();
    }
    static IWICImagingFactory& GetTextureFactory()
    {
        return GetGraphics().GetTextureFactory();
    }
    static IDWriteFactory& GetTextFactory()
    {
        return GetGraphics().GetTextFactory();
    }
    static IDirectSound8& GetAudioDevice()
    {
        return GetAudio().GetDevice();
    }
    static bool GetKey(int VK_CODE)
    {
        return GetInput().GetKey(VK_CODE);
    }
    static bool GetKeyUp(int VK_CODE)
    {
        return GetInput().GetKeyUp(VK_CODE);
    }
    static bool GetKeyDown(int VK_CODE)
    {
        return GetInput().GetKeyDown(VK_CODE);
    }
    static Float2 GetMousePosition()
    {
        return GetInput().GetMousePosition();
    }
    static void SetMousePosition(float x, float y)
    {
        GetInput().SetMousePosition(x, y);
    }
    static void SetShowCursor(bool isShowCursor)
    {
        GetInput().SetShowCursor(isShowCursor);
    }
    static float GetTime()
    {
        return GetTimer().GetTime();
    }
    static float GetDeltaTime()
    {
        return GetTimer().GetDeltaTime();
    }
    static int GetFrameRate()
    {
        return GetTimer().GetFrameRate();
    }
    static void AddFont(const wchar_t* filePath)
    {
        AddFontResourceExW(filePath, FR_PRIVATE, nullptr);
    }

private:
    static Window& GetWindow()
    {
        static std::unique_ptr<Window> window(new Window());
        return *window.get();
    }
    static Graphics& GetGraphics()
    {
        static std::unique_ptr<Graphics> graphics(new Graphics());
        return *graphics.get();
    }
    static Audio& GetAudio()
    {
        static std::unique_ptr<Audio> audio(new Audio());
        return *audio.get();
    }
    static Input& GetInput()
    {
        static std::unique_ptr<Input> input(new Input());
        return *input.get();
    }
    static Timer& GetTimer()
    {
        static std::unique_ptr<Timer> timer(new Timer());
        return *timer.get();
    }
};

class Texture
{
public:
    Texture()
    {
        App::Initialize();
    }
    Texture(const wchar_t* const filePath)
    {
        App::Initialize();
        Load(filePath);
    }
    Texture(const BYTE* const buffer, int width, int height)
    {
        App::Initialize();
        Create(buffer, width, height);
    }
    ~Texture()
    {
    }
    void Load(const wchar_t* const filePath)
    {
        ATL::CComPtr<IWICBitmapDecoder> decoder = nullptr;

        App::GetTextureFactory().CreateDecoderFromFilename(filePath, 0, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &decoder);
        ATL::CComPtr<IWICBitmapFrameDecode> frame = nullptr;
        decoder->GetFrame(0, &frame);
        UINT width, height;
        frame->GetSize(&width, &height);

        WICPixelFormatGUID pixelFormat;
        frame->GetPixelFormat(&pixelFormat);
        std::unique_ptr<BYTE[]> buffer(new BYTE[width * height * 4]);

        if (pixelFormat != GUID_WICPixelFormat32bppBGRA)
        {
            ATL::CComPtr<IWICFormatConverter> formatConverter = nullptr;
            App::GetTextureFactory().CreateFormatConverter(&formatConverter);

            formatConverter->Initialize(frame, GUID_WICPixelFormat32bppBGRA, WICBitmapDitherTypeErrorDiffusion, 0, 0, WICBitmapPaletteTypeCustom);

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

        texture.Release();
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
        App::GetGraphicsDevice3D().CreateTexture2D(&textureDesc, &textureSubresourceData, &texture);

        shaderResourceView.Release();
        D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc = {};
        shaderResourceViewDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        shaderResourceViewDesc.Texture2D.MipLevels = 1;
        App::GetGraphicsDevice3D().CreateShaderResourceView(texture, &shaderResourceViewDesc, &shaderResourceView);

        samplerState.Release();
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
        App::GetGraphicsDevice3D().CreateSamplerState(&samplerDesc, &samplerState);
    }
    DirectX::XMINT2 GetSize() const
    {
        return size;
    }
    void Attach(int slot)
    {
        if (texture == nullptr)
            return;

        App::GetGraphicsContext3D().PSSetShaderResources(slot, 1, &shaderResourceView.p);
        App::GetGraphicsContext3D().PSSetSamplers(slot, 1, &samplerState.p);
    }
    ID3D11Texture2D& GetInterface()
    {
        return *texture;
    }

private:
    DirectX::XMINT2 size;
    ATL::CComPtr<ID3D11Texture2D> texture = nullptr;
    ATL::CComPtr<ID3D11ShaderResourceView> shaderResourceView = nullptr;
    ATL::CComPtr<ID3D11SamplerState> samplerState = nullptr;
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
        vertexShader.Release();
        ATL::CComPtr<ID3DBlob> vertexShaderBlob = nullptr;
        CompileShader(source, "VS", "vs_5_0", &vertexShaderBlob);
        App::GetGraphicsDevice3D().CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), nullptr, &vertexShader);

        pixelShader.Release();
        ATL::CComPtr<ID3DBlob> pixelShaderBlob = nullptr;
        CompileShader(source, "PS", "ps_5_0", &pixelShaderBlob);
        App::GetGraphicsDevice3D().CreatePixelShader(pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize(), nullptr, &pixelShader);

        inputLayout.Release();
        std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDesc;
        inputElementDesc.push_back({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 });
        inputElementDesc.push_back({ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 });
        inputElementDesc.push_back({ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 });
        inputElementDesc.push_back({ "BLENDINDICES", 0, DXGI_FORMAT_R32G32B32A32_UINT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 });
        inputElementDesc.push_back({ "BLENDINDICES", 1, DXGI_FORMAT_R32G32B32A32_UINT, 0, 48, D3D11_INPUT_PER_VERTEX_DATA, 0 });
        inputElementDesc.push_back({ "BLENDWEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 64, D3D11_INPUT_PER_VERTEX_DATA, 0 });
        inputElementDesc.push_back({ "BLENDWEIGHT", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 80, D3D11_INPUT_PER_VERTEX_DATA, 0 });

        App::GetGraphicsDevice3D().CreateInputLayout(inputElementDesc.data(), inputElementDesc.size(), vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), &inputLayout);
    }
    void SetBuffer(int slot, void* cbuffer, size_t size)
    {
        constantBuffer[slot].ptr = cbuffer;

        constantBuffer[slot].buffer.Release();
        D3D11_BUFFER_DESC constantBufferDesc = {};
        constantBufferDesc.ByteWidth = size;
        constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
        constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        App::GetGraphicsDevice3D().CreateBuffer(&constantBufferDesc, nullptr, &constantBuffer[slot].buffer);
    }
    void SetTexture(int slot, Texture* texture)
    {
        textures[slot] = texture;
    }
    void Attach()
    {
        if (vertexShader != nullptr)
            App::GetGraphicsContext3D().VSSetShader(vertexShader, nullptr, 0);

        if (pixelShader != nullptr)
            App::GetGraphicsContext3D().PSSetShader(pixelShader, nullptr, 0);

        if (inputLayout != nullptr)
            App::GetGraphicsContext3D().IASetInputLayout(inputLayout);

        for (int i = 0; i < 10; i++)
        {
            if (constantBuffer[i].ptr != nullptr)
            {
                App::GetGraphicsContext3D().UpdateSubresource(constantBuffer[i].buffer, 0, nullptr, constantBuffer[i].ptr, 0, 0);
                App::GetGraphicsContext3D().VSSetConstantBuffers(i, 1, &constantBuffer[i].buffer.p);
                App::GetGraphicsContext3D().HSSetConstantBuffers(i, 1, &constantBuffer[i].buffer.p);
                App::GetGraphicsContext3D().DSSetConstantBuffers(i, 1, &constantBuffer[i].buffer.p);
                App::GetGraphicsContext3D().GSSetConstantBuffers(i, 1, &constantBuffer[i].buffer.p);
                App::GetGraphicsContext3D().PSSetConstantBuffers(i, 1, &constantBuffer[i].buffer.p);
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
        ATL::CComPtr<ID3D11Buffer> buffer = nullptr;
    };

    ConstantBuffer constantBuffer[10];
    Texture* textures[10];
    ATL::CComPtr<ID3D11VertexShader> vertexShader = nullptr;
    ATL::CComPtr<ID3D11PixelShader> pixelShader = nullptr;
    ATL::CComPtr<ID3D11InputLayout> inputLayout = nullptr;

    void Initialize()
    {
        App::Initialize();

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

        ATL::CComPtr<ID3DBlob> errorBlob = nullptr;
        D3DCompile(source.c_str(), source.length(), nullptr, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint, shaderModel, shaderFlags, 0, out, &errorBlob);

        if (errorBlob != nullptr)
        {
            OutputDebugStringA(static_cast<char*>(errorBlob->GetBufferPointer()));
            MessageBoxA(App::GetWindowHandle(), static_cast<char*>(errorBlob->GetBufferPointer()), "Shader Error", MB_OK);
        }
    }
};
class Camera : public App::Window::Proceedable
{
public:
    Float3 position;
    Float3 angles;
    Float4 color;

    Camera()
    {
        App::Initialize();

        position = Float3(0.0f, 0.0f, 0.0f);
        angles = Float3(0.0f, 0.0f, 0.0f);
        color = Float4(1.0f, 1.0f, 1.0f, 1.0f);

        isDepthTest = false;
        SetOrthographic(static_cast<float>(App::GetWindowSize().y), -D3D11_FLOAT32_MAX, D3D11_FLOAT32_MAX);

        App::Window::AddProcedure(this);

        Create();
    }
    ~Camera()
    {
        App::Window::RemoveProcedure(this);
    }
    void SetPerspective(float fieldOfView, float nearClip, float farClip)
    {
        isPerspective = true;
        this->fieldOfView = fieldOfView;
        this->nearClip = nearClip;
        this->farClip = farClip;
        float aspectRatio = App::GetWindowSize().x / (float)App::GetWindowSize().y;
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
        float aspectRatio = App::GetWindowSize().x / (float)App::GetWindowSize().y;
        constant.projection = DirectX::XMMatrixTranspose(
            DirectX::XMMatrixOrthographicLH(size * aspectRatio, size, nearClip, farClip)
        );
    }
    void SetDepthTest(bool isDepthTest)
    {
        this->isDepthTest = isDepthTest;
    }
    void Update()
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

        App::GetGraphicsContext3D().UpdateSubresource(constantBuffer, 0, nullptr, &constant, 0, 0);
        App::GetGraphicsContext3D().VSSetConstantBuffers(0, 1, &constantBuffer.p);
        App::GetGraphicsContext3D().HSSetConstantBuffers(0, 1, &constantBuffer.p);
        App::GetGraphicsContext3D().DSSetConstantBuffers(0, 1, &constantBuffer.p);
        App::GetGraphicsContext3D().GSSetConstantBuffers(0, 1, &constantBuffer.p);
        App::GetGraphicsContext3D().PSSetConstantBuffers(0, 1, &constantBuffer.p);

        float clearColor[4] = { color.x, color.y, color.z, color.w };
        App::GetGraphicsContext3D().ClearRenderTargetView(renderTargetView, clearColor);

        if (isDepthTest)
        {
            App::GetGraphicsContext3D().ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

            App::GetGraphicsContext3D().OMSetRenderTargets(1, &renderTargetView.p, depthStencilView);
        }
        else
        {
            App::GetGraphicsContext3D().OMSetRenderTargets(1, &renderTargetView.p, nullptr);

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
    ATL::CComPtr<ID3D11RenderTargetView> renderTargetView = nullptr;
    ATL::CComPtr<ID3D11DepthStencilView> depthStencilView = nullptr;
    ATL::CComPtr<ID3D11Texture2D> renderTexture = nullptr;
    ATL::CComPtr<ID3D11Texture2D> depthTexture = nullptr;
    ATL::CComPtr<ID3D11Buffer> constantBuffer = nullptr;

    void Create()
    {
        renderTexture.Release();
        App::GetGraphicsSwapChain().GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&renderTexture));
        renderTargetView.Release();
        App::GetGraphicsDevice3D().CreateRenderTargetView(renderTexture, nullptr, &renderTargetView);

        DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
        App::GetGraphicsSwapChain().GetDesc(&swapChainDesc);

        depthTexture.Release();
        D3D11_TEXTURE2D_DESC textureDesc = {};
        textureDesc.Width = static_cast<UINT>(App::GetWindowSize().x);
        textureDesc.Height = static_cast<UINT>(App::GetWindowSize().y);
        textureDesc.MipLevels = 1;
        textureDesc.ArraySize = 1;
        textureDesc.Format = DXGI_FORMAT_R32_TYPELESS;
        textureDesc.SampleDesc.Count = swapChainDesc.SampleDesc.Count;
        textureDesc.SampleDesc.Quality = swapChainDesc.SampleDesc.Quality;
        textureDesc.Usage = D3D11_USAGE_DEFAULT;
        textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        textureDesc.CPUAccessFlags = 0;
        textureDesc.MiscFlags = 0;
        App::GetGraphicsDevice3D().CreateTexture2D(&textureDesc, nullptr, &depthTexture);

        depthStencilView.Release();
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
        App::GetGraphicsDevice3D().CreateDepthStencilView(depthTexture, &depthStencilViewDesc, &depthStencilView);

        constantBuffer.Release();
        D3D11_BUFFER_DESC constantBufferDesc = {};
        constantBufferDesc.ByteWidth = static_cast<UINT>(sizeof(Constant));
        constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
        constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        constantBufferDesc.CPUAccessFlags = 0;
        App::GetGraphicsDevice3D().CreateBuffer(&constantBufferDesc, nullptr, &constantBuffer);
    }
    void OnProceed(HWND, UINT message, WPARAM, LPARAM) override
    {
        if (message != WM_SIZE)
            return;

        if (App::GetWindowSize().x <= 0.0f || App::GetWindowSize().y <= 0.0f)
            return;

        DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
        App::GetGraphicsSwapChain().GetDesc(&swapChainDesc);

        ATL::CComPtr<ID3D11RenderTargetView> nullRenderTarget = nullptr;
        ATL::CComPtr<ID3D11DepthStencilView> nullDepthStencil = nullptr;
        App::GetGraphicsContext3D().OMSetRenderTargets(1, &nullRenderTarget, nullDepthStencil);
        renderTargetView.Release();
        depthStencilView.Release();
        renderTexture.Release();
        depthTexture.Release();
        App::GetGraphicsContext3D().Flush();
        App::GetGraphicsSwapChain().ResizeBuffers(swapChainDesc.BufferCount, static_cast<UINT>(App::GetWindowSize().x), static_cast<UINT>(App::GetWindowSize().y), swapChainDesc.BufferDesc.Format, swapChainDesc.Flags);

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
        App::Initialize();

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

        size_t indexOffset = vertices.size() - 4;
        indices.push_back(indexOffset + 0);
        indices.push_back(indexOffset + 1);
        indices.push_back(indexOffset + 2);
        indices.push_back(indexOffset + 3);
        indices.push_back(indexOffset + 2);
        indices.push_back(indexOffset + 1);

        Apply();
    }
    void CreateCube(bool shouldClear = true)
    {
        if (shouldClear)
        {
            vertices.clear();
            indices.clear();
        }

        CreatePlane(Float2(0.5f, 0.5f), Float3(0.0f, 0.0f, -0.5f), false, Float3(1.0f, 0.0f, 0.0f), Float3(0.0f, 1.0f, 0.0f), Float3(0.0f, 0.0f, 1.0f));	// front
        CreatePlane(Float2(0.5f, 0.5f), Float3(0.0f, 0.0f, 0.5f), false, Float3(-1.0f, 0.0f, 0.0f), Float3(0.0f, 1.0f, 0.0f), Float3(0.0f, 0.0f, -1.0f));	// back
        CreatePlane(Float2(0.5f, 0.5f), Float3(0.5f, 0.0f, 0.0f), false, Float3(0.0f, 0.0f, 1.0f), Float3(0.0f, 1.0f, 0.0f), Float3(-1.0f, 0.0f, 0.0f));	// left
        CreatePlane(Float2(0.5f, 0.5f), Float3(-0.5f, 0.0f, 0.0f), false, Float3(0.0f, 0.0f, -1.0f), Float3(0.0f, 1.0f, 0.0f), Float3(1.0f, 0.0f, 0.0f));	// right
        CreatePlane(Float2(0.5f, 0.5f), Float3(0.0f, 0.5f, 0.0f), false, Float3(1.0f, 0.0f, 0.0f), Float3(0.0f, 0.0f, 1.0f), Float3(0.0f, -1.0f, 0.0f));	// up
        CreatePlane(Float2(0.5f, 0.5f), Float3(0.0f, -0.5f, 0.0f), false, Float3(1.0f, 0.0f, 0.0f), Float3(0.0f, 0.0f, -1.0f), Float3(0.0f, 1.0f, 0.0f));	// down
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
        rasterizerState.Release();
        App::GetGraphicsDevice3D().CreateRasterizerState(&rasterizerDesc, &rasterizerState);
    }
    void Apply()
    {
        vertexBuffer.Release();
        if (vertices.size() > 0)
        {
            D3D11_BUFFER_DESC vertexBufferDesc = {};
            vertexBufferDesc.ByteWidth = sizeof(Vertex) * vertices.size();
            vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
            vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
            D3D11_SUBRESOURCE_DATA vertexSubresourceData = {};
            vertexSubresourceData.pSysMem = vertices.data();
            App::GetGraphicsDevice3D().CreateBuffer(&vertexBufferDesc, &vertexSubresourceData, &vertexBuffer);
        }

        indexBuffer.Release();
        if (indices.size() > 0)
        {
            D3D11_BUFFER_DESC indexBufferDesc = {};
            indexBufferDesc.ByteWidth = sizeof(int) * indices.size();
            indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
            indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
            D3D11_SUBRESOURCE_DATA indexSubresourceData = {};
            indexSubresourceData.pSysMem = indices.data();
            App::GetGraphicsDevice3D().CreateBuffer(&indexBufferDesc, &indexSubresourceData, &indexBuffer);
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

        App::GetGraphicsContext3D().RSSetState(rasterizerState);

        UINT stride = sizeof(Vertex);
        UINT offset = 0;
        App::GetGraphicsContext3D().IASetVertexBuffers(0, 1, &vertexBuffer.p, &stride, &offset);

        if (indexBuffer == nullptr)
        {
            App::GetGraphicsContext3D().Draw(vertices.size(), 0);
        }
        else
        {
            App::GetGraphicsContext3D().IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
            App::GetGraphicsContext3D().DrawIndexed(indices.size(), 0, 0);
        }
    }

private:
    struct Constant
    {
        DirectX::XMMATRIX world;
    };

    Material material;
    Constant constant;
    ATL::CComPtr<ID3D11Buffer> vertexBuffer = nullptr;
    ATL::CComPtr<ID3D11Buffer> indexBuffer = nullptr;
    ATL::CComPtr<ID3D11RasterizerState> rasterizerState = nullptr;
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
        App::Initialize();

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

        this->text = text;

        length = DirectX::XMINT2(0, 1);
        int maxLength = 0;
        for (int i = 0; i < text.length(); i++)
        {
            if (text[i] == L'\n')
            {
                maxLength = 0;
                length.y++;
                continue;
            }

            maxLength++;

            if (length.x < maxLength)
            {
                length.x = maxLength;
            }
        }

        DirectX::XMINT2 textureSize(static_cast<int>(length.x * fontSize), static_cast<int>(length.y * fontSize * 2.0f));
        std::unique_ptr<BYTE[]> buffer(new BYTE[textureSize.x * textureSize.y * 4]);
        texture.Create(buffer.get(), textureSize.x, textureSize.y);

        ATL::CComPtr<IDXGISurface> surface = nullptr;
        texture.GetInterface().QueryInterface(&surface);

        D2D1_BITMAP_PROPERTIES1 bitmapProperties = {};
        bitmapProperties.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
        bitmapProperties.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
        bitmapProperties.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET;

        bitmap.Release();
        App::GetGraphicsContext2D().CreateBitmapFromDxgiSurface(surface, bitmapProperties, &bitmap);

        brush.Reset();
        App::GetGraphicsContext2D().CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), brush.GetAddressOf());
        App::GetGraphicsContext2D().SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_ALIASED);

        textFormat.Reset();
        App::GetTextFactory().CreateTextFormat(fontFace, nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, fontSize, L"ja-jp", textFormat.GetAddressOf());

        textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
        textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

        mesh.GetMaterial().SetTexture(0, &texture);

        SetPivot(0.0f);
    }
    void Draw()
    {
        App::GetGraphicsContext2D().SetTarget(bitmap);

        App::GetGraphicsContext2D().BeginDraw();
        App::GetGraphicsContext2D().Clear(D2D1::ColorF(1.0f, 1.0f, 1.0f, 0.0f));

        Microsoft::WRL::ComPtr<IDWriteTextLayout> textLayout = nullptr;
        App::GetTextFactory().CreateTextLayout(text.c_str(), (UINT32)text.length(), textFormat.Get(), static_cast<float>(texture.GetSize().x), static_cast<float>(texture.GetSize().y), textLayout.GetAddressOf());

        App::GetGraphicsContext2D().DrawTextLayout(D2D1::Point2F(0.0f, 0.0f), textLayout.Get(), brush.Get());

        App::GetGraphicsContext2D().EndDraw();

        Sprite::Draw();
    }
    void Load(const wchar_t* const filePath) = delete;
    void Create(const BYTE* const buffer, int width, int height) = delete;

private:
    std::wstring text;
    DirectX::XMINT2 length;
    ATL::CComPtr<ID2D1Bitmap1> bitmap = nullptr;
    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush = nullptr;
    Microsoft::WRL::ComPtr<IDWriteTextFormat> textFormat = nullptr;
};
class Sound : public App::Window::Proceedable
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
        App::Window::RemoveProcedure(this);
    }
    void Load(const wchar_t* const filePath)
    {
        App::GetAudioDevice();

        ATL::CComPtr<IStream> stream = nullptr;
        SHCreateStreamOnFileW(filePath, STGM_READ, &stream);

        ATL::CComPtr<IMFByteStream> byteStream = nullptr;
        MFCreateMFByteStreamOnStream(stream, &byteStream);

        ATL::CComPtr<IMFAttributes> attributes = nullptr;
        MFCreateAttributes(&attributes, 1);

        sourceReader.Release();
        MFCreateSourceReaderFromByteStream(byteStream, attributes, &sourceReader);

        ATL::CComPtr<IMFMediaType> mediaType = nullptr;
        MFCreateMediaType(&mediaType);
        mediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
        mediaType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);

        sourceReader->SetCurrentMediaType((DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, nullptr, mediaType);
        mediaType.Release();
        sourceReader->GetCurrentMediaType((DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, &mediaType);

        UINT32 waveFormatSize = sizeof(WAVEFORMATEX);
        MFCreateWaveFormatExFromMFMediaType(mediaType, &format, &waveFormatSize);

        ATL::CComPtr<IMFSample> sample = nullptr;
        DWORD flags = 0;
        sourceReader->ReadSample((DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, &flags, nullptr, &sample);

        ATL::CComPtr<IMFMediaBuffer> mediaBuffer = nullptr;
        sample->ConvertToContiguousBuffer(&mediaBuffer);

        mediaBuffer->GetMaxLength(&bufferSize);
        bufferSize -= format->nBlockAlign;

        DSBUFFERDESC bufferDesc = {};
        bufferDesc.dwSize = sizeof(DSBUFFERDESC);
        bufferDesc.dwFlags = DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY | DSBCAPS_GETCURRENTPOSITION2;
        bufferDesc.dwBufferBytes = bufferSize * 2;
        bufferDesc.lpwfxFormat = format;

        soundBuffer.Release();
        App::GetAudioDevice().CreateSoundBuffer(&bufferDesc, &soundBuffer, nullptr);
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

    ATL::CComPtr<IMFSourceReader> sourceReader = nullptr;
    ATL::CComPtr<IDirectSoundBuffer> soundBuffer = nullptr;
    DWORD bufferSize;
    int bufferIndex = 0;
    WAVEFORMATEX* format;
    State state = stop;

    void Initialize()
    {
        App::Initialize();

        App::Window::AddProcedure(this);
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

        ATL::CComPtr<IMFSample> sample = nullptr;
        DWORD flags = 0;
        sourceReader->ReadSample((DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, &flags, nullptr, &sample);

        if (flags & MF_SOURCE_READERF_ENDOFSTREAM)
        {
            if (!properties.isLoop)
            {
                Stop();
                return;
            }

            Reset();

            sample.Release();
            sourceReader->ReadSample((DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, &flags, nullptr, &sample);
        }

        ATL::CComPtr<IMFMediaBuffer> mediaBuffer = nullptr;
        sample->ConvertToContiguousBuffer(&mediaBuffer);
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


}
