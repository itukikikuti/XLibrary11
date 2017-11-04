#include <windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "Game.h"
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

using namespace std;
using namespace DirectX;
using namespace GameLibrary;

HWND Game::window = nullptr;
unique_ptr<ID3D11Device, Game::ComReleaser> Game::device = nullptr;
unique_ptr<ID3D11DeviceContext, Game::ComReleaser> Game::deviceContext = nullptr;
unique_ptr<IDXGISwapChain, Game::ComReleaser> Game::swapChain = nullptr;
unique_ptr<ID3D11RenderTargetView, Game::ComReleaser> Game::renderTargetView = nullptr;
unique_ptr<ID3D11Texture2D, Game::ComReleaser> Game::renderTargetTexture = nullptr;
unique_ptr<ID3D11ShaderResourceView, Game::ComReleaser> Game::renderTargetShaderResourceView = nullptr;
unique_ptr<ID3D11VertexShader, Game::ComReleaser> Game::vertexShader = nullptr;
unique_ptr<ID3D11PixelShader, Game::ComReleaser> Game::pixelShader = nullptr;
unique_ptr<ID3D11InputLayout, Game::ComReleaser> Game::inputLayout = nullptr;
float Game::color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
float Game::previosTime = 0.0f;
float Game::deltaTime = 0.0f;
MSG Game::response = {};

HWND Game::GetWindow() {
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

int Game::GetWidth() {
	RECT clientRect = {};
	GetClientRect(GetWindow(), &clientRect);

	return (clientRect.right - clientRect.left);
}

int Game::GetHeight() {
	RECT clientRect = {};
	GetClientRect(GetWindow(), &clientRect);

	return (clientRect.bottom - clientRect.top);
}

void Game::SetSize(int width, int height) {
	RECT windowRect = {};
	RECT clientRect = {};
	GetWindowRect(GetWindow(), &windowRect);
	GetClientRect(GetWindow(), &clientRect);

	int w = (windowRect.right - windowRect.left) - (clientRect.right - clientRect.left) + width;
	int h = (windowRect.bottom - windowRect.top) - (clientRect.bottom - clientRect.top) + height;

	SetWindowPos(GetWindow(), nullptr, 0, 0, w, h, SWP_NOMOVE | SWP_NOZORDER);
}

ID3D11Device& Game::GetDevice() {
	if (device.get() == nullptr) {
		CreateDeviceAndSwapChain();
	}

	return *device.get();
}

IDXGISwapChain& Game::GetSwapChain() {
	if (swapChain.get() == nullptr) {
		CreateDeviceAndSwapChain();
	}

	return *swapChain.get();
}

ID3D11DeviceContext& Game::GetDeviceContext() {
	if (deviceContext.get() == nullptr) {
		ID3D11DeviceContext* dc = nullptr;
		GetDevice().GetImmediateContext(&dc);
		deviceContext.reset(dc);

		ID3D11RenderTargetView* rtv = renderTargetView.get();
		deviceContext->OMSetRenderTargets(1, &rtv, nullptr);
		
		D3D11_VIEWPORT viewPort;
		viewPort.Width = (float)GetWidth();
		viewPort.Height = (float)GetHeight();
		viewPort.MinDepth = 0.0f;
		viewPort.MaxDepth = 1.0f;
		viewPort.TopLeftX = 0;
		viewPort.TopLeftY = 0;
		deviceContext->RSSetViewports(1, &viewPort);

		ID3D11VertexShader* vs;
		ID3D11PixelShader* ps;
		ID3D11InputLayout* il;

		ID3DBlob *vertexShaderBlob = nullptr;
		CompileShader(L"shader.fx", "VS", "vs_4_0", &vertexShaderBlob);
		GetDevice().CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), nullptr, &vs);
		vertexShader.reset(vs);
		deviceContext->VSSetShader(vertexShader.get(), nullptr, 0);

		ID3DBlob *pixelShaderBlob = nullptr;
		CompileShader(L"shader.fx", "PS", "ps_4_0", &pixelShaderBlob);
		GetDevice().CreatePixelShader(pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize(), nullptr, &ps);
		pixelShaderBlob->Release();
		pixelShader.reset(ps);
		deviceContext->PSSetShader(pixelShader.get(), nullptr, 0);

		D3D11_INPUT_ELEMENT_DESC inputElementDesc[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		int inputElementDescCount = sizeof(inputElementDesc) / sizeof(inputElementDesc[0]);

		GetDevice().CreateInputLayout(inputElementDesc, inputElementDescCount, vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), &il);
		vertexShaderBlob->Release();
		inputLayout.reset(il);
		deviceContext->IASetInputLayout(inputLayout.get());

		previosTime = GetTickCount() / 1000.0f;
	}

	return *deviceContext.get();
}

float Game::GetDeltaTime()
{
	return deltaTime;
}

bool Game::Update() {
	GetSwapChain().Present(0, 0);

	if (!ProcessResponse()) {
		return false;
	}

	GetDeviceContext().ClearRenderTargetView(renderTargetView.get(), color);

	deltaTime = (GetTickCount() / 1000.0f) - previosTime;
	previosTime = GetTickCount() / 1000.0f;

	return true;
}

void Game::CreateDeviceAndSwapChain() {
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

	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferCount = SWAP_CHAIN_COUNT;
	swapChainDesc.BufferDesc.Width = GetWidth();
	swapChainDesc.BufferDesc.Height = GetHeight();
	swapChainDesc.BufferDesc.Format = SWAP_CHAIN_FORMAT;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
	swapChainDesc.OutputWindow = GetWindow();
	swapChainDesc.SampleDesc.Count = MULTI_SAMPLE_COUNT;
	swapChainDesc.SampleDesc.Quality = MULTI_SAMPLE_QUALITY;
	swapChainDesc.Windowed = true;

	for (int i = 0; i < driverTypeCount; i++) {
		ID3D11Device* d = nullptr;
		IDXGISwapChain* sc = nullptr;
		HRESULT result = D3D11CreateDeviceAndSwapChain(nullptr, driverTypes[i], nullptr, createDeviceFlag, featureLevels, featureLevelCount, D3D11_SDK_VERSION, &swapChainDesc, &sc, &d, nullptr, nullptr);

		if (SUCCEEDED(result)) {
			device.reset(d);
			swapChain.reset(sc);
			break;
		}
	}

	ID3D11RenderTargetView* rtv = nullptr;
	ID3D11Texture2D* rtt = nullptr;
	ID3D11ShaderResourceView* rtsrv = nullptr;

	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&rtt);
	renderTargetTexture.reset(rtt);

	device->CreateRenderTargetView(renderTargetTexture.get(), nullptr, &rtv);
	renderTargetView.reset(rtv);

	device->CreateShaderResourceView(renderTargetTexture.get(), nullptr, &rtsrv);
	renderTargetShaderResourceView.reset(rtsrv);
}

void Game::CompileShader(WCHAR* filePath, char* entryPoint, char* shaderModel, ID3DBlob** out)
{
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

bool Game::ProcessResponse() {
	printf("%d\n", response.message);
	while (response.message != WM_QUIT) {
		if (PeekMessage(&response, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&response);
			DispatchMessage(&response);
		}
		else {
			return true;
		}
	}

	PostQuitMessage(response.wParam);
	return false;
}

LRESULT WINAPI Game::ProcessWindow(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
	if (message == WM_DESTROY) {
		PostQuitMessage(wParam);
	}
	return DefWindowProc(window, message, wParam, lParam);
}
