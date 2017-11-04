#if !defined(GRAPHICS_H)
#define GRAPHICS_H

#include <memory>
#include <windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace GameLibrary {
	class Game {
	public:
		Game() = delete;
		static HWND GetWindow();
		static int GetWidth();
		static int GetHeight();
		static void SetSize(int width, int height);
		static ID3D11Device& GetDevice();
		static IDXGISwapChain& GetSwapChain();
		static ID3D11DeviceContext& GetDeviceContext();
		static ID3D11RenderTargetView& GetRenderTargetView();
		static float GetDeltaTime();
		static bool Update();

	private:
		class ComReleaser {
		public:
			void operator()(IUnknown* com) {
				com->Release();
			}
		};

		static const int SWAP_CHAIN_COUNT = 2;
		static const DXGI_FORMAT SWAP_CHAIN_FORMAT = DXGI_FORMAT_R8G8B8A8_UNORM;
		static const int MULTI_SAMPLE_COUNT = 1;
		static const int MULTI_SAMPLE_QUALITY = 0;

		static float color[4];
		static float previosTime;
		static float deltaTime;

		static void CompileShader(WCHAR* filePath, char* entryPoint, char* shaderModel, ID3DBlob** out);
		static bool ProcessResponse();
		static LRESULT WINAPI ProcessWindow(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
	};
}

#endif
