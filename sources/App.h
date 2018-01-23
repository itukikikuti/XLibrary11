// © 2017 Naoki Nakagawa
#ifndef _GAME_LIBRARY_
#define _GAME_LIBRARY_

#define OEMRESOURCE
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <fstream>
#include <iostream>
#include <memory>
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
public:
#include "Window.h"
#include "Screen.h"
#include "Input.h"
#include "Time.h"
	PUBLIC App() = delete;
	PUBLIC static HWND GetWindowHandle() {
		return GetWindowInstance().GetHandle();
	}
	PUBLIC static DirectX::XMINT2 GetWindowSize() {
		return GetWindowInstance().GetSize();
	}
	PUBLIC static void SetWindowSize(int width, int height) {
		GetWindowInstance().SetSize(width, height);
	}
	PUBLIC static wchar_t* GetTitle() {
		return GetWindowInstance().GetTitle();
	}
	PUBLIC static void SetTitle(const wchar_t* title) {
		GetWindowInstance().SetTitle(title);
	}
	PUBLIC static void SetFullScreen(bool isFullscreen) {
		GetWindowInstance().SetFullScreen(isFullscreen);
	}
	PUBLIC static ID3D11Device& GetDevice() {
		return GetScreenInstance().GetDevice();
	}
	PUBLIC static IDXGISwapChain& GetSwapChain() {
		return GetScreenInstance().GetSwapChain();
	}
	PUBLIC static ID3D11DeviceContext& GetContext() {
		return GetScreenInstance().GetContext();
	}
	PUBLIC static ID3D11RenderTargetView& GetRenderTargetView(bool isResize = false) {
		return GetScreenInstance().GetRenderTargetView();
	}
	PUBLIC static bool GetKey(int VK_CODE) {
		return GetInputInstance().GetKey(VK_CODE);
	}
	PUBLIC static bool GetKeyUp(int VK_CODE) {
		return GetInputInstance().GetKeyUp(VK_CODE);
	}
	PUBLIC static bool GetKeyDown(int VK_CODE) {
		return GetInputInstance().GetKeyDown(VK_CODE);
	}
	PUBLIC static DirectX::XMINT2 GetMousePosition() {
		return GetInputInstance().GetMousePosition();
	}
	PUBLIC static float GetTime() {
		return GetTimeInstance().GetTime();
	}
	PUBLIC static float GetDeltaTime() {
		return GetTimeInstance().GetDeltaTime();
	}
	PUBLIC static int GetFrameRate() {
		return GetTimeInstance().GetFrameRate();
	}
	PUBLIC static DirectX::XMMATRIX GetViewMatrix() {
		return DirectX::XMMatrixLookAtLH(DirectX::XMVectorSet(App::GetWindowSize().x / 2.0f, -App::GetWindowSize().y / 2.0f, 0.0f, 0.0f), DirectX::XMVectorSet(App::GetWindowSize().x / 2.0f, -App::GetWindowSize().y / 2.0f, 1.0f, 0.0f), DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
	}
	PUBLIC static DirectX::XMMATRIX GetProjectionMatrix() {
		return DirectX::XMMatrixOrthographicLH(App::GetWindowSize().x * 1.0f, App::GetWindowSize().y * 1.0f, -1.0f, 1.0f);
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

		GetInputInstance().Update();
		GetTimeInstance().Update();

		GetContext().ClearRenderTargetView(&GetRenderTargetView(), color);

		return true;
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
	PRIVATE static Window& GetWindowInstance() {
		static std::unique_ptr<Window> window(new Window());
		return *window.get();
	}
	PRIVATE static Screen& GetScreenInstance() {
		static std::unique_ptr<Screen> screen(new Screen());
		return *screen.get();
	}
	PRIVATE static Input& GetInputInstance() {
		static std::unique_ptr<Input> input(new Input());
		return *input.get();
	}
	PRIVATE static Time& GetTimeInstance() {
		static std::unique_ptr<Time> time(new Time());
		return *time.get();
	}
};

#include "Mesh.h"
#include "Sprite.h"
#include "Text.h"

GAME_LIBRARY_END

#endif
