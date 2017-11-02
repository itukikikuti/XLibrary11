#include <cstdio>
#include <windows.h>
#include <wincodec.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "Graphics.h"
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
using namespace std;
using namespace DirectX;

Graphics::Graphics() :
	frame(0),
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

	D3D11_INPUT_ELEMENT_DESC inputElementDesc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	int inputElementDescCount = sizeof(inputElementDesc) / sizeof(inputElementDesc[0]);

	result = device->CreateInputLayout(inputElementDesc, inputElementDescCount, vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), &inputLayout);
	vertexShaderBlob->Release();
	if (FAILED(result)) return;
	deviceContext->IASetInputLayout(inputLayout);

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

	XMFLOAT3 vertices[] = {
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(1.0f, 0.0f, 0.0f),
		XMFLOAT3(0.0f, -1.0f, 0.0f),
		XMFLOAT3(1.0f, -1.0f, 0.0f),
	};
	vertexCount = sizeof(vertices) / sizeof(vertices[0]);

	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(XMFLOAT3) * vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA vertexSubresourceData = {};
	vertexSubresourceData.pSysMem = vertices;
	result = device->CreateBuffer(&vertexBufferDesc, &vertexSubresourceData, &vertexBuffer);
	if (FAILED(result)) return;
	UINT stride = sizeof(XMFLOAT3);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	int index[] = {
		0, 1, 2,
		3, 2, 1,
	};
	indexCount = sizeof(index) / sizeof(index[0]);

	D3D11_BUFFER_DESC indexBufferDesc = {};
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(int) * indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA indexSubresourceData = {};
	indexSubresourceData.pSysMem = index;
	result = device->CreateBuffer(&indexBufferDesc, &indexSubresourceData, &indexBuffer);
	if (FAILED(result)) return;
	deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	D3D11_BUFFER_DESC constantBufferDesc = {};
	constantBufferDesc.ByteWidth = sizeof(ConstantBuffer);
	constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.CPUAccessFlags = 0;
	result = device->CreateBuffer(&constantBufferDesc, nullptr, &constantBuffer);
	if (FAILED(result)) return;
	deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);
	deviceContext->GSSetConstantBuffers(0, 1, &constantBuffer);
	deviceContext->PSSetConstantBuffers(0, 1, &constantBuffer);

	cbuffer.view = XMMatrixLookAtLH(XMVectorSet(CLIENT_WIDTH / 2.0f, -CLIENT_HEIGHT / 2.0f, 0.0f, 0.0f), XMVectorSet(CLIENT_WIDTH / 2.0f, -CLIENT_HEIGHT / 2.0f, 1.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
	cbuffer.projection = XMMatrixOrthographicLH(CLIENT_WIDTH, CLIENT_HEIGHT, -1.0f, 1.0f);
	XMStoreFloat3(&cbuffer.lightDirection, XMVector3Normalize(XMVectorSet(0.25f, -1.0f, 0.5f, 0.0f)));

	IWICImagingFactory *factory = nullptr;
	result = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&factory));
	if (FAILED(result)) return;

	IWICBitmapDecoder *decoder = nullptr;
	result = factory->CreateDecoderFromFilename(L"box.jpg", 0, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &decoder);
	if (FAILED(result)) return;

	IWICBitmapFrameDecode *frame = nullptr;
	result = decoder->GetFrame(0, &frame);
	if (FAILED(result)) return;

	UINT textureWidth, textureHeight;
	result = frame->GetSize(&textureWidth, &textureHeight);
	if (FAILED(result)) return;

	WICPixelFormatGUID pixelFormat;
	result = frame->GetPixelFormat(&pixelFormat);
	if (FAILED(result)) return;

	BYTE *textureBuffer = new BYTE[textureWidth * textureHeight * 4];

	if (pixelFormat != GUID_WICPixelFormat32bppRGBA) {
		IWICFormatConverter *formatConverter = nullptr;
		result = factory->CreateFormatConverter(&formatConverter);
		if (FAILED(result)) return;

		result = formatConverter->Initialize(frame, GUID_WICPixelFormat32bppRGBA, WICBitmapDitherTypeErrorDiffusion, 0, 0, WICBitmapPaletteTypeCustom);
		if (FAILED(result)) return;

		result = formatConverter->CopyPixels(0, textureWidth * 4, textureWidth * textureHeight * 4, textureBuffer);
		if (FAILED(result)) return;
	}
	else
	{
		result = frame->CopyPixels(0, textureWidth * 4, textureWidth * textureHeight * 4, textureBuffer);
		if (FAILED(result)) return;
	}

	D3D11_TEXTURE2D_DESC textureDesc = {};
	textureDesc.Width = textureWidth;
	textureDesc.Height = textureHeight;
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
	textureSubresourceData.SysMemPitch = textureWidth * 4;
	textureSubresourceData.SysMemSlicePitch = textureWidth * textureHeight * 4;

	result = device->CreateTexture2D(&textureDesc, &textureSubresourceData, &texture);
	if (FAILED(result)) return;

	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc = {};
	shaderResourceViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;

	result = device->CreateShaderResourceView(texture, &shaderResourceViewDesc, &shaderResourceView);
	if (FAILED(result)) return;

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

	result = device->CreateSamplerState(&samplerDesc, &samplerState);
	if (FAILED(result)) return;

	deviceContext->PSSetShaderResources(0, 1, &shaderResourceView);
	deviceContext->PSSetSamplers(0, 1, &samplerState);

	delete[] textureBuffer;
}

Graphics::~Graphics() {
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
	frame++;
	deviceContext->ClearRenderTargetView(renderTargetView, clearColor);

	cbuffer.world = XMMatrixScaling(256.0f, 256.0f, 256.0f);
	deviceContext->UpdateSubresource(constantBuffer, 0, nullptr, &cbuffer, 0, 0);
	deviceContext->DrawIndexed(indexCount, 0, 0);

	cbuffer.world = XMMatrixScaling(128.0f, 128.0f, 128.0f);
	deviceContext->UpdateSubresource(constantBuffer, 0, nullptr, &cbuffer, 0, 0);
	deviceContext->DrawIndexed(indexCount, 0, 0);

	swapChain->Present(0, 0);

	while (windowMessage.message != WM_QUIT) {
		if (PeekMessage(&windowMessage, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&windowMessage);
			DispatchMessage(&windowMessage);
		}
		else {
			return true;
		}
	}

	return false;
}

LRESULT __stdcall Graphics::WindowProcedure(HWND windowHandle, UINT windowMessage, WPARAM wParam, LPARAM lParam) {
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
