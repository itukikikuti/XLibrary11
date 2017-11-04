#include <memory>
#include <wrl.h>
#include "Game.h"

using namespace std;
using namespace Microsoft::WRL;
using namespace DirectX;
using namespace GameLibrary;

float Game::color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
float Game::deltaTime = 0.0f;

HWND Game::GetWindow() {
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

char* Game::GetTitle() {
	char* title = nullptr;
	GetWindowText(GetWindow(), title, GetWindowTextLength(GetWindow()));
	return title;
}

void Game::SetTitle(char* title) {
	SetWindowText(GetWindow(), title);
}

ID3D11Device& Game::GetDevice() {
	static ComPtr<ID3D11Device> device = nullptr;

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

IDXGISwapChain& Game::GetSwapChain() {
	static ComPtr<IDXGISwapChain> swapChain = nullptr;

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

		factory->CreateSwapChain(&GetDevice(), &swapChainDesc, swapChain.GetAddressOf());

		factory->Release();
		adapter->Release();
		dxgiDevice->Release();
	}

	return *swapChain.Get();
}

ID3D11DeviceContext& Game::GetDeviceContext() {
	static ComPtr<ID3D11DeviceContext> deviceContext = nullptr;
	static ComPtr<ID3D11VertexShader> vertexShader = nullptr;
	static ComPtr<ID3D11PixelShader> pixelShader = nullptr;
	static ComPtr<ID3D11InputLayout> inputLayout = nullptr;

	if (deviceContext == nullptr) {
		GetDevice().GetImmediateContext(&deviceContext);
		
		D3D11_VIEWPORT viewPort;
		viewPort.Width = (float)GetWidth();
		viewPort.Height = (float)GetHeight();
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
	}

	return *deviceContext.Get();
}

ID3D11RenderTargetView& Game::GetRenderTargetView() {
	static ComPtr<ID3D11RenderTargetView> renderTargetView = nullptr;
	static ComPtr<ID3D11Texture2D> renderTargetTexture = nullptr;
	static ComPtr<ID3D11ShaderResourceView> renderTargetShaderResourceView = nullptr;

	if (renderTargetView == nullptr) {
		GetSwapChain().GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)renderTargetTexture.GetAddressOf());

		GetDevice().CreateRenderTargetView(renderTargetTexture.Get(), nullptr, renderTargetView.GetAddressOf());

		GetDevice().CreateShaderResourceView(renderTargetTexture.Get(), nullptr, renderTargetShaderResourceView.GetAddressOf());

		GetDeviceContext().OMSetRenderTargets(1, renderTargetView.GetAddressOf(), nullptr);
	}

	return *renderTargetView.Get();
}

float Game::GetDeltaTime() {
	return deltaTime;
}

bool Game::Update() {
	GetSwapChain().Present(0, 0);

	if (!ProcessResponse()) {
		return false;
	}

	PrecessDeltaTime();

	GetDeviceContext().ClearRenderTargetView(&GetRenderTargetView(), color);

	return true;
}

void Game::CompileShader(WCHAR* filePath, char* entryPoint, char* shaderModel, ID3DBlob** out) {
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

void Game::PrecessDeltaTime() {
	static unique_ptr<float> previosTime(new float(GetTickCount() / 1000.0f));

	deltaTime = (GetTickCount() / 1000.0f) - *previosTime;
	*previosTime = GetTickCount() / 1000.0f;
}

bool Game::ProcessResponse() {
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

	PostQuitMessage(response.wParam);
	return false;
}

LRESULT WINAPI Game::ProcessWindow(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
	if (message == WM_DESTROY) {
		PostQuitMessage(wParam);
	}
	return DefWindowProc(window, message, wParam, lParam);
}
