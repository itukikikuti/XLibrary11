#if !defined(GRAPHICS_H)
#define GRAPHICS_H
#include <list>
#include <windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "Sprite.h"
#include "Text.h"
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace GameLibrary {
	class Game {
	public:
		Game() = delete;
		static HWND GetWindow();
		static DirectX::XMINT2 GetSize();
		static void SetSize(int width, int height);
		static char* GetTitle();
		static void SetTitle(char* title);
		static ID3D11Device& GetDevice();
		static IDXGISwapChain& GetSwapChain();
		static ID3D11DeviceContext& GetDeviceContext();
		static ID3D11RenderTargetView& GetRenderTargetView();
		static DirectX::XMINT2 GetMousePosition();
		static float GetDeltaTime();
		static void AddFont(char* path);
		static bool Update();

	private:
		static DirectX::XMINT2 size;
		static DirectX::XMINT2 mousePosition;
		static float deltaTime;
		static std::list<char*> fontPathList;

		static void Finalize();
		static void CompileShader(WCHAR* filePath, char* entryPoint, char* shaderModel, ID3DBlob** out);
		static void ProcessSize();
		static void ProcessMousePosition();
		static void PrecessDeltaTime();
		static bool ProcessResponse();
		static LRESULT WINAPI ProcessWindow(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
	};
}

#endif
