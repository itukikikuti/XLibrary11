#include <cstdio>
#include <windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "Graphics.h"
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
using namespace std;
using namespace DirectX;

Graphics& Graphics::GetInstance() {
	static Graphics instance;
	return instance;
}

Graphics::Graphics() :
	windowMessage({}),
	driverType(D3D_DRIVER_TYPE_NULL),
	featureLevel(D3D_FEATURE_LEVEL_11_0) {

	HINSTANCE instance = GetModuleHandle(nullptr);
	WNDCLASSEX windowClass = {};
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WindowProcedure;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = instance;
	windowClass.hIcon = LoadIcon(instance, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	windowClass.lpszMenuName = nullptr;
	windowClass.lpszClassName = TITLE;
	windowClass.hIconSm = LoadIcon(instance, IDI_APPLICATION);
	if (!RegisterClassEx(&windowClass)) return;

	window = CreateWindow(TITLE, TITLE, WINDOW_STYLE, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, nullptr, nullptr, instance, nullptr);
	if (window == nullptr) return;

	RECT windowRect = {};
	RECT clientRect = {};
	GetWindowRect(window, &windowRect);
	GetClientRect(window, &clientRect);
	int windowWidth = (windowRect.right - windowRect.left) - (clientRect.right - clientRect.left) + CLIENT_WIDTH;
	int windowHeight = (windowRect.bottom - windowRect.top) - (clientRect.bottom - clientRect.top) + CLIENT_HEIGHT;
	SetWindowPos(window, nullptr, 0, 0, windowWidth, windowHeight, SWP_NOMOVE | SWP_NOZORDER);

	ShowWindow(window, SW_SHOWNORMAL);

	clearColor[0] = 1.0f;
	clearColor[1] = 1.0f;
	clearColor[2] = 1.0f;
	clearColor[3] = 1.0f;

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
	swapChainDesc.BufferDesc.Width = CLIENT_WIDTH;
	swapChainDesc.BufferDesc.Height = CLIENT_HEIGHT;
	swapChainDesc.BufferDesc.Format = SWAP_CHAIN_FORMAT;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
	swapChainDesc.OutputWindow = window;
	swapChainDesc.SampleDesc.Count = MULTI_SAMPLE_COUNT;
	swapChainDesc.SampleDesc.Quality = MULTI_SAMPLE_QUALITY;
	swapChainDesc.Windowed = true;

	HRESULT result = {};

	for (int i = 0; i < driverTypeCount; i++) {
		driverType = driverTypes[i];
		result = D3D11CreateDeviceAndSwapChain(nullptr, driverType, nullptr, createDeviceFlag, featureLevels, featureLevelCount, D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device, &featureLevel, &deviceContext);
		if (SUCCEEDED(result)) break;
	}
	if (FAILED(result)) return;

	if (!CreateRenderTarget()) return;
	deviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr);

	D3D11_VIEWPORT viewPort;
	viewPort.Width = (float)CLIENT_WIDTH;
	viewPort.Height = (float)CLIENT_HEIGHT;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;
	deviceContext->RSSetViewports(1, &viewPort);

	ID3DBlob *vertexShaderBlob = nullptr;
	result = CompileShader(L"shader.fx", "VS", "vs_4_0", &vertexShaderBlob);
	if (FAILED(result)) return;
	result = device->CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), nullptr, &vertexShader);
	if (FAILED(result)) {
		vertexShaderBlob->Release();
		return;
	}
	deviceContext->VSSetShader(vertexShader, nullptr, 0);

	ID3DBlob *geometryShaderBlob = nullptr;
	result = CompileShader(L"shader.fx", "GS", "gs_4_0", &geometryShaderBlob);
	if (FAILED(result)) return;
	result = device->CreateGeometryShader(geometryShaderBlob->GetBufferPointer(), geometryShaderBlob->GetBufferSize(), nullptr, &geometryShader);
	geometryShaderBlob->Release();
	if (FAILED(result)) return;
	deviceContext->GSSetShader(geometryShader, nullptr, 0);

	ID3DBlob *pixelShaderBlob = nullptr;
	result = CompileShader(L"shader.fx", "PS", "ps_4_0", &pixelShaderBlob);
	if (FAILED(result)) return;
	result = device->CreatePixelShader(pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize(), nullptr, &pixelShader);
	pixelShaderBlob->Release();
	if (FAILED(result)) return;
	deviceContext->PSSetShader(pixelShader, nullptr, 0);

	D3D11_INPUT_ELEMENT_DESC inputElementDesc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	int inputElementDescCount = sizeof(inputElementDesc) / sizeof(inputElementDesc[0]);

	result = device->CreateInputLayout(inputElementDesc, inputElementDescCount, vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), &inputLayout);
	vertexShaderBlob->Release();
	if (FAILED(result)) return;
	deviceContext->IASetInputLayout(inputLayout);
}

Graphics::~Graphics() {
	if (vertexShader)
		vertexShader->Release();

	if (geometryShader)
		geometryShader->Release();

	if (pixelShader)
		pixelShader->Release();

	if (inputLayout)
		inputLayout->Release();

	if (deviceContext)
	{
		deviceContext->ClearState();
		deviceContext->Flush();
	}

	ReleaseRenderTarget();

	if (swapChain)
		swapChain->Release();

	if (deviceContext)
		deviceContext->Release();

	if (device)
		device->Release();

	UnregisterClass(TITLE, GetModuleHandle(nullptr));
}

bool Graphics::Render() {

	swapChain->Present(0, 0);

	while (windowMessage.message != WM_QUIT) {
		if (PeekMessage(&windowMessage, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&windowMessage);
			DispatchMessage(&windowMessage);
		}
		else {
			deviceContext->ClearRenderTargetView(renderTargetView, clearColor);
			return true;
		}
	}

	return false;
}

ID3D11Device& Graphics::GetDevice() {
	return *device;
}

ID3D11DeviceContext& Graphics::GetDeviceContext() {
	return *deviceContext;
}

LRESULT WINAPI Graphics::WindowProcedure(HWND windowHandle, UINT windowMessage, WPARAM wParam, LPARAM lParam) {
	if (windowMessage == WM_DESTROY) {
		PostQuitMessage(0);
	}
	return DefWindowProc(windowHandle, windowMessage, wParam, lParam);
}

bool Graphics::CreateRenderTarget()
{
	HRESULT result = S_OK;

	result = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&renderTargetTexture);
	if (FAILED(result)) return false;

	result = device->CreateRenderTargetView(renderTargetTexture, nullptr, &renderTargetView);
	if (FAILED(result)) return false;

	result = device->CreateShaderResourceView(renderTargetTexture, nullptr, &renderTargetShaderResourceView);
	if (FAILED(result)) return false;

	return true;
}

void Graphics::ReleaseRenderTarget()
{
	if (renderTargetShaderResourceView)
		renderTargetShaderResourceView->Release();

	if (renderTargetView)
		renderTargetView->Release();

	if (renderTargetTexture)
		renderTargetTexture->Release();
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
