// © 2017 itukikikuti
#pragma once

#define OEMRESOURCE
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <strsafe.h>
#include <utility>
#include <vector>
#include <wincodec.h>
#include <windows.h>
#include <wrl.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#define Main() WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
#define PUBLIC public:
#define PRIVATE private:
#define PROTECTED protected:

namespace GameLibrary {

#include "Math.hpp"

	class App {

	#include "Window.hpp"
	#include "Graphics.hpp"
	#include "Input.hpp"
	#include "Timer.hpp"

		PUBLIC App() = delete;
		PUBLIC static HWND GetWindowHandle() {
			return GetWindow().GetHandle();
		}
		PUBLIC static std::vector<UINT>& GetWindowMessages() {
			return GetWindow().GetMessages();
		}
		PUBLIC static DirectX::XMFLOAT2 GetWindowSize() {
			return GetWindow().GetSize();
		}
		PUBLIC static void SetWindowSize(float width, float height) {
			GetWindow().SetSize(width, height);
		}
		PUBLIC static wchar_t* GetTitle() {
			return GetWindow().GetTitle();
		}
		PUBLIC static void SetTitle(const wchar_t* title) {
			GetWindow().SetTitle(title);
		}
		PUBLIC static void SetFullScreen(bool isFullscreen) {
			GetWindow().SetFullScreen(isFullscreen);
		}
		PUBLIC static ID3D11Device& GetGraphicsDevice() {
			return GetGraphics().GetDevice();
		}
		PUBLIC static ID3D11DeviceContext& GetGraphicsContext() {
			return GetGraphics().GetContext();
		}
		PUBLIC static IDXGISwapChain& GetGraphicsMemory() {
			return GetGraphics().GetMemory();
		}
		PUBLIC static bool GetKey(int VK_CODE) {
			return GetInput().GetKey(VK_CODE);
		}
		PUBLIC static bool GetKeyUp(int VK_CODE) {
			return GetInput().GetKeyUp(VK_CODE);
		}
		PUBLIC static bool GetKeyDown(int VK_CODE) {
			return GetInput().GetKeyDown(VK_CODE);
		}
		PUBLIC static DirectX::XMFLOAT2 GetMousePosition() {
			return GetInput().GetMousePosition();
		}
		PUBLIC static void SetMousePosition(DirectX::XMFLOAT2 position) {
			GetInput().SetMousePosition(position.x, position.y);
		}
		PUBLIC static void SetMousePosition(float x, float y) {
			GetInput().SetMousePosition(x, y);
		}
		PUBLIC static void SetShowCursor(bool isShowCursor) {
			GetInput().SetShowCursor(isShowCursor);
		}
		PUBLIC static float GetTime() {
			return GetTimer().GetTime();
		}
		PUBLIC static float GetDeltaTime() {
			return GetTimer().GetDeltaTime();
		}
		PUBLIC static int GetFrameRate() {
			return GetTimer().GetFrameRate();
		}
		PUBLIC static void AddFont(const wchar_t* filePath) {
			AddFontResourceExW(filePath, FR_PRIVATE, nullptr);
		}
		PUBLIC static bool Refresh() {
			GetGraphicsMemory().Present(1, 0);

			if (!GetWindow().Update()) return false;
			GetInput().Update();
			GetTimer().Update();

			return true;
		}
		PRIVATE static Window& GetWindow() {
			static std::unique_ptr<Window> window(new Window());
			return *window.get();
		}
		PRIVATE static Graphics& GetGraphics() {
			static std::unique_ptr<Graphics> graphics(new Graphics());
			return *graphics.get();
		}
		PRIVATE static Input& GetInput() {
			static std::unique_ptr<Input> input(new Input());
			return *input.get();
		}
		PRIVATE static Timer& GetTimer() {
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
}
