#include <windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "Graphics.h"
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

using namespace std;
using namespace DirectX;

HWND Graphics::window = nullptr;
unique_ptr<ID3D11Device, Graphics::ComReleaser> Graphics::device = nullptr;
unique_ptr<ID3D11DeviceContext, Graphics::ComReleaser> Graphics::deviceContext = nullptr;
unique_ptr<IDXGISwapChain, Graphics::ComReleaser> Graphics::swapChain = nullptr;
unique_ptr<ID3D11RenderTargetView, Graphics::ComReleaser> Graphics::renderTargetView = nullptr;
unique_ptr<ID3D11Texture2D, Graphics::ComReleaser> Graphics::renderTargetTexture = nullptr;
unique_ptr<ID3D11ShaderResourceView, Graphics::ComReleaser> Graphics::renderTargetShaderResourceView = nullptr;
unique_ptr<ID3D11VertexShader, Graphics::ComReleaser> Graphics::vertexShader = nullptr;
unique_ptr<ID3D11PixelShader, Graphics::ComReleaser> Graphics::pixelShader = nullptr;
unique_ptr<ID3D11InputLayout, Graphics::ComReleaser> Graphics::inputLayout = nullptr;
float Graphics::color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
float Graphics::previosTime = 0.0f;
float Graphics::deltaTime = 0.0f;
MSG Graphics::response = {};

HWND Graphics::GetWindow() {
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
		if (window == nullptr) return nullptr;

		SetSize(1280, 720);

		ShowWindow(window, SW_SHOWNORMAL);
	}

	return window;
}

int Graphics::GetWidth() {
	RECT clientRect = {};
	GetClientRect(GetWindow(), &clientRect);

	return (clientRect.right - clientRect.left);
}

int Graphics::GetHeight() {
	RECT clientRect = {};
	GetClientRect(GetWindow(), &clientRect);

	return (clientRect.bottom - clientRect.top);
}

void Graphics::SetSize(int width, int height) {
	RECT windowRect = {};
	RECT clientRect = {};
	GetWindowRect(GetWindow(), &windowRect);
	GetClientRect(GetWindow(), &clientRect);

	int w = (windowRect.right - windowRect.left) - (clientRect.right - clientRect.left) + width;
	int h = (windowRect.bottom - windowRect.top) - (clientRect.bottom - clientRect.top) + height;

	SetWindowPos(GetWindow(), nullptr, 0, 0, w, h, SWP_NOMOVE | SWP_NOZORDER);
}

ID3D11Device& Graphics::GetDevice() {
	if (device.get() == nullptr) {
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

		HRESULT result = {};

		for (int i = 0; i < driverTypeCount; i++) {
			ID3D11Device* d = nullptr;
			IDXGISwapChain* sc = nullptr;
			result = D3D11CreateDeviceAndSwapChain(nullptr, driverTypes[i], nullptr, createDeviceFlag, featureLevels, featureLevelCount, D3D11_SDK_VERSION, &swapChainDesc, &sc, &d, nullptr, nullptr);

			if (SUCCEEDED(result)) {
				device.reset(d);
				swapChain.reset(sc);
				break;
			}
		}

		//if (FAILED(result)) return nullptr;

		ID3D11RenderTargetView* rtv = nullptr;
		ID3D11Texture2D* rtt = nullptr;
		ID3D11ShaderResourceView* rtsrv = nullptr;

		result = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&rtt);
		//if (FAILED(result)) return nullptr;
		renderTargetTexture.reset(rtt);

		result = device->CreateRenderTargetView(renderTargetTexture.get(), nullptr, &rtv);
		//if (FAILED(result)) return nullptr;
		renderTargetView.reset(rtv);

		result = device->CreateShaderResourceView(renderTargetTexture.get(), nullptr, &rtsrv);
		//if (FAILED(result)) return nullptr;
		renderTargetShaderResourceView.reset(rtsrv);
	}

	return *device.get();
}

ID3D11DeviceContext& Graphics::GetDeviceContext() {
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

		HRESULT result = {};

		ID3D11VertexShader* vs;
		ID3D11PixelShader* ps;
		ID3D11InputLayout* il;

		ID3DBlob *vertexShaderBlob = nullptr;
		result = CompileShader(L"shader.fx", "VS", "vs_4_0", &vertexShaderBlob);
		//if (FAILED(result)) return nullptr;
		result = device->CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), nullptr, &vs);
		//if (FAILED(result)) {
		//	vertexShaderBlob->Release();
		//	return nullptr;
		//}
		vertexShader.reset(vs);
		deviceContext->VSSetShader(vertexShader.get(), nullptr, 0);

		ID3DBlob *pixelShaderBlob = nullptr;
		result = CompileShader(L"shader.fx", "PS", "ps_4_0", &pixelShaderBlob);
		//if (FAILED(result)) return nullptr;
		result = device->CreatePixelShader(pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize(), nullptr, &ps);
		pixelShaderBlob->Release();
		//if (FAILED(result)) return nullptr;
		pixelShader.reset(ps);
		deviceContext->PSSetShader(pixelShader.get(), nullptr, 0);

		D3D11_INPUT_ELEMENT_DESC inputElementDesc[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		int inputElementDescCount = sizeof(inputElementDesc) / sizeof(inputElementDesc[0]);

		result = device->CreateInputLayout(inputElementDesc, inputElementDescCount, vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), &il);
		vertexShaderBlob->Release();
		//if (FAILED(result)) return nullptr;
		inputLayout.reset(il);
		deviceContext->IASetInputLayout(inputLayout.get());

		previosTime = GetTickCount() / 1000.0f;
	}

	return *deviceContext.get();
}

float Graphics::GetDeltaTime()
{
	return deltaTime;
}

bool Graphics::Update() {
	swapChain->Present(0, 0);

	if (!ProcessResponse()) {
		return false;
	}

	deviceContext->ClearRenderTargetView(renderTargetView.get(), color);

	deltaTime = (GetTickCount() / 1000.0f) - previosTime;
	previosTime = GetTickCount() / 1000.0f;

	return true;
}

bool Graphics::ProcessResponse() {
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

LRESULT WINAPI Graphics::ProcessWindow(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
	if (message == WM_DESTROY) {
		PostQuitMessage(0);
	}
	return DefWindowProc(window, message, wParam, lParam);
}

bool Graphics::CompileShader(WCHAR* filePath, char* entryPoint, char* shaderModel, ID3DBlob** out)
{
	HRESULT result = S_OK;

	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(_DEBUG)
	shaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob *errorBlob = nullptr;

	result = D3DCompileFromFile(filePath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint, shaderModel, shaderFlags, 0, out, &errorBlob);

	if (FAILED(result))
		if (errorBlob != nullptr)
			OutputDebugString((char*)errorBlob->GetBufferPointer());

	if (errorBlob)
		errorBlob->Release();

	return SUCCEEDED(result);
}
