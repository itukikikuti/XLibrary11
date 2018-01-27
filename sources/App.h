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
#include "Graphic.h"
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
		return GetGraphicInstance().GetDevice();
	}
	PUBLIC static IDXGISwapChain& GetSwapChain() {
		return GetGraphicInstance().GetSwapChain();
	}
	PUBLIC static ID3D11DeviceContext& GetContext() {
		return GetGraphicInstance().GetContext();
	}
	PUBLIC static ID3D11RenderTargetView& GetRenderTargetView(bool isResize = false) {
		return GetGraphicInstance().GetRenderTargetView();
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
	PUBLIC static DirectX::XMFLOAT2 GetMousePosition() {
		return GetInputInstance().GetMousePosition();
	}
	PUBLIC static void SetMousePosition(DirectX::XMFLOAT2 position) {
		GetInputInstance().SetMousePosition(position.x, position.y);
	}
	PUBLIC static void SetMousePosition(float x, float y) {
		GetInputInstance().SetMousePosition(x, y);
	}
	PUBLIC static void SetShowCursor(bool isShowCursor) {
		GetInputInstance().SetShowCursor(isShowCursor);
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
	PRIVATE static Window& GetWindowInstance() {
		static std::unique_ptr<Window> window(new Window(ProcessWindow));
		return *window.get();
	}
	PRIVATE static Graphic& GetGraphicInstance() {
		static std::unique_ptr<Graphic> graphic(new Graphic());
		return *graphic.get();
	}
	PRIVATE static Input& GetInputInstance() {
		static std::unique_ptr<Input> input(new Input());
		return *input.get();
	}
	PRIVATE static Time& GetTimeInstance() {
		static std::unique_ptr<Time> time(new Time());
		return *time.get();
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
	PRIVATE static LRESULT WINAPI ProcessWindow(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
		switch (message) {
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProcW(window, message, wParam, lParam);
		}
		return 0;
	}
};

#include "Camera.h"
#include "Mesh.h"
#include "Sprite.h"
#include "Text.h"

GAME_LIBRARY_END

#endif
