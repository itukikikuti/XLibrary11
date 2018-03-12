// © 2017 itukikikuti
// https://github.com/itukikikuti/XLibrary11
// MIT License
#pragma once

#define OEMRESOURCE
#include <forward_list>
#include <fstream>
#include <memory>
#include <vector>
#include <Windows.h>
#include <atlbase.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <Shlwapi.h>
#include <wincodec.h>
#include <xaudio2.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "mfuuid.lib")
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "xaudio2.lib")

namespace XLibrary11
{

#define MAIN() APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)

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
    operator DirectX::XMVECTOR() const noexcept
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
    operator DirectX::XMVECTOR() const noexcept
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
    operator DirectX::XMVECTOR() const noexcept
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
class Graphics : public App::Window::Proceedable
{
public:
    Graphics()
    {
        App::Initialize();

        UINT flags = 0;
#if defined(_DEBUG)
        flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

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
        D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flags, featureLevels.data(), featureLevels.size(), D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device, nullptr, &context);

        context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

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
        device->CreateBlendState(&blendDesc, &blendState);
        context->OMSetBlendState(blendState, blendFactor, 0xffffffff);

        D3D11_BUFFER_DESC constantBufferDesc = {};
        constantBufferDesc.ByteWidth = sizeof(Constant);
        constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
        constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        device->CreateBuffer(&constantBufferDesc, nullptr, &constantBuffer);

        App::AddProcedure(this);

        CreateRenderTarget();
    }
    ~Graphics()
    {
        App::RemoveProcedure(this);
    }
    ID3D11Device& GetDevice() const
    {
        return *device;
    }
    IDXGISwapChain& GetMemory() const
    {
        return *swapChain;
    }
    ID3D11DeviceContext& GetContext() const
    {
        return *context;
    }
    void Update()
    {
        swapChain->Present(1, 0);

        context->UpdateSubresource(constantBuffer, 0, nullptr, &constant, 0, 0);
        context->VSSetConstantBuffers(1, 1, &constantBuffer.p);
        context->HSSetConstantBuffers(1, 1, &constantBuffer.p);
        context->DSSetConstantBuffers(1, 1, &constantBuffer.p);
        context->GSSetConstantBuffers(1, 1, &constantBuffer.p);
        context->PSSetConstantBuffers(1, 1, &constantBuffer.p);

        context->OMSetRenderTargets(1, &renderTargetView.p, nullptr);

        static float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        context->ClearRenderTargetView(renderTargetView, color);
    }

private:
    struct Constant
    {
        DirectX::XMMATRIX view;
        DirectX::XMMATRIX projection;
    };

    Constant constant;
    ATL::CComPtr<ID3D11Device> device = nullptr;
    ATL::CComPtr<IDXGISwapChain> swapChain = nullptr;
    ATL::CComPtr<ID3D11DeviceContext> context = nullptr;
    ATL::CComPtr<ID3D11RenderTargetView> renderTargetView = nullptr;
    ATL::CComPtr<ID3D11Texture2D> renderTexture = nullptr;
    ATL::CComPtr<ID3D11Buffer> constantBuffer = nullptr;

    void CreateRenderTarget()
    {
        D3D11_VIEWPORT viewPort = {};
        viewPort.Width = static_cast<float>(App::GetWindowSize().x);
        viewPort.Height = static_cast<float>(App::GetWindowSize().y);
        context->RSSetViewports(1, &viewPort);

        swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&renderTexture));
        device->CreateRenderTargetView(renderTexture, nullptr, &renderTargetView);

        constant.view = DirectX::XMMatrixIdentity();
        constant.projection = DirectX::XMMatrixOrthographicLH(static_cast<float>(App::GetWindowSize().x), static_cast<float>(App::GetWindowSize().y), -10000.0f, 10000.0f);
    }
    void OnProceed(HWND, UINT message, WPARAM, LPARAM) override
    {
        if (message != WM_SIZE)
            return;

        if (App::GetWindowSize().x <= 0.0f || App::GetWindowSize().y <= 0.0f)
            return;

        DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
        swapChain->GetDesc(&swapChainDesc);

        ATL::CComPtr<ID3D11RenderTargetView> nullRenderTarget = nullptr;
        context->OMSetRenderTargets(1, &nullRenderTarget, nullptr);
        renderTargetView.Release();
        renderTexture.Release();
        context->Flush();
        swapChain->ResizeBuffers(swapChainDesc.BufferCount, App::GetWindowSize().x, App::GetWindowSize().y, swapChainDesc.BufferDesc.Format, 0);

        CreateRenderTarget();
    }
};
class Audio
{
public:
    Audio()
    {
        App::Initialize();

        App::GetWindowHandle();

        XAudio2Create(&audioEngine);

        audioEngine->CreateMasteringVoice(&masteringVoice);

        MFStartup(MF_VERSION);
    }
    ~Audio()
    {
        MFShutdown();

        masteringVoice->DestroyVoice();

        audioEngine->StopEngine();
    }
    IXAudio2& GetEngine() const
    {
        return *audioEngine;
    }

private:
    ATL::CComPtr<IXAudio2> audioEngine = nullptr;
    IXAudio2MasteringVoice* masteringVoice = nullptr;
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

        mousePosition.x = x;
        mousePosition.y = y;
        POINT point = { static_cast<int>(x), static_cast<int>(y) };
        ClientToScreen(App::GetWindowHandle(), &point);
        SetCursorPos(point.x, point.y);
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
        mousePosition = Float2(static_cast<float>(point.x), static_cast<float>(point.y));

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
        deltaTime = static_cast<float>((count.QuadPart - preCount.QuadPart) / frequency.QuadPart);
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

    static constexpr wchar_t* NAME = L"XLibrary11";

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
    static void AddProcedure(Window::Proceedable* const procedure)
    {
        GetWindow().AddProcedure(procedure);
    }
    static void RemoveProcedure(Window::Proceedable* const procedure)
    {
        GetWindow().RemoveProcedure(procedure);
    }
    static ID3D11Device& GetGraphicsDevice()
    {
        return GetGraphics().GetDevice();
    }
    static ID3D11DeviceContext& GetGraphicsContext()
    {
        return GetGraphics().GetContext();
    }
    static IDXGISwapChain& GetGraphicsMemory()
    {
        return GetGraphics().GetMemory();
    }
    static IXAudio2& GetAudioEngine()
    {
        return GetAudio().GetEngine();
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
    ~Texture()
    {
    }
    void Load(const wchar_t* const filePath)
    {
        static ATL::CComPtr<IWICImagingFactory> factory = nullptr;
        if (factory == nullptr)
            CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&factory));

        ATL::CComPtr<IWICBitmapDecoder> decoder = nullptr;

        factory->CreateDecoderFromFilename(filePath, 0, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &decoder);
        ATL::CComPtr<IWICBitmapFrameDecode> frame = nullptr;
        decoder->GetFrame(0, &frame);
        UINT width, height;
        frame->GetSize(&width, &height);

        WICPixelFormatGUID pixelFormat;
        frame->GetPixelFormat(&pixelFormat);
        std::unique_ptr<BYTE[]> buffer(new BYTE[width * height * 4]);

        if (pixelFormat != GUID_WICPixelFormat32bppRGBA)
        {
            ATL::CComPtr<IWICFormatConverter> formatConverter = nullptr;
            factory->CreateFormatConverter(&formatConverter);

            formatConverter->Initialize(frame, GUID_WICPixelFormat32bppRGBA, WICBitmapDitherTypeErrorDiffusion, 0, 0, WICBitmapPaletteTypeCustom);

            formatConverter->CopyPixels(0, width * 4, width * height * 4, buffer.get());
        }
        else
        {
            frame->CopyPixels(0, width * 4, width * height * 4, buffer.get());
        }

        size = DirectX::XMINT2(width, height);

        texture.Release();
        D3D11_TEXTURE2D_DESC textureDesc = {};
        textureDesc.Width = width;
        textureDesc.Height = height;
        textureDesc.MipLevels = 1;
        textureDesc.ArraySize = 1;
        textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        textureDesc.SampleDesc.Count = 1;
        textureDesc.SampleDesc.Quality = 0;
        textureDesc.Usage = D3D11_USAGE_DEFAULT;
        textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        textureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
        textureDesc.MiscFlags = 0;

        D3D11_SUBRESOURCE_DATA textureSubresourceData = {};
        textureSubresourceData.pSysMem = buffer.get();
        textureSubresourceData.SysMemPitch = width * 4;
        textureSubresourceData.SysMemSlicePitch = width * height * 4;
        App::GetGraphicsDevice().CreateTexture2D(&textureDesc, &textureSubresourceData, &texture);

        shaderResourceView.Release();
        D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc = {};
        shaderResourceViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        shaderResourceViewDesc.Texture2D.MipLevels = 1;
        App::GetGraphicsDevice().CreateShaderResourceView(texture, &shaderResourceViewDesc, &shaderResourceView);

        samplerState.Release();
        D3D11_SAMPLER_DESC samplerDesc = {};
        samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
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
        App::GetGraphicsDevice().CreateSamplerState(&samplerDesc, &samplerState);
    }
    DirectX::XMINT2 GetSize() const
    {
        return size;
    }
    void Attach(int slot)
    {
        if (texture == nullptr)
            return;

        App::GetGraphicsContext().PSSetShaderResources(slot, 1, &shaderResourceView.p);
        App::GetGraphicsContext().PSSetSamplers(slot, 1, &samplerState.p);
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
    Material(char* source)
    {
        Initialize();
        Create(source);
    }
    Material(const wchar_t* const filePath)
    {
        Initialize();
        Load(filePath);
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

        Create(source.c_str());
    }
    void SetBuffer(void* cbuffer, size_t size)
    {
        buffer = cbuffer;

        constantBuffer.Release();
        D3D11_BUFFER_DESC constantBufferDesc = {};
        constantBufferDesc.ByteWidth = size;
        constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
        constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        App::GetGraphicsDevice().CreateBuffer(&constantBufferDesc, nullptr, &constantBuffer);
    }
    void SetTexture(int slot, Texture* texture)
    {
        textures[slot] = texture;
    }
    void Attach()
    {
        if (vertexShader != nullptr)
            App::GetGraphicsContext().VSSetShader(vertexShader, nullptr, 0);

        if (pixelShader != nullptr)
            App::GetGraphicsContext().PSSetShader(pixelShader, nullptr, 0);

        if (inputLayout != nullptr)
            App::GetGraphicsContext().IASetInputLayout(inputLayout);

        if (buffer != nullptr)
        {
            App::GetGraphicsContext().UpdateSubresource(constantBuffer, 0, nullptr, buffer, 0, 0);
            App::GetGraphicsContext().VSSetConstantBuffers(0, 1, &constantBuffer.p);
            App::GetGraphicsContext().HSSetConstantBuffers(0, 1, &constantBuffer.p);
            App::GetGraphicsContext().DSSetConstantBuffers(0, 1, &constantBuffer.p);
            App::GetGraphicsContext().GSSetConstantBuffers(0, 1, &constantBuffer.p);
            App::GetGraphicsContext().PSSetConstantBuffers(0, 1, &constantBuffer.p);
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
    void* buffer = nullptr;
    Texture* textures[10];
    ATL::CComPtr<ID3D11VertexShader> vertexShader = nullptr;
    ATL::CComPtr<ID3D11PixelShader> pixelShader = nullptr;
    ATL::CComPtr<ID3D11InputLayout> inputLayout = nullptr;
    ATL::CComPtr<ID3D11Buffer> constantBuffer = nullptr;

    void Initialize()
    {
        App::Initialize();

        for (int i = 0; i < 10; i++)
        {
            textures[i] = nullptr;
        }
    }
    void Create(const char* source)
    {
        vertexShader.Release();
        ATL::CComPtr<ID3DBlob> vertexShaderBlob = nullptr;
        CompileShader(source, "VS", "vs_5_0", &vertexShaderBlob);
        App::GetGraphicsDevice().CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), nullptr, &vertexShader);

        pixelShader.Release();
        ATL::CComPtr<ID3DBlob> pixelShaderBlob = nullptr;
        CompileShader(source, "PS", "ps_5_0", &pixelShaderBlob);
        App::GetGraphicsDevice().CreatePixelShader(pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize(), nullptr, &pixelShader);

        inputLayout.Release();
        std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDesc;
        inputElementDesc.push_back({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 });
        inputElementDesc.push_back({ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 });
        inputElementDesc.push_back({ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 });

        App::GetGraphicsDevice().CreateInputLayout(inputElementDesc.data(), inputElementDesc.size(), vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), &inputLayout);
    }
    static void CompileShader(const char* const source, const char* const entryPoint, const char* const shaderModel, ID3DBlob** out)
    {
        DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(_DEBUG)
        shaderFlags |= D3DCOMPILE_DEBUG;
#endif

        ATL::CComPtr<ID3DBlob> errorBlob = nullptr;
        D3DCompile(source, strlen(source), nullptr, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint, shaderModel, shaderFlags, 0, out, &errorBlob);

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

    Camera()
    {
        App::Initialize();
        Initialize();
        Create();
    }
    ~Camera()
    {
        App::RemoveProcedure(this);
    }
    void SetPerspective(float fieldOfView, float nearClip, float farClip)
    {
        this->fieldOfView = fieldOfView;
        this->nearClip = nearClip;
        this->farClip = farClip;
        constant.projection = DirectX::XMMatrixTranspose(
            DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(fieldOfView), App::GetWindowSize().x / (float)App::GetWindowSize().y, nearClip, farClip)
        );
    }
    void Update()
    {
        constant.view = DirectX::XMMatrixTranspose(
            DirectX::XMMatrixInverse(
                nullptr,
                DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(angles.z)) *
                DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(angles.y)) *
                DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(angles.x)) *
                DirectX::XMMatrixTranslation(position.x, position.y, position.z)
            )
        );

        App::GetGraphicsContext().UpdateSubresource(constantBuffer, 0, nullptr, &constant, 0, 0);
        App::GetGraphicsContext().VSSetConstantBuffers(1, 1, &constantBuffer.p);
        App::GetGraphicsContext().HSSetConstantBuffers(1, 1, &constantBuffer.p);
        App::GetGraphicsContext().DSSetConstantBuffers(1, 1, &constantBuffer.p);
        App::GetGraphicsContext().GSSetConstantBuffers(1, 1, &constantBuffer.p);
        App::GetGraphicsContext().PSSetConstantBuffers(1, 1, &constantBuffer.p);

        App::GetGraphicsContext().OMSetRenderTargets(1, &renderTargetView.p, depthStencilView);

        static float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        App::GetGraphicsContext().ClearRenderTargetView(renderTargetView, color);
        App::GetGraphicsContext().ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    }

private:
    struct Constant
    {
        DirectX::XMMATRIX view;
        DirectX::XMMATRIX projection;
    };

    float fieldOfView;
    float nearClip;
    float farClip;
    Constant constant;
    ATL::CComPtr<ID3D11RenderTargetView> renderTargetView = nullptr;
    ATL::CComPtr<ID3D11DepthStencilView> depthStencilView = nullptr;
    ATL::CComPtr<ID3D11Texture2D> renderTexture = nullptr;
    ATL::CComPtr<ID3D11Texture2D> depthTexture = nullptr;
    ATL::CComPtr<ID3D11Buffer> constantBuffer = nullptr;

    void Initialize()
    {
        position = Float3(0.0f, 0.0f, -5.0f);
        angles = Float3(0.0f, 0.0f, 0.0f);

        SetPerspective(60.0f, 0.1f, 1000.0f);

        App::AddProcedure(this);
    }
    void Create()
    {
        renderTexture.Release();
        App::GetGraphicsMemory().GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&renderTexture));
        renderTargetView.Release();
        App::GetGraphicsDevice().CreateRenderTargetView(renderTexture, nullptr, &renderTargetView);

        DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
        App::GetGraphicsMemory().GetDesc(&swapChainDesc);

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
        App::GetGraphicsDevice().CreateTexture2D(&textureDesc, nullptr, &depthTexture);

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
        App::GetGraphicsDevice().CreateDepthStencilView(depthTexture, &depthStencilViewDesc, &depthStencilView);

        constantBuffer.Release();
        D3D11_BUFFER_DESC constantBufferDesc = {};
        constantBufferDesc.ByteWidth = static_cast<UINT>(sizeof(Constant));
        constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
        constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        constantBufferDesc.CPUAccessFlags = 0;
        App::GetGraphicsDevice().CreateBuffer(&constantBufferDesc, nullptr, &constantBuffer);
    }
    void OnProceed(HWND, UINT message, WPARAM, LPARAM) override
    {
        if (message != WM_SIZE)
            return;

        if (App::GetWindowSize().x <= 0.0f || App::GetWindowSize().y <= 0.0f)
            return;

        DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
        App::GetGraphicsMemory().GetDesc(&swapChainDesc);

        ATL::CComPtr<ID3D11RenderTargetView> nullRenderTarget = nullptr;
        ATL::CComPtr<ID3D11DepthStencilView> nullDepthStencil = nullptr;
        App::GetGraphicsContext().OMSetRenderTargets(1, &nullRenderTarget, nullDepthStencil);
        renderTargetView.Release();
        depthStencilView.Release();
        renderTexture.Release();
        depthTexture.Release();
        App::GetGraphicsContext().Flush();
        App::GetGraphicsMemory().ResizeBuffers(swapChainDesc.BufferCount, static_cast<UINT>(App::GetWindowSize().x), static_cast<UINT>(App::GetWindowSize().y), swapChainDesc.BufferDesc.Format, swapChainDesc.Flags);

        SetPerspective(fieldOfView, nearClip, farClip);
        Create();
    }
};
class Mesh {
public:
    Float3 position;
    Float3 angles;
    Float3 scale;
    std::vector<Vertex> vertices;
    std::vector<UINT> indices;
    Material material;

    Mesh()
    {
        App::Initialize();

        position = Float3(0.0f, 0.0f, 0.0f);
        angles = Float3(0.0f, 0.0f, 0.0f);
        scale = Float3(1.0f, 1.0f, 1.0f);

        material = Material(
            "cbuffer Object : register(b0)"
            "{"
            "    matrix world;"
            "};"
            "cbuffer Camera : register(b1)"
            "{"
            "    matrix view;"
            "    matrix projection;"
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
        Apply();
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
    }
    void CreateCube(bool shouldClear = true)
    {
        if (shouldClear)
        {
            vertices.clear();
            indices.clear();
        }

        CreatePlane(Float2(0.5f, 0.5f), Float3(0.0f, 0.0f, -0.5f), false, Float3(1.0f, 0.0f, 0.0f), Float3(0.0f, 1.0f, 0.0f), Float3(0.0f, 0.0f, 1.0f));		// front
        CreatePlane(Float2(0.5f, 0.5f), Float3(0.0f, 0.0f, 0.5f), false, Float3(-1.0f, 0.0f, 0.0f), Float3(0.0f, 1.0f, 0.0f), Float3(0.0f, 0.0f, -1.0f));	// back
        CreatePlane(Float2(0.5f, 0.5f), Float3(0.5f, 0.0f, 0.0f), false, Float3(0.0f, 0.0f, 1.0f), Float3(0.0f, 1.0f, 0.0f), Float3(-1.0f, 0.0f, 0.0f));		// left
        CreatePlane(Float2(0.5f, 0.5f), Float3(-0.5f, 0.0f, 0.0f), false, Float3(0.0f, 0.0f, -1.0f), Float3(0.0f, 1.0f, 0.0f), Float3(1.0f, 0.0f, 0.0f));	// right
        CreatePlane(Float2(0.5f, 0.5f), Float3(0.0f, 0.5f, 0.0f), false, Float3(1.0f, 0.0f, 0.0f), Float3(0.0f, 0.0f, 1.0f), Float3(0.0f, -1.0f, 0.0f));		// up
        CreatePlane(Float2(0.5f, 0.5f), Float3(0.0f, -0.5f, 0.0f), false, Float3(1.0f, 0.0f, 0.0f), Float3(0.0f, 0.0f, -1.0f), Float3(0.0f, 1.0f, 0.0f));	// down
    }
    void SetCullingMode(D3D11_CULL_MODE cullingMode)
    {
        D3D11_RASTERIZER_DESC rasterizerDesc = {};
        rasterizerDesc.FillMode = D3D11_FILL_SOLID;
        rasterizerDesc.CullMode = cullingMode;
        App::GetGraphicsDevice().CreateRasterizerState(&rasterizerDesc, &rasterizerState);
    }
    void Apply()
    {
        if (vertices.size() > 0)
        {
            vertexBuffer.Release();
            D3D11_BUFFER_DESC vertexBufferDesc = {};
            vertexBufferDesc.ByteWidth = sizeof(Vertex) * vertices.size();
            vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
            vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
            D3D11_SUBRESOURCE_DATA vertexSubresourceData = {};
            vertexSubresourceData.pSysMem = vertices.data();
            App::GetGraphicsDevice().CreateBuffer(&vertexBufferDesc, &vertexSubresourceData, &vertexBuffer);
        }

        if (indices.size() > 0)
        {
            indexBuffer.Release();
            D3D11_BUFFER_DESC indexBufferDesc = {};
            indexBufferDesc.ByteWidth = sizeof(int) * indices.size();
            indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
            indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
            D3D11_SUBRESOURCE_DATA indexSubresourceData = {};
            indexSubresourceData.pSysMem = indices.data();
            App::GetGraphicsDevice().CreateBuffer(&indexBufferDesc, &indexSubresourceData, &indexBuffer);
        }

        material.SetBuffer(&constant, sizeof(Constant));
    }
    void Draw()
    {
        if (vertexBuffer == nullptr)
            return;

        material.Attach();

        constant.world = DirectX::XMMatrixTranspose(
            DirectX::XMMatrixScaling(scale.x, scale.y, scale.z) *
            DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(angles.z)) *
            DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(angles.y)) *
            DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(angles.x)) *
            DirectX::XMMatrixTranslation(position.x, position.y, position.z)
        );

        App::GetGraphicsContext().RSSetState(rasterizerState);

        UINT stride = sizeof(Vertex);
        UINT offset = 0;
        App::GetGraphicsContext().IASetVertexBuffers(0, 1, &vertexBuffer.p, &stride, &offset);

        if (indexBuffer == nullptr)
        {
            App::GetGraphicsContext().Draw(vertices.size(), 0);
        }
        else
        {
            App::GetGraphicsContext().IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
            App::GetGraphicsContext().DrawIndexed(indices.size(), 0, 0);
        }
    }

private:
    struct Constant
    {
        DirectX::XMMATRIX world;
    };

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
    Texture texture;

    Sprite(const wchar_t* const filePath)
    {
        App::Initialize();
        Initialize();
        Load(filePath);
    }
    ~Sprite()
    {
    }
    void Load(const wchar_t* const filePath)
    {
        texture.Load(filePath);

        mesh.material.SetTexture(0, &texture);

        Float2 textureSize(texture.GetSize().x, texture.GetSize().y);
        mesh.CreatePlane(textureSize / 2.0f);
        
        mesh.Apply();
    }
    void Draw()
    {
        mesh.position = position;
        mesh.angles = angles;
        mesh.scale = scale;
        mesh.Draw();
    }
private:
    Mesh mesh;
    
    void Initialize()
    {
        position = Float3(0.0f, 0.0f, 0.0f);
        angles = Float3(0.0f, 0.0f, 0.0f);
        scale = Float3(1.0f, 1.0f, 1.0f);

        mesh.material = Material(
            "cbuffer Object : register(b0)"
            "{"
            "    matrix world;"
            "};"
            "cbuffer Camera : register(b1)"
            "{"
            "    matrix view;"
            "    matrix projection;"
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
            "    return texture0.Sample(sampler0, pixel.uv);"
            "}"
        );
    }
};
class Voice : public IXAudio2VoiceCallback
{
public:
    Voice(const wchar_t* const filePath)
    {
        App::Initialize();
        Load(filePath);
    }
    ~Voice()
    {
        sourceVoice->DestroyVoice();
    }
    void Load(const wchar_t* const filePath)
    {
        App::GetAudioEngine();

        ATL::CComPtr<IStream> stream;
        SHCreateStreamOnFileW(filePath, STGM_READ, &stream);

        ATL::CComPtr<IMFByteStream> byteStream;
        MFCreateMFByteStreamOnStream(stream, &byteStream);

        ATL::CComPtr<IMFAttributes> attributes;
        MFCreateAttributes(&attributes, 1);

        MFCreateSourceReaderFromByteStream(byteStream, attributes, &sourceReader);

        ATL::CComPtr<IMFMediaType> mediaType;
        MFCreateMediaType(&mediaType);
        mediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
        mediaType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);

        sourceReader->SetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, nullptr, mediaType);

        mediaType.Release();
        sourceReader->GetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, &mediaType);

        UINT32 waveFormatSize = 0;
        WAVEFORMATEX* waveFormat;
        MFCreateWaveFormatExFromMFMediaType(mediaType, &waveFormat, &waveFormatSize);

        App::GetAudioEngine().CreateSourceVoice(&sourceVoice, waveFormat, XAUDIO2_VOICE_NOPITCH, 1.0f, this);
    }
    void Play()
    {
        sourceVoice->Start();
        SubmitBuffer();
    }

private:
    ATL::CComPtr<IMFSourceReader> sourceReader = nullptr;
    IXAudio2SourceVoice* sourceVoice = nullptr;

    void SubmitBuffer()
    {
        ATL::CComPtr<IMFSample> sample;
        DWORD flags = 0;
        sourceReader->ReadSample(MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, &flags, nullptr, &sample);

        if (flags & MF_SOURCE_READERF_ENDOFSTREAM)
        {
            PROPVARIANT position = {};
            position.vt = VT_I8;
            position.hVal.QuadPart = 0;
            sourceReader->SetCurrentPosition(GUID_NULL, position);

            sample.Release();
            sourceReader->ReadSample(MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, nullptr, &flags, nullptr, &sample);
        }

        ATL::CComPtr<IMFMediaBuffer> mediaBuffer;
        sample->ConvertToContiguousBuffer(&mediaBuffer);

        DWORD audioDataLength = 0;
        BYTE* audioData;
        mediaBuffer->Lock(&audioData, nullptr, &audioDataLength);
        mediaBuffer->Unlock();

        XAUDIO2_BUFFER audioBuffer = {};
        audioBuffer.AudioBytes = audioDataLength;
        audioBuffer.pAudioData = audioData;
        sourceVoice->SubmitSourceBuffer(&audioBuffer);
    }
    void _stdcall OnBufferEnd(void*) override
    {
        SubmitBuffer();
    }
    void _stdcall OnBufferStart(void*) override
    {
    }
    void _stdcall OnLoopEnd(void*) override
    {
    }
    void _stdcall OnStreamEnd() override
    {
    }
    void _stdcall OnVoiceError(void*, HRESULT) override
    {
    }
    void _stdcall OnVoiceProcessingPassStart(UINT32) override
    {
    }
    void _stdcall OnVoiceProcessingPassEnd() override
    {
    }
};

}
