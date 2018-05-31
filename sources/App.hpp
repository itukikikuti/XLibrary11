// © 2017 itukikikuti
// https://github.com/itukikikuti/XLibrary11
// MIT License
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

XLIBRARY_NAMESPACE_BEGIN

using namespace DirectX;

#include "Utility.hpp"

class App final
{
public:
#include "Window.hpp"
#include "Graphics.hpp"
#include "Audio.hpp"
#include "Input.hpp"
#include "Timer.hpp"
#include "Random.hpp"

    App() = delete;
    static bool Refresh()
    {
        GetGraphicsInstance().Update();
        GetInputInstance().Update();
        GetTimerInstance().Update();
        return GetWindowInstance().Update();
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
        return GetWindowInstance().GetHandle();
    }
    static DirectX::XMINT2 GetWindowSize()
    {
        return GetWindowInstance().GetSize();
    }
    static void SetWindowSize(int width, int height)
    {
        GetWindowInstance().SetSize(width, height);
    }
    static wchar_t* const GetTitle()
    {
        return GetWindowInstance().GetTitle();
    }
    static void SetTitle(const wchar_t* const title)
    {
        GetWindowInstance().SetTitle(title);
    }
    static void SetFullScreen(bool isFullScreen)
    {
        GetWindowInstance().SetFullScreen(isFullScreen);
    }
    static void AddWindowProcedure(Window::Proceedable* const procedure)
    {
        GetWindowInstance().AddProcedure(procedure);
    }
    static void RemoveWindowProcedure(Window::Proceedable* const procedure)
    {
        GetWindowInstance().RemoveProcedure(procedure);
    }
    static ID3D11Device& GetGraphicsDevice3D()
    {
        return GetGraphicsInstance().GetDevice3D();
    }
    static ID3D11DeviceContext& GetGraphicsContext3D()
    {
        return GetGraphicsInstance().GetContext3D();
    }
    static ID2D1Device& GetGraphicsDevice2D()
    {
        return GetGraphicsInstance().GetDevice2D();
    }
    static ID2D1DeviceContext& GetGraphicsContext2D()
    {
        return GetGraphicsInstance().GetContext2D();
    }
    static IDXGISwapChain& GetGraphicsSwapChain()
    {
        return GetGraphicsInstance().GetSwapChain();
    }
    static IWICImagingFactory& GetTextureFactory()
    {
        return GetGraphicsInstance().GetTextureFactory();
    }
    static IDWriteFactory& GetTextFactory()
    {
        return GetGraphicsInstance().GetTextFactory();
    }
    static IDirectSound8& GetAudioDevice()
    {
        return GetAudioInstance().GetDevice();
    }
    static bool GetKey(int VK_CODE)
    {
        return GetInputInstance().GetKey(VK_CODE);
    }
    static bool GetKeyUp(int VK_CODE)
    {
        return GetInputInstance().GetKeyUp(VK_CODE);
    }
    static bool GetKeyDown(int VK_CODE)
    {
        return GetInputInstance().GetKeyDown(VK_CODE);
    }
    static Float2 GetMousePosition()
    {
        return GetInputInstance().GetMousePosition();
    }
    static void SetMousePosition(float x, float y)
    {
        GetInputInstance().SetMousePosition(x, y);
    }
    static void SetShowCursor(bool isShowCursor)
    {
        GetInputInstance().SetShowCursor(isShowCursor);
    }
    static float GetTime()
    {
        return GetTimerInstance().GetTime();
    }
    static float GetDeltaTime()
    {
        return GetTimerInstance().GetDeltaTime();
    }
    static int GetFrameRate()
    {
        return GetTimerInstance().GetFrameRate();
    }
    static void SetRandomSeed(int seed)
    {
        return GetRandomInstance().SetSeed(seed);
    }
    static float GetRandom()
    {
        return GetRandomInstance().Get();
    }
    static void AddFont(const wchar_t* filePath)
    {
        AddFontResourceExW(filePath, FR_PRIVATE, nullptr);
    }

private:
    static Window& GetWindowInstance()
    {
        static std::unique_ptr<Window> window(new Window());
        return *window.get();
    }
    static Graphics& GetGraphicsInstance()
    {
        static std::unique_ptr<Graphics> graphics(new Graphics());
        return *graphics.get();
    }
    static Audio& GetAudioInstance()
    {
        static std::unique_ptr<Audio> audio(new Audio());
        return *audio.get();
    }
    static Input& GetInputInstance()
    {
        static std::unique_ptr<Input> input(new Input());
        return *input.get();
    }
    static Timer& GetTimerInstance()
    {
        static std::unique_ptr<Timer> timer(new Timer());
        return *timer.get();
    }
    static Random& GetRandomInstance()
    {
        static std::unique_ptr<Random> random(new Random());
        return *random.get();
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
