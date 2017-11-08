// (c) 2017 Naoki Nakagawa
#pragma once
#include <vector>
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
			return GetSizeProperty();
		}

		static void SetSize(int width, int height) {
			GetSizeProperty() = DirectX::XMINT2(width, height);

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
				CompileShader(L"shader.fx", "VS", "vs_4_0", &vertexShaderBlob);
				GetDevice().CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), nullptr, vertexShader.GetAddressOf());
				deviceContext->VSSetShader(vertexShader.Get(), nullptr, 0);

				ID3DBlob *pixelShaderBlob = nullptr;
				CompileShader(L"shader.fx", "PS", "ps_4_0", &pixelShaderBlob);
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
			return GetMousePositionProperty();
		}

		static bool GetKey(int VK_CODE) {
			return GetKeyStateProperty()[VK_CODE] & 0x80;
		}

		static bool GetKeyUp(int VK_CODE) {
			return !(GetKeyStateProperty()[VK_CODE] & 0x80) && (GetPreKeyStateProperty()[VK_CODE] & 0x80);
		}

		static bool GetKeyDown(int VK_CODE) {
			return (GetKeyStateProperty()[VK_CODE] & 0x80) && !(GetPreKeyStateProperty()[VK_CODE] & 0x80);
		}

		static float GetDeltaTime() {
			return GetDeltaTimeProperty();
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

			GetDeviceContext().ClearRenderTargetView(&GetRenderTargetView(), color);

			return true;
		}

	private:
		static DirectX::XMINT2& GetSizeProperty() {
			static DirectX::XMINT2 size;
			return size;
		}

		static DirectX::XMINT2& GetMousePositionProperty() {
			static DirectX::XMINT2 mousePosition;
			return mousePosition;
		}

		static BYTE* GetPreKeyStateProperty() {
			static BYTE preKeyState[256];
			return preKeyState;
		}

		static BYTE* GetKeyStateProperty() {
			static BYTE keyState[256];
			return keyState;
		}

		static float& GetDeltaTimeProperty() {
			static float deltaTime;
			return deltaTime;
		}

		static void CompileShader(WCHAR* filePath, char* entryPoint, char* shaderModel, ID3DBlob** out) {
			DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(_DEBUG)
			shaderFlags |= D3DCOMPILE_DEBUG;
#endif

			ID3DBlob *errorBlob = nullptr;

			D3DCompileFromFile(filePath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint, shaderModel, shaderFlags, 0, out, &errorBlob);

			if (errorBlob != nullptr) {
				OutputDebugString((char*)errorBlob->GetBufferPointer());
				errorBlob->Release();
			}
		}

		static void ProcessSize() {
			RECT clientRect = {};
			GetClientRect(GetWindow(), &clientRect);

			GetSizeProperty() = DirectX::XMINT2(clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
		}

		static void ProcessMousePosition() {
			POINT point = {};
			GetCursorPos(&point);

			ScreenToClient(GetWindow(), &point);
			GetMousePositionProperty() = DirectX::XMINT2(point.x, point.y);
		}

		static void ProcessKey() {
			for (int i = 0; i < 256; i++) {
				GetPreKeyStateProperty()[i] = GetKeyStateProperty()[i];
			}

			GetKeyboardState(GetKeyStateProperty());
		}

		static void PrecessDeltaTime() {
			static float preTime = GetTickCount() / 1000.0f;

			GetDeltaTimeProperty() = (GetTickCount() / 1000.0f) - preTime;
			preTime = GetTickCount() / 1000.0f;
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

#include "Sprite.h"
#include "Text.h"
