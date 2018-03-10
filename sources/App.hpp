// © 2017 itukikikuti
#pragma once

#define OEMRESOURCE
#include <forward_list>
#include <fstream>
#include <functional>
#include <memory>
#include <vector>
#include <windows.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <xaudio2.h>
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <Shlwapi.h>
#include <wincodec.h>
#include <strsafe.h>
#include <crtdbg.h>
#include <atlbase.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "xaudio2.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "mfuuid.lib")
#pragma comment(lib, "Shlwapi.lib")

XLIBRARY_NAMESPACE_BEGIN

#define Main() APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
#define PUBLIC public:
#define PRIVATE private:
#define PROTECTED protected:

#include "Utility.hpp"

class App final
{
	PUBLIC static constexpr wchar_t* NAME = L"XLibrary11";

#include "Window.hpp"
#include "Graphics.hpp"
#include "Audio.hpp"
#include "Input.hpp"
#include "Timer.hpp"

	PUBLIC App() = delete;
	PUBLIC static bool Refresh()
	{
		GetGraphics().Update();
		GetInput().Update();
		GetTimer().Update();
		return GetWindow().Update();
	}
	PUBLIC static void Initialize()
	{
		static bool isInitialized = false;

		if (!isInitialized)
		{
			CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
			isInitialized = true;
		}
	}
	PUBLIC static HWND GetWindowHandle()
	{
		return GetWindow().GetHandle();
	}
	PUBLIC static DirectX::XMINT2 GetWindowSize()
	{
		return GetWindow().GetSize();
	}
	PUBLIC static void SetWindowSize(int width, int height)
	{
		GetWindow().SetSize(width, height);
	}
	PUBLIC static wchar_t* const GetTitle()
	{
		return GetWindow().GetTitle();
	}
	PUBLIC static void SetTitle(const wchar_t* const title)
	{
		GetWindow().SetTitle(title);
	}
	PUBLIC static void SetFullScreen(bool isFullScreen)
	{
		GetWindow().SetFullScreen(isFullScreen);
	}
	PUBLIC static void AddProcedure(Window::Proceedable* const procedure)
	{
		GetWindow().AddProcedure(procedure);
	}
	PUBLIC static void RemoveProcedure(Window::Proceedable* const procedure)
	{
		GetWindow().RemoveProcedure(procedure);
	}
	PUBLIC static ID3D11Device& GetGraphicsDevice()
	{
		return GetGraphics().GetDevice();
	}
	PUBLIC static ID3D11DeviceContext& GetGraphicsContext()
	{
		return GetGraphics().GetContext();
	}
	PUBLIC static IDXGISwapChain& GetGraphicsMemory()
	{
		return GetGraphics().GetMemory();
	}
	PUBLIC static IXAudio2& GetAudioEngine()
	{
		return GetAudio().GetEngine();
	}
	PUBLIC static bool GetKey(int VK_CODE)
	{
		return GetInput().GetKey(VK_CODE);
	}
	PUBLIC static bool GetKeyUp(int VK_CODE)
	{
		return GetInput().GetKeyUp(VK_CODE);
	}
	PUBLIC static bool GetKeyDown(int VK_CODE)
	{
		return GetInput().GetKeyDown(VK_CODE);
	}
	PUBLIC static Float2 GetMousePosition()
	{
		return GetInput().GetMousePosition();
	}
	PUBLIC static void SetMousePosition(float x, float y)
	{
		GetInput().SetMousePosition(x, y);
	}
	PUBLIC static void SetShowCursor(bool isShowCursor)
	{
		GetInput().SetShowCursor(isShowCursor);
	}
	PUBLIC static float GetTime()
	{
		return GetTimer().GetTime();
	}
	PUBLIC static float GetDeltaTime()
	{
		return GetTimer().GetDeltaTime();
	}
	PUBLIC static int GetFrameRate()
	{
		return GetTimer().GetFrameRate();
	}
	PUBLIC static void AddFont(const wchar_t* filePath)
	{
		AddFontResourceExW(filePath, FR_PRIVATE, nullptr);
	}
	PRIVATE static Window& GetWindow()
	{
		static std::unique_ptr<Window> window(new Window());
		return *window.get();
	}
	PRIVATE static Graphics& GetGraphics()
	{
		static std::unique_ptr<Graphics> graphics(new Graphics());
		return *graphics.get();
	}
	PRIVATE static Audio& GetAudio()
	{
		static std::unique_ptr<Audio> audio(new Audio());
		return *audio.get();
	}
	PRIVATE static Input& GetInput()
	{
		static std::unique_ptr<Input> input(new Input());
		return *input.get();
	}
	PRIVATE static Timer& GetTimer()
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
#include "Voice.hpp"
XLIBRARY_NAMESPACE_END
