#if !defined(GRAPHICS_H)
#define GRAPHICS_H

#include <d3d11.h>
#include <DirectXMath.h>
#include <vector>

class Graphics {
public:

	const DWORD WINDOW_STYLE = WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX;
	const char TITLE[10] = "GDK";
	static const int CLIENT_WIDTH = 1280, CLIENT_HEIGHT = 720;
	const int SWAP_CHAIN_COUNT = 2;
	const DXGI_FORMAT SWAP_CHAIN_FORMAT = DXGI_FORMAT_R8G8B8A8_UNORM;
	const int MULTI_SAMPLE_COUNT = 1;
	const int MULTI_SAMPLE_QUALITY = 0;
	const DXGI_FORMAT DEPTH_STENCIL_FORMAT = DXGI_FORMAT_D24_UNORM_S8_UINT;

	static Graphics& GetInstance();

	bool Render();
	float GetDeltaTime();
	ID3D11Device& GetDevice();
	ID3D11DeviceContext& GetDeviceContext();

private:
	HWND window;
	MSG windowMessage;
	float previosTime;
	float deltaTime;
	float clearColor[4];
	D3D_DRIVER_TYPE driverType;
	ID3D11Device *device;
	ID3D11DeviceContext *deviceContext;
	IDXGISwapChain *swapChain;
	D3D_FEATURE_LEVEL featureLevel;
	ID3D11RenderTargetView *renderTargetView;
	ID3D11Texture2D *renderTargetTexture;
	ID3D11ShaderResourceView *renderTargetShaderResourceView;
	ID3D11VertexShader *vertexShader;
	ID3D11PixelShader *pixelShader;
	ID3D11InputLayout *inputLayout;

	Graphics();
	~Graphics();
	Graphics(const Graphics&);
	Graphics& operator=(const Graphics&);
	bool ProcessWindowMessage();
	static LRESULT WINAPI ProcessWindow(HWND windowHandle, UINT windowMessage, WPARAM wParam, LPARAM lParam);
	bool CreateRenderTarget();
	void ReleaseRenderTarget();
	bool CompileShader(WCHAR* filePath, char* entryPoint, char* shaderModel, ID3DBlob** out);
};

#endif
