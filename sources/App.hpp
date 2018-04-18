// © 2017 itukikikuti
// https://github.com/itukikikuti/XLibrary11
// MIT License
#pragma once

#define OEMRESOURCE
#include <cstdio>
#include <forward_list>
#include <fstream>
#include <memory>
#include <vector>
#include <Windows.h>
#include <atlbase.h>
#include <d2d1_1.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <dshow.h>
#include <dwrite.h>
#include <wincodec.h>
#include <wrl.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "strmiids.lib")

XLIBRARY_NAMESPACE_BEGIN

#define MAIN() APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)

#include "Utility.hpp"

class App final
{
public:
#include "Window.hpp"
#include "Graphics.hpp"
#include "Input.hpp"
#include "Timer.hpp"

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

#include "Texture.hpp"
#include "Material.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"
#include "Sprite.hpp"
#include "Text.hpp"
#include "Sound.hpp"

XLIBRARY_NAMESPACE_END
