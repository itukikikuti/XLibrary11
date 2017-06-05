#if !defined(GRAPHICS_H)
#define GRAPHICS_H

#include <d3d11.h>
#include <DirectXMath.h>

struct Vertex {
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT2 uv;
};

struct ConstantBuffer {
	DirectX::XMMATRIX world;
	DirectX::XMMATRIX view;
	DirectX::XMMATRIX projection;
	DirectX::XMFLOAT3 lightDirection;
};

class Graphics {
public:
	const DWORD WINDOW_STYLE = WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX;
	const char TITLE[10] = "GDK";
	const int CLIENT_WIDTH = 1280, CLIENT_HEIGHT = 720;
	const int SWAP_CHAIN_COUNT = 2;
	const DXGI_FORMAT SWAP_CHAIN_FORMAT = DXGI_FORMAT_R8G8B8A8_UNORM;
	const int MULTI_SAMPLE_COUNT = 1;
	const int MULTI_SAMPLE_QUALITY = 0;
	const DXGI_FORMAT DEPTH_STENCIL_FORMAT = DXGI_FORMAT_D24_UNORM_S8_UINT;

	Graphics();
	~Graphics();
	void Render();
private:
	int frame;
	HWND window;
	float clearColor[4];
	D3D_DRIVER_TYPE driverType;
	ID3D11Device *device;
	ID3D11DeviceContext *deviceContext;
	IDXGISwapChain *swapChain;
	D3D_FEATURE_LEVEL featureLevel;
	ID3D11RenderTargetView *renderTargetView;
	ID3D11DepthStencilView *depthStencilView;
	ID3D11Texture2D *renderTargetTexture;
	ID3D11Texture2D *depthStencilTexture;
	ID3D11ShaderResourceView *renderTargetShaderResourceView;
	ID3D11ShaderResourceView *depthStencilShaderResourceView;
	ID3D11VertexShader *vertexShader;
	ID3D11GeometryShader *geometryShader;
	ID3D11PixelShader *pixelShader;
	ID3D11InputLayout *inputLayout;
	ID3D11Buffer *vertexBuffer;
	ID3D11Buffer *indexBuffer;
	ID3D11Buffer *constantBuffer;
	ID3D11Texture2D *texture;
	ID3D11ShaderResourceView *shaderResourceView;
	ID3D11SamplerState *samplerState;
	ConstantBuffer cbuffer;
	int vertexCount;
	int indexCount;

	static LRESULT __stdcall WindowProcedure(HWND windowHandle, UINT windowMessage, WPARAM wParam, LPARAM lParam);
	bool CreateRenderTarget();
	void ReleaseRenderTarget();
	bool CreateDepthStencil();
	void ReleaseDepthStencil();
	bool CompileShader(WCHAR* filePath, char* entryPoint, char* shaderModel, ID3DBlob** out);
};

#endif
