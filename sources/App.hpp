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

inline void XLibraryInitialize()
{
    static bool isInitialized = false;

    if (!isInitialized)
    {
        CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
        isInitialized = true;
    }
}

#include "Utility.hpp"
#include "Window.hpp"
#include "Input.hpp"
#include "Graphics.hpp"

class App final
{
public:
#include "Audio.hpp"
#include "Timer.hpp"
#include "Random.hpp"

    App() = delete;
    static bool Refresh()
    {
        Graphics::Update();
        Input::Update();
        GetTimerInstance().Update();
        return Window::Update();
    }
    static IDirectSound8& GetAudioDevice()
    {
        return GetAudioInstance().GetDevice();
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
    static Audio& GetAudioInstance()
    {
        static std::unique_ptr<Audio> audio(new Audio());
        return *audio.get();
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
