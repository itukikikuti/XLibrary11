// © 2017 Naoki Nakagawa
#ifndef _GAME_LIBRARY_
#define _GAME_LIBRARY_

#define OEMRESOURCE
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <strsafe.h>
#include <vector>
#include <wincodec.h>
#include <windows.h>
#include <wrl.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#define GAME_LIBRARY_BEGIN namespace GameLibrary {
#define GAME_LIBRARY_END }
#define Main() WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
#define PUBLIC public:
#define PRIVATE private:
#define PROTECTED protected:

GAME_LIBRARY_BEGIN

class App {
	#include "Window.h"
	#include "Screen.h"

	PUBLIC App() = delete;
	PUBLIC static HWND GetWindowHandle() {
		return GetWindow()->GetHandle();
	}
	PUBLIC static DirectX::XMINT2 GetWindowSize() {
		return GetWindow()->GetSize();
	}
	PUBLIC static void SetWindowSize(int width, int height) {
		GetWindow()->SetSize(width, height);
	}
	PUBLIC static wchar_t* GetTitle() {
		return GetWindow()->GetTitle();
	}
	PUBLIC static void SetTitle(const wchar_t* title) {
		GetWindow()->SetTitle(title);
	}
	PUBLIC static void SetFullScreen(bool isFullscreen) {
		GetWindow()->SetFullScreen(isFullscreen);
	}
	PUBLIC static ID3D11Device& GetDevice() {
		return GetScreen()->GetDevice();
	}
	PUBLIC static IDXGISwapChain& GetSwapChain() {
		return GetScreen()->GetSwapChain();
	}
	PUBLIC static ID3D11DeviceContext& GetContext() {
		return GetScreen()->GetContext();
	}
	PUBLIC static ID3D11RenderTargetView& GetRenderTargetView(bool isResize = false) {
		return GetScreen()->GetRenderTargetView();
	}
	PUBLIC static DirectX::XMMATRIX GetViewMatrix() {
		return DirectX::XMMatrixLookAtLH(DirectX::XMVectorSet(App::GetWindowSize().x / 2.0f, -App::GetWindowSize().y / 2.0f, 0.0f, 0.0f), DirectX::XMVectorSet(App::GetWindowSize().x / 2.0f, -App::GetWindowSize().y / 2.0f, 1.0f, 0.0f), DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
	}
	PUBLIC static DirectX::XMMATRIX GetProjectionMatrix() {
		return DirectX::XMMatrixOrthographicLH(App::GetWindowSize().x * 1.0f, App::GetWindowSize().y * 1.0f, -1.0f, 1.0f);
	}
	PUBLIC static DirectX::XMINT2 GetMousePosition() {
		return MousePosition();
	}
	PUBLIC static bool GetKey(int VK_CODE) {
		return KeyState()[VK_CODE] & 0x80;
	}
	PUBLIC static bool GetKeyUp(int VK_CODE) {
		return !(KeyState()[VK_CODE] & 0x80) && (PreKeyState()[VK_CODE] & 0x80);
	}
	PUBLIC static bool GetKeyDown(int VK_CODE) {
		return (KeyState()[VK_CODE] & 0x80) && !(PreKeyState()[VK_CODE] & 0x80);
	}
	PUBLIC static float GetTime() {
		return Time();
	}
	PUBLIC static float GetDeltaTime() {
		return DeltaTime();
	}
	PUBLIC static int GetFrameRate() {
		return FrameRate();
	}
	PUBLIC static void AddFont(const wchar_t* filePath) {
		AddFontResourceExW(filePath, FR_PRIVATE, nullptr);
	}
	PUBLIC static bool Refresh() {
		static float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

		GetSwapChain().Present(0, 0);

		if (!ProcessMessage()) {
			return false;
		}

		ProcessMousePosition();
		ProcessKey();
		PrecessDeltaTime();
		PrecessTime();
		ProcessFrameRate();

		GetContext().ClearRenderTargetView(&GetRenderTargetView(), color);

		return true;
	}
	PRIVATE static DirectX::XMINT2& MousePosition() {
		static DirectX::XMINT2 mousePosition;
		return mousePosition;
	}
	PRIVATE static BYTE* PreKeyState() {
		static BYTE preKeyState[256];
		return preKeyState;
	}
	PRIVATE static BYTE* KeyState() {
		static BYTE keyState[256];
		return keyState;
	}
	PRIVATE static float& Time() {
		static float time = 0.0f;
		return time;
	}
	PRIVATE static float& DeltaTime() {
		static float deltaTime = 0.0f;
		return deltaTime;
	}
	PRIVATE static int& FrameRate() {
		static int frameRate = 0;
		return frameRate;
	}
	PRIVATE static void ProcessMousePosition() {
		POINT point = {};
		GetCursorPos(&point);

		ScreenToClient(GetWindowHandle(), &point);
		MousePosition() = DirectX::XMINT2(point.x, point.y);
	}
	PRIVATE static void ProcessKey() {
		for (int i = 0; i < 256; i++) {
			PreKeyState()[i] = KeyState()[i];
		}

		GetKeyboardState(KeyState());
	}
	PRIVATE static LARGE_INTEGER GetCounter() {
		LARGE_INTEGER counter;
		QueryPerformanceCounter(&counter);
		return counter;
	}
	PRIVATE static LARGE_INTEGER GetCountFrequency() {
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		return frequency;
	}
	PRIVATE static void PrecessTime() {
		Time() += GetDeltaTime();
	}
	PRIVATE static void PrecessDeltaTime() {
		static LARGE_INTEGER preTime = GetCounter();
		static LARGE_INTEGER frequency = GetCountFrequency();

		LARGE_INTEGER time = GetCounter();
		DeltaTime() = (float)(time.QuadPart - preTime.QuadPart) / frequency.QuadPart;
		preTime = GetCounter();
	}
	PRIVATE static void ProcessFrameRate() {
		static float time = 0.0f;
		static int c = 0;

		c++;
		time += GetDeltaTime();
		if (time >= 1.0f) {
			FrameRate() = c;
			c = 0;
			time -= 1.0f;
		}
	}
	PRIVATE static bool ProcessMessage() {
		static MSG message = {};

		while (message.message != WM_QUIT) {
			if (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE)) {
				TranslateMessage(&message);
				DispatchMessageW(&message);
			}
			else {
				return true;
			}
		}

		return false;
	}
	PRIVATE static Window* GetWindow() {
		static Window* window = new Window();
		return window;
	}
	PRIVATE static Screen* GetScreen() {
		static Screen* screen = new Screen();
		return screen;
	}
};

#include "Mesh.h"
#include "Sprite.h"
#include "Text.h"

GAME_LIBRARY_END

#endif
