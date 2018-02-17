// © 2017 itukikikuti
#pragma once

#define OEMRESOURCE
#include <windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wincodec.h>
#include <xaudio2.h>
#include <mfapi.h>
#include <DirectXMath.h>
#include <wrl.h>
#include <memory>
#include <vector>
#include <forward_list>
#include <fstream>
#include <functional>
#include <strsafe.h>
#include <Shlwapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "mfuuid.lib")
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "xaudio2.lib")

XLIBRARY_NAMESPACE_BEGIN

#define Main() WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
#define PUBLIC public:
#define PRIVATE private:
#define PROTECTED protected:

#include "Math.hpp"
#include "Interface.hpp"

class Window;
class Graphics;
class Audio;
class Input;
class Timer;

class App {
	PUBLIC static constexpr wchar_t* name = L"XLibrary11";
	PUBLIC App() = delete;
	PUBLIC static HWND GetWindowHandle();
	PUBLIC static Float2 GetWindowSize();
	PUBLIC static void SetWindowSize(float width, float height);
	PUBLIC static wchar_t* GetTitle();
	PUBLIC static void SetTitle(const wchar_t* title);
	PUBLIC static void SetFullScreen(bool isFullscreen);
	PUBLIC static void AddProcedure(Proceedable* const procedure);
	PUBLIC static void RemoveProcedure(Proceedable* const procedure);
	PUBLIC static ID3D11Device& GetGraphicsDevice();
	PUBLIC static ID3D11DeviceContext& GetGraphicsContext();
	PUBLIC static IDXGISwapChain& GetGraphicsMemory();
	PUBLIC static IXAudio2& GetAudioEngine();
	PUBLIC static bool GetKey(int VK_CODE);
	PUBLIC static bool GetKeyUp(int VK_CODE);
	PUBLIC static bool GetKeyDown(int VK_CODE);
	PUBLIC static Float2 GetMousePosition();
	PUBLIC static void SetMousePosition(Float2 position);
	PUBLIC static void SetMousePosition(float x, float y);
	PUBLIC static void SetShowCursor(bool isShowCursor);
	PUBLIC static float GetTime();
	PUBLIC static float GetDeltaTime();
	PUBLIC static int GetFrameRate();
	PUBLIC static void AddFont(const wchar_t* filePath);
	PUBLIC static bool Refresh();
	PRIVATE static Window& GetWindow();
	PRIVATE static Graphics& GetGraphics();
	PRIVATE static Audio& GetAudio();
	PRIVATE static Input& GetInput();
	PRIVATE static Timer& GetTimer();
};

#include "Texture.hpp"
#include "Material.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"
#include "Sprite.hpp"
#include "Text.hpp"
#include "Voice.hpp"

#include "Window.hpp"
#include "Graphics.hpp"
#include "Audio.hpp"
#include "Input.hpp"
#include "Timer.hpp"

HWND App::GetWindowHandle() {
	return GetWindow().GetHandle();
}
Float2 App::GetWindowSize() {
	return GetWindow().GetSize();
}
void App::SetWindowSize(float width, float height) {
	GetWindow().SetSize(width, height);
}
wchar_t* App::GetTitle() {
	return GetWindow().GetTitle();
}
void App::SetTitle(const wchar_t* title) {
	GetWindow().SetTitle(title);
}
void App::SetFullScreen(bool isFullscreen) {
	GetWindow().SetFullScreen(isFullscreen);
}
void App::AddProcedure(Proceedable* const procedure) {
	GetWindow().AddProcedure(procedure);
}
void App::RemoveProcedure(Proceedable* const procedure) {
	GetWindow().RemoveProcedure(procedure);
}
ID3D11Device& App::GetGraphicsDevice() {
	return GetGraphics().GetDevice();
}
ID3D11DeviceContext& App::GetGraphicsContext() {
	return GetGraphics().GetContext();
}
IDXGISwapChain& App::GetGraphicsMemory() {
	return GetGraphics().GetMemory();
}
IXAudio2& App::GetAudioEngine() {
	return GetAudio().GetAudioEngine();
}
bool App::GetKey(int VK_CODE) {
	return GetInput().GetKey(VK_CODE);
}
bool App::GetKeyUp(int VK_CODE) {
	return GetInput().GetKeyUp(VK_CODE);
}
bool App::GetKeyDown(int VK_CODE) {
	return GetInput().GetKeyDown(VK_CODE);
}
Float2 App::GetMousePosition() {
	return GetInput().GetMousePosition();
}
void App::SetMousePosition(Float2 position) {
	GetInput().SetMousePosition(position.x, position.y);
}
void App::SetMousePosition(float x, float y) {
	GetInput().SetMousePosition(x, y);
}
void App::SetShowCursor(bool isShowCursor) {
	GetInput().SetShowCursor(isShowCursor);
}
float App::GetTime() {
	return GetTimer().GetTime();
}
float App::GetDeltaTime() {
	return GetTimer().GetDeltaTime();
}
int App::GetFrameRate() {
	return GetTimer().GetFrameRate();
}
void App::AddFont(const wchar_t* filePath) {
	AddFontResourceExW(filePath, FR_PRIVATE, nullptr);
}
bool App::Refresh() {
	GetGraphicsMemory().Present(1, 0);

	if (!GetWindow().Update()) return false;
	GetInput().Update();
	GetTimer().Update();

	return true;
}
Window& App::GetWindow() {
	static std::unique_ptr<Window> window(new Window());
	return *window.get();
}
Graphics& App::GetGraphics() {
	static std::unique_ptr<Graphics> graphics(new Graphics());
	return *graphics.get();
}
Audio& App::GetAudio() {
	static std::unique_ptr<Audio> audio(new Audio());
	return *audio.get();
}
Input& App::GetInput() {
	static std::unique_ptr<Input> input(new Input());
	return *input.get();
}
Timer& App::GetTimer() {
	static std::unique_ptr<Timer> timer(new Timer());
	return *timer.get();
}

XLIBRARY_NAMESPACE_END
