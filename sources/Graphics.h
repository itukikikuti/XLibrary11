#if !defined(GRAPHICS_H)
#define GRAPHICS_H

#include <memory>
#include <d3d11.h>
#include <DirectXMath.h>

class Graphics {
public:
	Graphics() = delete;
	static HWND GetWindow();
	static int GetWidth();
	static int GetHeight();
	static void SetSize(int width, int height);
	static ID3D11Device& GetDevice();
	static ID3D11DeviceContext& GetDeviceContext();
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

	static HWND window;
	static std::unique_ptr<ID3D11Device, ComReleaser> device;
	static std::unique_ptr<ID3D11DeviceContext, ComReleaser> deviceContext;
	static std::unique_ptr<IDXGISwapChain, ComReleaser> swapChain;
	static std::unique_ptr<ID3D11RenderTargetView, ComReleaser> renderTargetView;
	static std::unique_ptr<ID3D11Texture2D, ComReleaser> renderTargetTexture;
	static std::unique_ptr<ID3D11ShaderResourceView, ComReleaser> renderTargetShaderResourceView;
	static std::unique_ptr<ID3D11VertexShader, ComReleaser> vertexShader;
	static std::unique_ptr<ID3D11PixelShader, ComReleaser> pixelShader;
	static std::unique_ptr<ID3D11InputLayout, ComReleaser> inputLayout;
	static float color[4];
	static float previosTime;
	static float deltaTime;
	static MSG response;

	static bool ProcessResponse();
	static LRESULT WINAPI ProcessWindow(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
	static bool CompileShader(WCHAR* filePath, char* entryPoint, char* shaderModel, ID3DBlob** out);
};

#endif
