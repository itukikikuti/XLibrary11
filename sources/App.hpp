// © 2017 itukikikuti
// https://github.com/itukikikuti/XLibrary11
// GNU General Public License v3.0
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

XLIBRARY_NAMESPACE_BEGIN

#define MAIN() APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)

#include "Utility.hpp"

class App final
{
public:

#include "Window.hpp"
#include "Graphics.hpp"
#include "Audio.hpp"
#include "Input.hpp"
#include "Timer.hpp"

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

#include "Texture.hpp"
#include "Material.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"
#include "Sprite.hpp"
#include "Text.hpp"
#include "Voice.hpp"

XLIBRARY_NAMESPACE_END
