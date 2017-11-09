// (c) 2017 Naoki Nakagawa
#pragma once
#include <string>
#include <windows.h>
#include <wrl.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#if defined(_DEBUG)
#define Main() main()
#else
#define Main() WINAPI WinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
#endif

namespace GameLibrary {
	class Game {
	public:
		Game() = delete;
		static HWND GetWindow() {
			static HWND window = nullptr;

			if (window == nullptr) {
				HINSTANCE instance = GetModuleHandle(nullptr);

				WNDCLASSEX windowClass = {};
				windowClass.cbSize = sizeof(WNDCLASSEX);
				windowClass.style = CS_HREDRAW | CS_VREDRAW;
				windowClass.lpfnWndProc = ProcessWindow;
				windowClass.cbClsExtra = 0;
				windowClass.cbWndExtra = 0;
				windowClass.hInstance = instance;
				windowClass.hIcon = LoadIcon(instance, IDI_APPLICATION);
				windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
				windowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
				windowClass.lpszMenuName = nullptr;
				windowClass.lpszClassName = "GameLibrary";
				windowClass.hIconSm = LoadIcon(instance, IDI_APPLICATION);
				if (!RegisterClassEx(&windowClass)) return nullptr;

				window = CreateWindow("GameLibrary", "GameLibrary", WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, nullptr, nullptr, instance, nullptr);

				SetSize(1280, 720);

				ShowWindow(window, SW_SHOWNORMAL);
			}

			return window;
		}

		static DirectX::XMINT2 GetSize() {
			return Size();
		}

		static void SetSize(int width, int height) {
			Size() = DirectX::XMINT2(width, height);

			RECT windowRect = {};
			RECT clientRect = {};
			GetWindowRect(GetWindow(), &windowRect);
			GetClientRect(GetWindow(), &clientRect);

			int w = (windowRect.right - windowRect.left) - (clientRect.right - clientRect.left) + width;
			int h = (windowRect.bottom - windowRect.top) - (clientRect.bottom - clientRect.top) + height;

			int x = (GetSystemMetrics(SM_CXSCREEN) - w) / 2;
			int y = (GetSystemMetrics(SM_CYSCREEN) - h) / 2;

			SetWindowPos(GetWindow(), nullptr, x, y, w, h, SWP_NOZORDER);
		}

		static char* GetTitle() {
			char* title = nullptr;
			GetWindowText(GetWindow(), title, GetWindowTextLength(GetWindow()));
			return title;
		}

		static void SetTitle(char* title) {
			SetWindowText(GetWindow(), title);
		}

		static ID3D11Device& GetDevice() {
			static Microsoft::WRL::ComPtr<ID3D11Device> device = nullptr;

			if (device == nullptr) {
				int createDeviceFlag = 0;
#if defined(_DEBUG)
				createDeviceFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

				D3D_DRIVER_TYPE driverTypes[] = {
					D3D_DRIVER_TYPE_HARDWARE,
					D3D_DRIVER_TYPE_WARP,
					D3D_DRIVER_TYPE_REFERENCE,
				};
				int driverTypeCount = sizeof(driverTypes) / sizeof(driverTypes[0]);

				D3D_FEATURE_LEVEL featureLevels[] = {
					D3D_FEATURE_LEVEL_11_0,
					D3D_FEATURE_LEVEL_10_1,
					D3D_FEATURE_LEVEL_10_0,
				};
				int featureLevelCount = sizeof(featureLevels) / sizeof(featureLevels[0]);

				for (int i = 0; i < driverTypeCount; i++) {
					HRESULT result = D3D11CreateDevice(nullptr, driverTypes[i], nullptr, createDeviceFlag, featureLevels, featureLevelCount, D3D11_SDK_VERSION, device.GetAddressOf(), nullptr, nullptr);

					if (SUCCEEDED(result)) {
						break;
					}
				}
			}

			return *device.Get();
		}

		static IDXGISwapChain& GetSwapChain() {
			static Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain = nullptr;

			if (swapChain == nullptr) {
				const int SWAP_CHAIN_COUNT = 2;
				const DXGI_FORMAT SWAP_CHAIN_FORMAT = DXGI_FORMAT_R8G8B8A8_UNORM;
				const int MULTI_SAMPLE_COUNT = 1;
				const int MULTI_SAMPLE_QUALITY = 0;

				IDXGIDevice1* dxgiDevice = nullptr;
				IDXGIAdapter* adapter = nullptr;
				IDXGIFactory* factory = nullptr;

				GetDevice().QueryInterface(__uuidof(IDXGIDevice1), (void**)&dxgiDevice);
				dxgiDevice->GetAdapter(&adapter);
				adapter->GetParent(__uuidof(IDXGIFactory), (void**)&factory);

				DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
				swapChainDesc.BufferCount = SWAP_CHAIN_COUNT;
				swapChainDesc.BufferDesc.Width = GetSize().x;
				swapChainDesc.BufferDesc.Height = GetSize().y;
				swapChainDesc.BufferDesc.Format = SWAP_CHAIN_FORMAT;
				swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
				swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
				swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
				swapChainDesc.OutputWindow = GetWindow();
				swapChainDesc.SampleDesc.Count = MULTI_SAMPLE_COUNT;
				swapChainDesc.SampleDesc.Quality = MULTI_SAMPLE_QUALITY;
				swapChainDesc.Windowed = true;

				factory->CreateSwapChain(&GetDevice(), &swapChainDesc, swapChain.GetAddressOf());

				factory->Release();
				adapter->Release();
				dxgiDevice->Release();
			}

			return *swapChain.Get();
		}

		static ID3D11DeviceContext& GetDeviceContext() {
			static Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext = nullptr;
			static Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader = nullptr;
			static Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader = nullptr;
			static Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout = nullptr;

			if (deviceContext == nullptr) {
				GetDevice().GetImmediateContext(&deviceContext);

				D3D11_VIEWPORT viewPort = {};
				viewPort.Width = (float)GetSize().x;
				viewPort.Height = (float)GetSize().y;
				viewPort.MinDepth = 0.0f;
				viewPort.MaxDepth = 1.0f;
				viewPort.TopLeftX = 0;
				viewPort.TopLeftY = 0;
				deviceContext->RSSetViewports(1, &viewPort);

				ID3DBlob *vertexShaderBlob = nullptr;
				CompileShader(nullptr, "VS", "vs_4_0", &vertexShaderBlob);
				GetDevice().CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), nullptr, vertexShader.GetAddressOf());
				deviceContext->VSSetShader(vertexShader.Get(), nullptr, 0);

				ID3DBlob *pixelShaderBlob = nullptr;
				CompileShader(nullptr, "PS", "ps_4_0", &pixelShaderBlob);
				GetDevice().CreatePixelShader(pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize(), nullptr, pixelShader.GetAddressOf());
				pixelShaderBlob->Release();
				deviceContext->PSSetShader(pixelShader.Get(), nullptr, 0);

				D3D11_INPUT_ELEMENT_DESC inputElementDesc[] = {
					{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
					{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				};
				int inputElementDescCount = sizeof(inputElementDesc) / sizeof(inputElementDesc[0]);

				GetDevice().CreateInputLayout(inputElementDesc, inputElementDescCount, vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), inputLayout.GetAddressOf());
				vertexShaderBlob->Release();
				deviceContext->IASetInputLayout(inputLayout.Get());

				ID3D11BlendState* blendState = nullptr;
				D3D11_BLEND_DESC blendDesc = {};
				blendDesc.AlphaToCoverageEnable = false;
				blendDesc.IndependentBlendEnable = false;
				blendDesc.RenderTarget[0].BlendEnable = true;
				blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
				blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
				blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
				blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
				blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
				blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
				blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

				float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
				GetDevice().CreateBlendState(&blendDesc, &blendState);
				deviceContext->OMSetBlendState(blendState, blendFactor, 0xffffffff);
				blendState->Release();
			}

			return *deviceContext.Get();
		}

		static ID3D11RenderTargetView& GetRenderTargetView() {
			static Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView = nullptr;
			static Microsoft::WRL::ComPtr<ID3D11Texture2D> renderTargetTexture = nullptr;
			static Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> renderTargetShaderResourceView = nullptr;

			if (renderTargetView == nullptr) {
				GetSwapChain().GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)renderTargetTexture.GetAddressOf());

				GetDevice().CreateRenderTargetView(renderTargetTexture.Get(), nullptr, renderTargetView.GetAddressOf());

				GetDevice().CreateShaderResourceView(renderTargetTexture.Get(), nullptr, renderTargetShaderResourceView.GetAddressOf());

				GetDeviceContext().OMSetRenderTargets(1, renderTargetView.GetAddressOf(), nullptr);
			}

			return *renderTargetView.Get();
		}

		static DirectX::XMINT2 GetMousePosition() {
			return MousePosition();
		}

		static bool GetKey(int VK_CODE) {
			return KeyState()[VK_CODE] & 0x80;
		}

		static bool GetKeyUp(int VK_CODE) {
			return !(KeyState()[VK_CODE] & 0x80) && (PreKeyState()[VK_CODE] & 0x80);
		}

		static bool GetKeyDown(int VK_CODE) {
			return (KeyState()[VK_CODE] & 0x80) && !(PreKeyState()[VK_CODE] & 0x80);
		}

		static float GetTime() {
			return Time();
		}

		static float GetDeltaTime() {
			return DeltaTime();
		}

		static void AddFont(char* path) {
			AddFontResourceEx(path, FR_PRIVATE, nullptr);
		}

		static bool Update() {
			static float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

			GetSwapChain().Present(0, 0);

			if (!ProcessResponse()) {
				return false;
			}

			ProcessSize();
			ProcessMousePosition();
			ProcessKey();
			PrecessDeltaTime();
			PrecessTime();

			GetDeviceContext().ClearRenderTargetView(&GetRenderTargetView(), color);

			return true;
		}

	private:
		static DirectX::XMINT2& Size() {
			static DirectX::XMINT2 size;
			return size;
		}

		static DirectX::XMINT2& MousePosition() {
			static DirectX::XMINT2 mousePosition;
			return mousePosition;
		}

		static BYTE* PreKeyState() {
			static BYTE preKeyState[256];
			return preKeyState;
		}

		static BYTE* KeyState() {
			static BYTE keyState[256];
			return keyState;
		}

		static float& Time() {
			static float time = 0.0f;
			return time;
		}

		static float& DeltaTime() {
			static float deltaTime = 0.0f;
			return deltaTime;
		}

		static void CompileShader(WCHAR* filePath, char* entryPoint, char* shaderModel, ID3DBlob** out) {
			DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(_DEBUG)
			shaderFlags |= D3DCOMPILE_DEBUG;
#endif

			ID3DBlob *errorBlob = nullptr;

			if (filePath == nullptr) {
				std::string source("\
cbuffer CB:register(b0){matrix W;matrix V;matrix P;float4 C;};\
Texture2D Tex:register(t0);SamplerState S:register(s0);\
struct VO{float4 pos:SV_POSITION;float4 c:COLOR;float2 uv:TEXCOORD;};\
VO VS(float4 v:POSITION,float2 uv:TEXCOORD){VO o=(VO)0;o.pos=mul(W,v);o.pos=mul(V,o.pos);o.pos=mul(P,o.pos);o.c=C;o.uv=uv;return o;}\
float4 PS(VO o):SV_TARGET{return Tex.Sample(S,o.uv)*o.c;}");

				D3DCompile(source.c_str(), source.size(), nullptr, nullptr, nullptr, entryPoint, shaderModel, shaderFlags, 0, out, &errorBlob);
			}
			else {
				D3DCompileFromFile(filePath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint, shaderModel, shaderFlags, 0, out, &errorBlob);
			}

			if (errorBlob != nullptr) {
				OutputDebugString((char*)errorBlob->GetBufferPointer());
				errorBlob->Release();
			}
		}

		static void ProcessSize() {
			RECT clientRect = {};
			GetClientRect(GetWindow(), &clientRect);

			Size() = DirectX::XMINT2(clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
		}

		static void ProcessMousePosition() {
			POINT point = {};
			GetCursorPos(&point);

			ScreenToClient(GetWindow(), &point);
			MousePosition() = DirectX::XMINT2(point.x, point.y);
		}

		static void ProcessKey() {
			for (int i = 0; i < 256; i++) {
				PreKeyState()[i] = KeyState()[i];
			}

			GetKeyboardState(KeyState());
		}

		static LARGE_INTEGER GetCounter() {
			LARGE_INTEGER counter;
			QueryPerformanceCounter(&counter);
			return counter;
		}
		
		static LARGE_INTEGER GetCountFrequency() {
			LARGE_INTEGER frequency;
			QueryPerformanceFrequency(&frequency);
			return frequency;
		}

		static void PrecessTime() {
			Time() += GetDeltaTime();
		}

		static void PrecessDeltaTime() {
			static LARGE_INTEGER preTime = GetCounter();
			static LARGE_INTEGER frequency = GetCountFrequency();

			LARGE_INTEGER time = GetCounter();
			DeltaTime() = (float)(time.QuadPart - preTime.QuadPart) / frequency.QuadPart;
			preTime = GetCounter();
		}

		static bool ProcessResponse() {
			static MSG response = {};

			while (response.message != WM_QUIT) {
				if (PeekMessage(&response, nullptr, 0, 0, PM_REMOVE)) {
					TranslateMessage(&response);
					DispatchMessage(&response);
				}
				else {
					return true;
				}
			}

			return false;
		}

		static LRESULT WINAPI ProcessWindow(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
			if (message == WM_DESTROY) {
				PostQuitMessage(0);
			}
			return DefWindowProc(window, message, wParam, lParam);
		}
	};
}

// (c) 2017 Naoki Nakagawa
#pragma once
#include <wincodec.h>

namespace GameLibrary {
	class Sprite {
	public:
		Sprite(wchar_t* path) {
			IWICImagingFactory* factory = nullptr;
			CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&factory));
			IWICBitmapDecoder* decoder = nullptr;
			factory->CreateDecoderFromFilename(path, 0, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &decoder);
			IWICBitmapFrameDecode* frame = nullptr;
			decoder->GetFrame(0, &frame);
			frame->GetSize(&width, &height);
			WICPixelFormatGUID pixelFormat;
			frame->GetPixelFormat(&pixelFormat);
			BYTE* textureBuffer = new BYTE[width * height * 4];

			if (pixelFormat != GUID_WICPixelFormat32bppRGBA) {
				IWICFormatConverter* formatConverter = nullptr;
				factory->CreateFormatConverter(&formatConverter);

				formatConverter->Initialize(frame, GUID_WICPixelFormat32bppRGBA, WICBitmapDitherTypeErrorDiffusion, 0, 0, WICBitmapPaletteTypeCustom);

				formatConverter->CopyPixels(0, width * 4, width * height * 4, textureBuffer);
			}
			else {
				frame->CopyPixels(0, width * 4, width * height * 4, textureBuffer);
			}

			D3D11_TEXTURE2D_DESC textureDesc = {};
			textureDesc.Width = width;
			textureDesc.Height = height;
			textureDesc.MipLevels = 1;
			textureDesc.ArraySize = 1;
			textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			textureDesc.SampleDesc.Count = 1;
			textureDesc.SampleDesc.Quality = 0;
			textureDesc.Usage = D3D11_USAGE_DEFAULT;
			textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
			textureDesc.CPUAccessFlags = 0;
			textureDesc.MiscFlags = 0;

			D3D11_SUBRESOURCE_DATA textureSubresourceData;
			textureSubresourceData.pSysMem = textureBuffer;
			textureSubresourceData.SysMemPitch = width * 4;
			textureSubresourceData.SysMemSlicePitch = width * height * 4;
			Game::GetDevice().CreateTexture2D(&textureDesc, &textureSubresourceData, &texture);

			delete[] textureBuffer;

			Initialize();

			Position() = DirectX::XMFLOAT2(0.0f, 0.0f);
			Angle() = 0.0f;
			Scale() = DirectX::XMFLOAT2(1.0f, 1.0f);
			Color() = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		}

		virtual ~Sprite() {
			if (texture)
				texture->Release();

			if (shaderResourceView)
				shaderResourceView->Release();

			if (samplerState)
				samplerState->Release();

			if (vertexBuffer)
				vertexBuffer->Release();

			if (indexBuffer)
				indexBuffer->Release();

			if (constantBuffer)
				constantBuffer->Release();
		}

		DirectX::XMINT2 GetSize() {
			return DirectX::XMINT2(width, height);
		}

		void SetScale(float scale) {
			Scale() = DirectX::XMFLOAT2(scale, scale);
		}

		DirectX::XMFLOAT2& Position() {
			return position;
		}

		float& Angle() {
			return angle;
		}

		DirectX::XMFLOAT2& Scale() {
			return scale;
		}

		DirectX::XMFLOAT4& Color() {
			return color;
		}

		void Draw() {
			using namespace DirectX;

			constant.world = XMMatrixIdentity();
			constant.world *= XMMatrixScaling(width * Scale().x, height * Scale().y, 1.0f);
			constant.world *= XMMatrixRotationZ(XMConvertToRadians(-Angle()));
			constant.world *= XMMatrixTranslation(Position().x, -Position().y, 0.0f);
			constant.color = Color();

			Game::GetDeviceContext().UpdateSubresource(constantBuffer, 0, nullptr, &constant, 0, 0);

			Game::GetDeviceContext().VSSetConstantBuffers(0, 1, &constantBuffer);
			Game::GetDeviceContext().PSSetShaderResources(0, 1, &shaderResourceView);
			Game::GetDeviceContext().PSSetSamplers(0, 1, &samplerState);

			Game::GetDeviceContext().DrawIndexed(indexCount, 0, 0);
		}

	protected:
		struct Constant {
			DirectX::XMMATRIX world;
			DirectX::XMMATRIX view;
			DirectX::XMMATRIX projection;
			DirectX::XMFLOAT4 color;
		};

		DirectX::XMFLOAT2 position;
		float angle;
		DirectX::XMFLOAT2 scale;
		DirectX::XMFLOAT4 color;
		UINT width;
		UINT height;
		ID3D11Texture2D* texture;
		Constant constant;

		Sprite() {
		}

		void Initialize() {
			using namespace DirectX;

			Vertex quad[] = {
				{ XMFLOAT3(-0.5f, 0.5f, 0.0f), XMFLOAT2(0.0f, 0.0f) },
				{ XMFLOAT3(0.5f, 0.5f, 0.0f), XMFLOAT2(1.0f, 0.0f) },
				{ XMFLOAT3(-0.5f, -0.5f, 0.0f), XMFLOAT2(0.0f, 1.0f) },
				{ XMFLOAT3(0.5f, -0.5f, 0.0f), XMFLOAT2(1.0f, 1.0f) },
			};
			int vertexCount = sizeof(quad) / sizeof(quad[0]);

			int index[] = {
				0, 1, 2,
				3, 2, 1,
			};
			indexCount = sizeof(index) / sizeof(index[0]);

			constant.view = XMMatrixLookAtLH(XMVectorSet(Game::GetSize().x / 2.0f, -Game::GetSize().y / 2.0f, 0.0f, 0.0f), XMVectorSet(Game::GetSize().x / 2.0f, -Game::GetSize().y / 2.0f, 1.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
			constant.projection = XMMatrixOrthographicLH(Game::GetSize().x * 1.0f, Game::GetSize().y * 1.0f, -1.0f, 1.0f);

			D3D11_BUFFER_DESC vertexBufferDesc = {};
			vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
			vertexBufferDesc.ByteWidth = sizeof(Vertex) * vertexCount;
			vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			vertexBufferDesc.CPUAccessFlags = 0;
			D3D11_SUBRESOURCE_DATA vertexSubresourceData = {};
			vertexSubresourceData.pSysMem = quad;
			Game::GetDevice().CreateBuffer(&vertexBufferDesc, &vertexSubresourceData, &vertexBuffer);

			UINT stride = sizeof(Vertex);
			UINT offset = 0;
			Game::GetDeviceContext().IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
			Game::GetDeviceContext().IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			D3D11_BUFFER_DESC indexBufferDesc = {};
			indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
			indexBufferDesc.ByteWidth = sizeof(int) * indexCount;
			indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			indexBufferDesc.CPUAccessFlags = 0;
			D3D11_SUBRESOURCE_DATA indexSubresourceData = {};
			indexSubresourceData.pSysMem = index;
			Game::GetDevice().CreateBuffer(&indexBufferDesc, &indexSubresourceData, &indexBuffer);

			Game::GetDeviceContext().IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

			D3D11_BUFFER_DESC constantBufferDesc = {};
			constantBufferDesc.ByteWidth = sizeof(Constant);
			constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
			constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			constantBufferDesc.CPUAccessFlags = 0;
			Game::GetDevice().CreateBuffer(&constantBufferDesc, nullptr, &constantBuffer);

			D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc = {};
			shaderResourceViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			shaderResourceViewDesc.Texture2D.MipLevels = 1;
			Game::GetDevice().CreateShaderResourceView(texture, &shaderResourceViewDesc, &shaderResourceView);

			D3D11_SAMPLER_DESC samplerDesc;
			samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.MipLODBias = 0.0f;
			samplerDesc.MaxAnisotropy = 1;
			samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
			samplerDesc.BorderColor[0] = 0;
			samplerDesc.BorderColor[1] = 0;
			samplerDesc.BorderColor[2] = 0;
			samplerDesc.BorderColor[3] = 0;
			samplerDesc.MinLOD = 0;
			samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
			Game::GetDevice().CreateSamplerState(&samplerDesc, &samplerState);
		}

	private:
		struct Vertex {
			DirectX::XMFLOAT3 position;
			DirectX::XMFLOAT2 uv;
		};

		wchar_t* path;
		int indexCount;
		ID3D11Buffer* vertexBuffer;
		ID3D11Buffer* indexBuffer;
		ID3D11Buffer* constantBuffer;
		ID3D11ShaderResourceView* shaderResourceView;
		ID3D11SamplerState* samplerState;
	};
}

// (c) 2017 Naoki Nakagawa
#pragma once
#include <strsafe.h>

namespace GameLibrary {
	class Text : public Sprite {
	public:
		Text(char* text, char* fontFamily = "‚l‚r –¾’©") {
			using namespace DirectX;

			LOGFONT logFont = {};
			logFont.lfHeight = 256;
			logFont.lfWidth = 0;
			logFont.lfEscapement = 0;
			logFont.lfOrientation = 0;
			logFont.lfWeight = 0;
			logFont.lfItalic = false;
			logFont.lfUnderline = false;
			logFont.lfStrikeOut = false;
			logFont.lfCharSet = SHIFTJIS_CHARSET;
			logFont.lfOutPrecision = OUT_TT_ONLY_PRECIS;
			logFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
			logFont.lfQuality = PROOF_QUALITY;
			logFont.lfPitchAndFamily = FIXED_PITCH | FF_MODERN;
			StringCchCopy(logFont.lfFaceName, 32, fontFamily);
			HFONT font = CreateFontIndirect(&logFont);

			HDC dc = GetDC(nullptr);
			HFONT oldFont = (HFONT)SelectObject(dc, font);

			UINT code = 0;
#if _UNICODE
			code = (UINT)*text;
#else
			if (IsDBCSLeadByte(*text)) {
				code = (BYTE)text[0] << 8 | (BYTE)text[1];
			}
			else {
				code = text[0];
			}
#endif

			TEXTMETRIC textMetrics = {};
			GetTextMetrics(dc, &textMetrics);
			GLYPHMETRICS glyphMetrics;
			const MAT2 matrix = { { 0, 1 },{ 0, 0 },{ 0, 0 },{ 0, 1 } };
			DWORD size = GetGlyphOutline(dc, code, GGO_GRAY4_BITMAP, &glyphMetrics, 0, nullptr, &matrix);
			BYTE* ptr = new BYTE[size];
			GetGlyphOutline(dc, code, GGO_GRAY4_BITMAP, &glyphMetrics, size, ptr, &matrix);

			SelectObject(dc, oldFont);
			DeleteObject(font);
			ReleaseDC(nullptr, dc);

			width = glyphMetrics.gmCellIncX;
			height = textMetrics.tmHeight;

			D3D11_TEXTURE2D_DESC textureDesc = {};
			textureDesc.Width = width;
			textureDesc.Height = height;
			textureDesc.MipLevels = 1;
			textureDesc.ArraySize = 1;
			textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			textureDesc.SampleDesc.Count = 1;
			textureDesc.SampleDesc.Quality = 0;
			textureDesc.Usage = D3D11_USAGE_DYNAMIC;
			textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
			textureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			textureDesc.MiscFlags = 0;

			Game::GetDevice().CreateTexture2D(&textureDesc, nullptr, &texture);

			D3D11_MAPPED_SUBRESOURCE mapped;
			Game::GetDeviceContext().Map(texture, D3D11CalcSubresource(0, 0, 1), D3D11_MAP_WRITE_DISCARD, 0, &mapped);

			BYTE* bits = (BYTE*)mapped.pData;
			XMINT2 origin;
			origin.x = glyphMetrics.gmptGlyphOrigin.x;
			origin.y = textMetrics.tmAscent - glyphMetrics.gmptGlyphOrigin.y;
			XMINT2 bitmapSize;
			bitmapSize.x = glyphMetrics.gmBlackBoxX + (4 - (glyphMetrics.gmBlackBoxX % 4)) % 4;
			bitmapSize.y = glyphMetrics.gmBlackBoxY;
			const int LEVEL = 17;
			memset(bits, 0, mapped.RowPitch * textMetrics.tmHeight);

			for (int y = origin.y; y < origin.y + bitmapSize.y; y++) {
				for (int x = origin.x; x < origin.x + bitmapSize.x; x++) {
					DWORD alpha = (255 * ptr[x - origin.x + bitmapSize.x * (y - origin.y)]) / (LEVEL - 1);
					DWORD color = 0x00ffffff | (alpha << 24);
					memcpy((BYTE*)bits + mapped.RowPitch * y + 4 * x, &color, sizeof(DWORD));
				}
			}

			Game::GetDeviceContext().Unmap(texture, D3D11CalcSubresource(0, 0, 1));
			delete[] ptr;

			Initialize();

			Position() = XMFLOAT2(0.0f, 0.0f);
			Angle() = 0.0f;
			Scale() = XMFLOAT2(1.0f, 1.0f);
			Color() = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
		}
	};
}

