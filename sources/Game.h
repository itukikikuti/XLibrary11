// (c) 2017 Naoki Nakagawa
#pragma once
#include <string>
#include <tchar.h>
#include <windows.h>
#include <wrl.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#define Main() WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
#define PUBLIC public:
#define PRIVATE private:
#define PROTECTED protected:

namespace GameLibrary {
	class Game {
		PUBLIC Game() = delete;
		PUBLIC static HWND GetWindow() {
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
				windowClass.lpszClassName = _T("GameLibrary");
				windowClass.hIconSm = LoadIcon(instance, IDI_APPLICATION);
				if (!RegisterClassEx(&windowClass)) return nullptr;

				window = CreateWindow(_T("GameLibrary"), _T("GameLibrary"), WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, nullptr, nullptr, instance, nullptr);

				SetSize(1280, 720);

				ShowWindow(window, SW_SHOWNORMAL);
			}

			return window;
		}
		PUBLIC static DirectX::XMINT2 GetSize() {
			return Size();
		}
		PUBLIC static void SetSize(int width, int height) {
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
		PUBLIC static TCHAR* GetTitle() {
			TCHAR* title = nullptr;
			GetWindowText(GetWindow(), title, GetWindowTextLength(GetWindow()));
			return title;
		}
		PUBLIC static void SetTitle(const TCHAR* title) {
			SetWindowText(GetWindow(), title);
		}
		PUBLIC static ID3D11Device& GetDevice() {
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
		PUBLIC static IDXGISwapChain& GetSwapChain() {
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
		PUBLIC static ID3D11DeviceContext& GetDeviceContext() {
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
		PUBLIC static ID3D11RenderTargetView& GetRenderTargetView() {
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
		PUBLIC static DirectX::XMINT2 GetMousePosition() {
			return MousePosition();
		}
		PUBLIC static bool GetKey(int VK_CODE) {
			return KeyState()[VK_CODE] & 0x80;
		}
		PUBLIC static bool GetKeyUp(int VK_CODE) {
			return !(KeyState()[VK_CODE] & 0x80) && (PreKeyState()[VK_CODE] & 0x80);
		}
		PUBLIC static bool GetKeyDown(int VK_CODE) {
			return (KeyState()[VK_CODE] & 0x80) && !(PreKeyState()[VK_CODE] & 0x80);
		}
		PUBLIC static float GetTime() {
			return Time();
		}
		PUBLIC static float GetDeltaTime() {
			return DeltaTime();
		}
		PUBLIC static void AddFont(const TCHAR* path) {
			AddFontResourceEx(path, FR_PRIVATE, nullptr);
		}
		PUBLIC static bool Update() {
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
		PUBLIC static std::wstring GetWideChar(const TCHAR* tstring) {
#ifdef UNICODE
			return (wchar_t*)tstring;
#else
			size_t length = _tcslen(tstring) + 1;
			size_t result = 0;
			wchar_t* wstring = new wchar_t[length];
			mbstowcs_s(&result, wstring, length, tstring, _TRUNCATE);

			std::wstring wideString(wstring);
			delete wstring;
			return wideString;
#endif
		}
		PRIVATE static DirectX::XMINT2& Size() {
			static DirectX::XMINT2 size;
			return size;
		}
		PRIVATE static DirectX::XMINT2& MousePosition() {
			static DirectX::XMINT2 mousePosition;
			return mousePosition;
		}
		PRIVATE static BYTE* PreKeyState() {
			static BYTE preKeyState[256];
			return preKeyState;
		}
		PRIVATE static BYTE* KeyState() {
			static BYTE keyState[256];
			return keyState;
		}
		PRIVATE static float& Time() {
			static float time = 0.0f;
			return time;
		}
		PRIVATE static float& DeltaTime() {
			static float deltaTime = 0.0f;
			return deltaTime;
		}
		PRIVATE static void CompileShader(const TCHAR* path, const char* entryPoint, const char* shaderModel, ID3DBlob** out) {
			DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(_DEBUG)
			shaderFlags |= D3DCOMPILE_DEBUG;
#endif

			ID3DBlob *errorBlob = nullptr;

			if (path == nullptr) {
				char* shader = "\
cbuffer CB:register(b0){matrix W;matrix V;matrix P;float4 C;};\
Texture2D Tex:register(t0);SamplerState S:register(s0);\
struct VO{float4 pos:SV_POSITION;float4 c:COLOR;float2 uv:TEXCOORD;};\
VO VS(float4 v:POSITION,float2 uv:TEXCOORD){VO o=(VO)0;o.pos=mul(W,v);o.pos=mul(V,o.pos);o.pos=mul(P,o.pos);o.c=C;o.uv=uv;return o;}\
float4 PS(VO o):SV_TARGET{return Tex.Sample(S,o.uv)*o.c;}";

				D3DCompile(shader, strlen(shader), nullptr, nullptr, nullptr, entryPoint, shaderModel, shaderFlags, 0, out, &errorBlob);
			}
			else {
				D3DCompileFromFile(GetWideChar(path).c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint, shaderModel, shaderFlags, 0, out, &errorBlob);
			}

			if (errorBlob != nullptr) {
				OutputDebugString((TCHAR*)errorBlob->GetBufferPointer());
				errorBlob->Release();
			}
		}
		PRIVATE static void ProcessSize() {
			RECT clientRect = {};
			GetClientRect(GetWindow(), &clientRect);

			Size() = DirectX::XMINT2(clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
		}
		PRIVATE static void ProcessMousePosition() {
			POINT point = {};
			GetCursorPos(&point);

			ScreenToClient(GetWindow(), &point);
			MousePosition() = DirectX::XMINT2(point.x, point.y);
		}
		PRIVATE static void ProcessKey() {
			for (int i = 0; i < 256; i++) {
				PreKeyState()[i] = KeyState()[i];
			}

			GetKeyboardState(KeyState());
		}
		PRIVATE static LARGE_INTEGER GetCounter() {
			LARGE_INTEGER counter;
			QueryPerformanceCounter(&counter);
			return counter;
		}
		PRIVATE static LARGE_INTEGER GetCountFrequency() {
			LARGE_INTEGER frequency;
			QueryPerformanceFrequency(&frequency);
			return frequency;
		}
		PRIVATE static void PrecessTime() {
			Time() += GetDeltaTime();
		}
		PRIVATE static void PrecessDeltaTime() {
			static LARGE_INTEGER preTime = GetCounter();
			static LARGE_INTEGER frequency = GetCountFrequency();

			LARGE_INTEGER time = GetCounter();
			DeltaTime() = (float)(time.QuadPart - preTime.QuadPart) / frequency.QuadPart;
			preTime = GetCounter();
		}
		PRIVATE static bool ProcessResponse() {
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
		PRIVATE static LRESULT WINAPI ProcessWindow(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
			if (message == WM_DESTROY) {
				PostQuitMessage(0);
			}
			return DefWindowProc(window, message, wParam, lParam);
		}
	};
}

#include "Sprite.h"
#include "Text.h"
