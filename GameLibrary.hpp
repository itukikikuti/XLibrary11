namespace GameLibrary {
// © 2017 itukikikuti
#pragma once

#define OEMRESOURCE
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <strsafe.h>
#include <utility>
#include <vector>
#include <wincodec.h>
#include <windows.h>
#include <wrl.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#define Main() WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
#define PUBLIC public:
#define PRIVATE private:
#define PROTECTED protected:

class Float2 {
	PUBLIC float x;
	PUBLIC float y;

	PUBLIC Float2() : x(0.0f), y(0.0f) {
	}
	PUBLIC Float2(float x, float y) : x(x), y(y) {
	}
	PUBLIC Float2& operator=(const DirectX::XMFLOAT2& value) {
		x = value.x;
		y = value.y;
		return *this;
	}
	PUBLIC Float2& operator=(const Float2& value) {
		x = value.x;
		y = value.y;
		return *this;
	}
	PUBLIC Float2& operator=(const float& value) {
		x = value;
		y = value;
		return *this;
	}
	PUBLIC Float2& operator+=(const Float2& value) {
		x += value.x;
		y += value.y;
		return *this;
	}
	PUBLIC Float2& operator+=(const float& value) {
		x += value;
		y += value;
		return *this;
	}
	PUBLIC Float2& operator-=(const Float2& value) {
		x -= value.x;
		y -= value.y;
		return *this;
	}
	PUBLIC Float2& operator-=(const float& value) {
		x -= value;
		y -= value;
		return *this;
	}
	PUBLIC Float2& operator*=(const Float2& value) {
		x *= value.x;
		y *= value.y;
		return *this;
	}
	PUBLIC Float2& operator*=(const float& value) {
		x *= value;
		y *= value;
		return *this;
	}
	PUBLIC Float2& operator/=(const Float2& value) {
		x /= value.x;
		y /= value.y;
		return *this;
	}
	PUBLIC Float2& operator/=(const float& value) {
		x /= value;
		y /= value;
		return *this;
	}
};

Float2 operator+(const Float2& t1, const Float2& t2) {
	return Float2(t1) += t2;
}
Float2 operator+(const Float2& t1, const float& t2) {
	return Float2(t1) += t2;
}
Float2 operator-(const Float2& t1, const Float2& t2) {
	return Float2(t1) -= t2;
}
Float2 operator-(const Float2& t1, const float& t2) {
	return Float2(t1) -= t2;
}
Float2 operator*(const Float2& t1, const Float2& t2) {
	return Float2(t1) *= t2;
}
Float2 operator*(const Float2& t1, const float& t2) {
	return Float2(t1) *= t2;
}
Float2 operator/(const Float2& t1, const Float2& t2) {
	return Float2(t1) /= t2;
}
Float2 operator/(const Float2& t1, const float& t2) {
	return Float2(t1) /= t2;
}

class Float3 {
	PUBLIC float x;
	PUBLIC float y;
	PUBLIC float z;

	PUBLIC Float3() : x(0.0f), y(0.0f), z(0.0f) {
	}
	PUBLIC Float3(float x, float y, float z) : x(x), y(y), z(z) {
	}
	PUBLIC Float3& operator=(const DirectX::XMFLOAT3& value) {
		x = value.x;
		y = value.y;
		z = value.z;
		return *this;
	}
	PUBLIC Float3& operator=(const Float3& value) {
		x = value.x;
		y = value.y;
		z = value.z;
		return *this;
	}
	PUBLIC Float3& operator=(const float& value) {
		x = value;
		y = value;
		z = value;
		return *this;
	}
	PUBLIC Float3& operator+=(const Float3& value) {
		x += value.x;
		y += value.y;
		z += value.z;
		return *this;
	}
	PUBLIC Float3& operator+=(const float& value) {
		x += value;
		y += value;
		z += value;
		return *this;
	}
	PUBLIC Float3& operator-=(const Float3& value) {
		x -= value.x;
		y -= value.y;
		z -= value.z;
		return *this;
	}
	PUBLIC Float3& operator-=(const float& value) {
		x -= value;
		y -= value;
		z -= value;
		return *this;
	}
	PUBLIC Float3& operator*=(const Float3& value) {
		x *= value.x;
		y *= value.y;
		z *= value.z;
		return *this;
	}
	PUBLIC Float3& operator*=(const float& value) {
		x *= value;
		y *= value;
		z *= value;
		return *this;
	}
	PUBLIC Float3& operator/=(const Float3& value) {
		x /= value.x;
		y /= value.y;
		z /= value.z;
		return *this;
	}
	PUBLIC Float3& operator/=(const float& value) {
		x /= value;
		y /= value;
		z /= value;
		return *this;
	}
};

Float3 operator+(const Float3& t1, const Float3& t2) {
	return Float3(t1) += t2;
}
Float3 operator+(const Float3& t1, const float& t2) {
	return Float3(t1) += t2;
}
Float3 operator-(const Float3& t1, const Float3& t2) {
	return Float3(t1) -= t2;
}
Float3 operator-(const Float3& t1, const float& t2) {
	return Float3(t1) -= t2;
}
Float3 operator*(const Float3& t1, const Float3& t2) {
	return Float3(t1) *= t2;
}
Float3 operator*(const Float3& t1, const float& t2) {
	return Float3(t1) *= t2;
}
Float3 operator/(const Float3& t1, const Float3& t2) {
	return Float3(t1) /= t2;
}
Float3 operator/(const Float3& t1, const float& t2) {
	return Float3(t1) /= t2;
}

class Float4 {
	PUBLIC float x;
	PUBLIC float y;
	PUBLIC float z;
	PUBLIC float w;

	PUBLIC Float4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {
	}
	PUBLIC Float4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {
	}
	PUBLIC Float4& operator=(const DirectX::XMFLOAT4& value) {
		x = value.x;
		y = value.y;
		z = value.z;
		w = value.w;
		return *this;
	}
	PUBLIC Float4& operator=(const Float4& value) {
		x = value.x;
		y = value.y;
		z = value.z;
		w = value.w;
		return *this;
	}
	PUBLIC Float4& operator=(const float& value) {
		x = value;
		y = value;
		z = value;
		w = value;
		return *this;
	}
	PUBLIC Float4& operator+=(const Float4& value) {
		x += value.x;
		y += value.y;
		z += value.z;
		w += value.w;
		return *this;
	}
	PUBLIC Float4& operator+=(const float& value) {
		x += value;
		y += value;
		z += value;
		w += value;
		return *this;
	}
	PUBLIC Float4& operator-=(const Float4& value) {
		x -= value.x;
		y -= value.y;
		z -= value.z;
		w -= value.w;
		return *this;
	}
	PUBLIC Float4& operator-=(const float& value) {
		x -= value;
		y -= value;
		z -= value;
		w -= value;
		return *this;
	}
	PUBLIC Float4& operator*=(const Float4& value) {
		x *= value.x;
		y *= value.y;
		z *= value.z;
		w *= value.w;
		return *this;
	}
	PUBLIC Float4& operator*=(const float& value) {
		x *= value;
		y *= value;
		z *= value;
		w *= value;
		return *this;
	}
	PUBLIC Float4& operator/=(const Float4& value) {
		x /= value.x;
		y /= value.y;
		z /= value.z;
		w /= value.w;
		return *this;
	}
	PUBLIC Float4& operator/=(const float& value) {
		x /= value;
		y /= value;
		z /= value;
		w /= value;
		return *this;
	}
};

Float4 operator+(const Float4& t1, const Float4& t2) {
	return Float4(t1) += t2;
}
Float4 operator+(const Float4& t1, const float& t2) {
	return Float4(t1) += t2;
}
Float4 operator-(const Float4& t1, const Float4& t2) {
	return Float4(t1) -= t2;
}
Float4 operator-(const Float4& t1, const float& t2) {
	return Float4(t1) -= t2;
}
Float4 operator*(const Float4& t1, const Float4& t2) {
	return Float4(t1) *= t2;
}
Float4 operator*(const Float4& t1, const float& t2) {
	return Float4(t1) *= t2;
}
Float4 operator/(const Float4& t1, const Float4& t2) {
	return Float4(t1) /= t2;
}
Float4 operator/(const Float4& t1, const float& t2) {
	return Float4(t1) /= t2;
}

struct Vertex {
	Float3 position;
	Float3 normal;
	Float2 uv;

	Vertex(Float3 position, Float3 normal, Float2 uv) {
		this->position = position;
		this->normal = normal;
		this->uv = uv;
	}
};


class App {

class Window {
	PRIVATE HWND handle;
	PRIVATE const DWORD style = WS_OVERLAPPEDWINDOW;
	PRIVATE std::vector<UINT> messages;

	PUBLIC Window() {
		HINSTANCE instance = GetModuleHandleW(nullptr);

		WNDCLASSEXW windowClass = {};
		windowClass.cbSize = sizeof(WNDCLASSEXW);
		windowClass.style = CS_HREDRAW | CS_VREDRAW;
		windowClass.lpfnWndProc = Procedure;
		windowClass.cbClsExtra = 0;
		windowClass.cbWndExtra = 0;
		windowClass.hInstance = instance;
		windowClass.hIcon = nullptr;
		windowClass.hCursor = (HCURSOR)LoadImageW(nullptr, MAKEINTRESOURCEW(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
		windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		windowClass.lpszMenuName = nullptr;
		windowClass.lpszClassName = L"GameLibrary";
		windowClass.hIconSm = nullptr;
		RegisterClassExW(&windowClass);

		handle = CreateWindowW(L"GameLibrary", L"GameLibrary", style, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, nullptr, nullptr, instance, nullptr);

		SetSize(1280.0f, 720.0f);

		ShowWindow(handle, SW_SHOWNORMAL);

		SetWindowLongPtrW(handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	}
	PUBLIC ~Window() {
	}
	PUBLIC HWND GetHandle() {
		return handle;
	}
	PUBLIC std::vector<UINT>& GetMessages() {
		return messages;
	}
	PUBLIC Float2 GetSize() {
		RECT clientRect = {};
		GetClientRect(handle, &clientRect);

		return Float2(static_cast<float>(clientRect.right - clientRect.left), static_cast<float>(clientRect.bottom - clientRect.top));
	}
	PUBLIC void SetSize(float width, float height) {
		RECT windowRect = {};
		RECT clientRect = {};
		GetWindowRect(handle, &windowRect);
		GetClientRect(handle, &clientRect);

		int w = (windowRect.right - windowRect.left) - (clientRect.right - clientRect.left) + static_cast<int>(width);
		int h = (windowRect.bottom - windowRect.top) - (clientRect.bottom - clientRect.top) + static_cast<int>(height);

		int x = (GetSystemMetrics(SM_CXSCREEN) - w) / 2;
		int y = (GetSystemMetrics(SM_CYSCREEN) - h) / 2;

		SetWindowPos(handle, nullptr, x, y, w, h, SWP_FRAMECHANGED);
	}
	PUBLIC wchar_t* GetTitle() {
		wchar_t* title = nullptr;
		GetWindowTextW(handle, title, GetWindowTextLengthW(handle));
		return title;
	}
	PUBLIC void SetTitle(const wchar_t* title) {
		SetWindowTextW(handle, title);
	}
	PUBLIC void SetFullScreen(bool isFullscreen) {
		static Float2 size = GetSize();

		if (isFullscreen) {
			size = GetSize();
			int w = GetSystemMetrics(SM_CXSCREEN);
			int h = GetSystemMetrics(SM_CYSCREEN);
			SetWindowLongPtrW(handle, GWL_STYLE, WS_VISIBLE | WS_POPUP);
			SetWindowPos(handle, HWND_TOP, 0, 0, w, h, SWP_FRAMECHANGED);
		}
		else {
			SetWindowLongPtrW(handle, GWL_STYLE, WS_VISIBLE | style);
			SetWindowPos(handle, nullptr, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);
			SetSize(size.x, size.y);
		}
	}
	PUBLIC bool Update() {
		static MSG message = {};

		messages.clear();

		while (message.message != WM_QUIT) {
			if (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE)) {
				TranslateMessage(&message);
				DispatchMessageW(&message);
			}
			else {
				return true;
			}
		}

		return false;
	}
	PRIVATE LRESULT Proceed(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) {
		messages.push_back(message);

		switch (message) {
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProcW(handle, message, wParam, lParam);
		}
		return 0;
	}
	PRIVATE static LRESULT WINAPI Procedure(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) {
		Window* window = (Window*)(GetWindowLongPtrW(handle, GWLP_USERDATA));
		if (window) {
			return window->Proceed(handle, message, wParam, lParam);
		}
		return DefWindowProcW(handle, message, wParam, lParam);
	}
};

class Graphics {
	PRIVATE const int SWAP_CHAIN_COUNT = 2;
	PRIVATE const DXGI_FORMAT SWAP_CHAIN_FORMAT = DXGI_FORMAT_R8G8B8A8_UNORM;
	PRIVATE const int MULTI_SAMPLE_COUNT = 4;
	PRIVATE const int MULTI_SAMPLE_QUALITY = 0;

	PRIVATE Microsoft::WRL::ComPtr<ID3D11Device> device = nullptr;
	PRIVATE Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain = nullptr;
	PRIVATE Microsoft::WRL::ComPtr<ID3D11DeviceContext> context = nullptr;

	PUBLIC Graphics() {
		int flags = 0;
#if defined(DEBUG) || defined(_DEBUG)
		flags |= D3D11_CREATE_DEVICE_DEBUG;
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
		swapChainDesc.BufferDesc.Width = static_cast<UINT>(App::GetWindowSize().x);
		swapChainDesc.BufferDesc.Height = static_cast<UINT>(App::GetWindowSize().y);
		swapChainDesc.BufferDesc.Format = SWAP_CHAIN_FORMAT;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
		swapChainDesc.OutputWindow = App::GetWindowHandle();
		swapChainDesc.SampleDesc.Count = MULTI_SAMPLE_COUNT;
		swapChainDesc.SampleDesc.Quality = MULTI_SAMPLE_QUALITY;
		swapChainDesc.Windowed = true;

		for (int i = 0; i < driverTypeCount; i++) {
			HRESULT result = D3D11CreateDeviceAndSwapChain(nullptr, driverTypes[i], nullptr, flags, featureLevels, featureLevelCount, D3D11_SDK_VERSION, &swapChainDesc, swapChain.GetAddressOf(), device.GetAddressOf(), nullptr, context.GetAddressOf());

			if (SUCCEEDED(result)) {
				break;
			}
		}

		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		Microsoft::WRL::ComPtr<ID3D11BlendState> blendState = nullptr;
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
		device->CreateBlendState(&blendDesc, &blendState);
		context->OMSetBlendState(blendState.Get(), blendFactor, 0xffffffff);

		//Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerState = nullptr;
		//D3D11_RASTERIZER_DESC rasterizerDesc = {};
		//rasterizerDesc.FillMode = D3D11_FILL_SOLID;
		//rasterizerDesc.CullMode = D3D11_CULL_NONE;
		//device->CreateRasterizerState(&rasterizerDesc, &rasterizerState);
		//context->RSSetState(rasterizerState.Get());
	}
	PUBLIC ~Graphics() {
	}
	PUBLIC ID3D11Device& GetDevice() {
		return *device.Get();
	}
	PUBLIC IDXGISwapChain& GetMemory() {
		return *swapChain.Get();
	}
	PUBLIC ID3D11DeviceContext& GetContext() {
		return *context.Get();
	}
};

class Input {
	PRIVATE Float2 mousePosition;
	PRIVATE BYTE preKeyState[256];
	PRIVATE BYTE keyState[256];
	PRIVATE bool isShowCursor = true;

	PUBLIC Input() {
		Update();
	}
	PUBLIC ~Input() {
	}
	PUBLIC bool GetKey(int keyCode) {
		return keyState[keyCode] & 0x80;
	}
	PUBLIC bool GetKeyUp(int keyCode) {
		return !(keyState[keyCode] & 0x80) && (preKeyState[keyCode] & 0x80);
	}
	PUBLIC bool GetKeyDown(int keyCode) {
		return (keyState[keyCode] & 0x80) && !(preKeyState[keyCode] & 0x80);
	}
	PUBLIC Float2 GetMousePosition() {
		return mousePosition;
	}
	PUBLIC void SetMousePosition(float x, float y) {
		if (GetActiveWindow() != App::GetWindowHandle()) {
			return;
		}

		mousePosition.x = x;
		mousePosition.y = y;
		POINT point = { static_cast<int>(x), static_cast<int>(y) };
		ClientToScreen(App::GetWindowHandle(), &point);
		SetCursorPos(point.x, point.y);
	}
	PUBLIC void SetShowCursor(bool isShowCursor) {
		if (this->isShowCursor == isShowCursor) {
			return;
		}

		this->isShowCursor = isShowCursor;
		ShowCursor(isShowCursor);
	}
	PUBLIC void Update() {
		POINT point = {};
		GetCursorPos(&point);

		ScreenToClient(App::GetWindowHandle(), &point);
		mousePosition = Float2(static_cast<float>(point.x), static_cast<float>(point.y));

		for (int i = 0; i < 256; i++) {
			preKeyState[i] = keyState[i];
		}

		GetKeyboardState(keyState);
	}
};

class Timer {
	PRIVATE float time = 0.0f;
	PRIVATE float deltaTime = 0.0f;
	PRIVATE int frameRate = 0;
	PRIVATE float second = 0.0f;
	PRIVATE int frameCount = 0;
	LARGE_INTEGER preCount;
	LARGE_INTEGER frequency;

	PUBLIC Timer() {
		preCount = GetCounter();
		frequency = GetCountFrequency();
	}
	PUBLIC ~Timer() {
	}
	PUBLIC float GetTime() {
		return time;
	}
	PUBLIC float GetDeltaTime() {
		return deltaTime;
	}
	PUBLIC int GetFrameRate() {
		return frameRate;
	}
	PUBLIC void Update() {

		LARGE_INTEGER count = GetCounter();
		deltaTime = (float)(count.QuadPart - preCount.QuadPart) / frequency.QuadPart;
		preCount = GetCounter();

		time += deltaTime;


		frameCount++;
		second += deltaTime;
		if (second >= 1.0f) {
			frameRate = frameCount;
			frameCount = 0;
			second -= 1.0f;
		}
	}
	PRIVATE LARGE_INTEGER GetCounter() {
		LARGE_INTEGER counter;
		QueryPerformanceCounter(&counter);
		return counter;
	}
	PRIVATE LARGE_INTEGER GetCountFrequency() {
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		return frequency;
	}
};


	PUBLIC App() = delete;
	PUBLIC static HWND GetWindowHandle() {
		return GetWindow().GetHandle();
	}
	PUBLIC static std::vector<UINT>& GetWindowMessages() {
		return GetWindow().GetMessages();
	}
	PUBLIC static Float2 GetWindowSize() {
		return GetWindow().GetSize();
	}
	PUBLIC static void SetWindowSize(float width, float height) {
		GetWindow().SetSize(width, height);
	}
	PUBLIC static wchar_t* GetTitle() {
		return GetWindow().GetTitle();
	}
	PUBLIC static void SetTitle(const wchar_t* title) {
		GetWindow().SetTitle(title);
	}
	PUBLIC static void SetFullScreen(bool isFullscreen) {
		GetWindow().SetFullScreen(isFullscreen);
	}
	PUBLIC static ID3D11Device& GetGraphicsDevice() {
		return GetGraphics().GetDevice();
	}
	PUBLIC static ID3D11DeviceContext& GetGraphicsContext() {
		return GetGraphics().GetContext();
	}
	PUBLIC static IDXGISwapChain& GetGraphicsMemory() {
		return GetGraphics().GetMemory();
	}
	PUBLIC static bool GetKey(int VK_CODE) {
		return GetInput().GetKey(VK_CODE);
	}
	PUBLIC static bool GetKeyUp(int VK_CODE) {
		return GetInput().GetKeyUp(VK_CODE);
	}
	PUBLIC static bool GetKeyDown(int VK_CODE) {
		return GetInput().GetKeyDown(VK_CODE);
	}
	PUBLIC static Float2 GetMousePosition() {
		return GetInput().GetMousePosition();
	}
	PUBLIC static void SetMousePosition(Float2 position) {
		GetInput().SetMousePosition(position.x, position.y);
	}
	PUBLIC static void SetMousePosition(float x, float y) {
		GetInput().SetMousePosition(x, y);
	}
	PUBLIC static void SetShowCursor(bool isShowCursor) {
		GetInput().SetShowCursor(isShowCursor);
	}
	PUBLIC static float GetTime() {
		return GetTimer().GetTime();
	}
	PUBLIC static float GetDeltaTime() {
		return GetTimer().GetDeltaTime();
	}
	PUBLIC static int GetFrameRate() {
		return GetTimer().GetFrameRate();
	}
	PUBLIC static void AddFont(const wchar_t* filePath) {
		AddFontResourceExW(filePath, FR_PRIVATE, nullptr);
	}
	PUBLIC static bool Refresh() {
		GetGraphicsMemory().Present(1, 0);

		if (!GetWindow().Update()) return false;
		GetInput().Update();
		GetTimer().Update();

		return true;
	}
	PRIVATE static Window& GetWindow() {
		static std::unique_ptr<Window> window(new Window());
		return *window.get();
	}
	PRIVATE static Graphics& GetGraphics() {
		static std::unique_ptr<Graphics> graphics(new Graphics());
		return *graphics.get();
	}
	PRIVATE static Input& GetInput() {
		static std::unique_ptr<Input> input(new Input());
		return *input.get();
	}
	PRIVATE static Timer& GetTimer() {
		static std::unique_ptr<Timer> timer(new Timer());
		return *timer.get();
	}
};

class Texture {
	PROTECTED int width;
	PROTECTED int height;
	PROTECTED Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
	PROTECTED Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView;
	PROTECTED Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState;

	PUBLIC Texture(wchar_t* filePath) {
		Load(filePath);
	}
	PUBLIC Texture(int width, int height, BYTE* buffer) {
		this->width = width;
		this->height = height;
		Setup(buffer);
	}
	PUBLIC virtual ~Texture() {
	}
	PUBLIC void Load(wchar_t* filePath) {
		CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);

		Microsoft::WRL::ComPtr<IWICImagingFactory> factory = nullptr;
		CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(factory.GetAddressOf()));

		Microsoft::WRL::ComPtr<IWICBitmapDecoder> decoder = nullptr;

		factory->CreateDecoderFromFilename(filePath, 0, GENERIC_READ, WICDecodeMetadataCacheOnDemand, decoder.GetAddressOf());
		Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> frame = nullptr;
		decoder->GetFrame(0, frame.GetAddressOf());
		UINT width, height;
		frame->GetSize(&width, &height);
		this->width = static_cast<UINT>(width);
		this->height = static_cast<UINT>(height);

		WICPixelFormatGUID pixelFormat;
		frame->GetPixelFormat(&pixelFormat);
		BYTE* buffer = new BYTE[width * height * 4];

		if (pixelFormat != GUID_WICPixelFormat32bppRGBA) {
			Microsoft::WRL::ComPtr<IWICFormatConverter> formatConverter = nullptr;
			factory->CreateFormatConverter(formatConverter.GetAddressOf());

			formatConverter->Initialize(frame.Get(), GUID_WICPixelFormat32bppRGBA, WICBitmapDitherTypeErrorDiffusion, 0, 0, WICBitmapPaletteTypeCustom);

			formatConverter->CopyPixels(0, width * 4, width * height * 4, buffer);
		}
		else {
			frame->CopyPixels(0, width * 4, width * height * 4, buffer);
		}

		Setup(buffer);

		delete[] buffer;
	}
	PUBLIC Float2 GetSize() {
		return Float2(static_cast<float>(width), static_cast<float>(height));
	}
	PUBLIC virtual void Attach(int slot) {
		App::GetGraphicsContext().PSSetShaderResources(slot, 1, shaderResourceView.GetAddressOf());
		App::GetGraphicsContext().PSSetSamplers(slot, 1, samplerState.GetAddressOf());
	}
	PROTECTED void Setup(BYTE* buffer) {
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
		textureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		textureDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA textureSubresourceData = {};
		textureSubresourceData.pSysMem = buffer;
		textureSubresourceData.SysMemPitch = width * 4;
		textureSubresourceData.SysMemSlicePitch = width * height * 4;
		App::GetGraphicsDevice().CreateTexture2D(&textureDesc, &textureSubresourceData, texture.GetAddressOf());

		D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc = {};
		shaderResourceViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		shaderResourceViewDesc.Texture2D.MipLevels = 1;
		App::GetGraphicsDevice().CreateShaderResourceView(texture.Get(), &shaderResourceViewDesc, shaderResourceView.GetAddressOf());

		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.MipLODBias = 0.0f;
		samplerDesc.MaxAnisotropy = 1;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		samplerDesc.BorderColor[0] = 0.0f;
		samplerDesc.BorderColor[1] = 0.0f;
		samplerDesc.BorderColor[2] = 0.0f;
		samplerDesc.BorderColor[3] = 0.0f;
		samplerDesc.MinLOD = 0.0f;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
		App::GetGraphicsDevice().CreateSamplerState(&samplerDesc, samplerState.GetAddressOf());
	}
};

class Material {
	PUBLIC void* cbuffer = nullptr;
	PUBLIC Texture* textures[10];
	PROTECTED Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader = nullptr;
	PROTECTED Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader = nullptr;
	PROTECTED Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout = nullptr;
	PROTECTED Microsoft::WRL::ComPtr<ID3D11Buffer> constantBuffer = nullptr;

	PUBLIC Material() {
		char* source =
			"cbuffer Object : register(b0) {"
			"    matrix _world;"
			"};"
			"cbuffer Camera : register(b1) {"
			"    matrix _view;"
			"    matrix _projection;"
			"};"
			"float4 VS(float4 vertex : POSITION) : SV_POSITION {"
			"    float4 output = vertex;"
			"    output = mul(_world, output);"
			"    output = mul(_view, output);"
			"    output = mul(_projection, output);"
			"    return output;"
			"}"
			"float4 PS(float4 position : SV_POSITION) : SV_TARGET {"
			"    return float4(1, 0, 1, 1);"
			"}";

		Setup(source);
	}
	PUBLIC Material(char* source) {
		Setup(source);
	}
	PUBLIC Material(wchar_t* filePath) {
		Load(filePath);
	}
	PUBLIC virtual ~Material() {
	}
	PUBLIC void Load(wchar_t* filePath) {
		std::ifstream sourceFile(filePath);
		std::istreambuf_iterator<char> iterator(sourceFile);
		std::istreambuf_iterator<char> last;
		std::string source(iterator, last);
		sourceFile.close();

		Setup(source.c_str());
	}
	PUBLIC virtual void Attach() {
		App::GetGraphicsContext().VSSetShader(vertexShader.Get(), nullptr, 0);
		App::GetGraphicsContext().PSSetShader(pixelShader.Get(), nullptr, 0);
		App::GetGraphicsContext().IASetInputLayout(inputLayout.Get());

		if (cbuffer != nullptr) {
			App::GetGraphicsContext().UpdateSubresource(constantBuffer.Get(), 0, nullptr, cbuffer, 0, 0);
			App::GetGraphicsContext().VSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());
			App::GetGraphicsContext().HSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());
			App::GetGraphicsContext().DSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());
			App::GetGraphicsContext().GSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());
			App::GetGraphicsContext().PSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());
		}

		int i = 0;
		for (Texture* texture : textures) {
			if (texture != nullptr) {
				texture->Attach(i);
			}
			i++;
		}
	}
	PUBLIC void SetCBuffer(void* cbuffer, size_t size) {
		this->cbuffer = cbuffer;

		D3D11_BUFFER_DESC constantBufferDesc = {};
		constantBufferDesc.ByteWidth = static_cast<UINT>(size);
		constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constantBufferDesc.CPUAccessFlags = 0;
		App::GetGraphicsDevice().CreateBuffer(&constantBufferDesc, nullptr, constantBuffer.GetAddressOf());
	}
	PUBLIC void SetTexture(int slot, Texture* texture) {
		textures[slot] = texture;
	}
	PROTECTED void Setup(const char* source) {
		Microsoft::WRL::ComPtr<ID3DBlob> vertexShaderBlob = nullptr;
		CompileShader(source, "VS", "vs_5_0", vertexShaderBlob.GetAddressOf());
		App::GetGraphicsDevice().CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), nullptr, vertexShader.GetAddressOf());

		Microsoft::WRL::ComPtr<ID3DBlob> pixelShaderBlob = nullptr;
		CompileShader(source, "PS", "ps_5_0", pixelShaderBlob.GetAddressOf());
		App::GetGraphicsDevice().CreatePixelShader(pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize(), nullptr, pixelShader.GetAddressOf());

		std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDesc;
		inputElementDesc.push_back({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		inputElementDesc.push_back({ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		inputElementDesc.push_back({ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 });

		App::GetGraphicsDevice().CreateInputLayout(&inputElementDesc[0], static_cast<UINT>(inputElementDesc.size()), vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), inputLayout.GetAddressOf());
	}
	PROTECTED static void CompileShader(const char* source, const char* entryPoint, const char* shaderModel, ID3DBlob** out) {
		DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(DEBUG) || defined(_DEBUG)
		shaderFlags |= D3DCOMPILE_DEBUG;
#endif

		Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;
		D3DCompile(source, strlen(source), nullptr, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint, shaderModel, shaderFlags, 0, out, &errorBlob);

		if (errorBlob != nullptr) {
			OutputDebugStringA((char*)errorBlob->GetBufferPointer());
			MessageBoxA(App::GetWindowHandle(), (char*)errorBlob->GetBufferPointer(), "Shader Error", MB_OK);
		}
	}
};

class Camera {
	PROTECTED struct Constant {
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
	};

	PUBLIC Float3 position;
	PUBLIC Float3 angles;
	PROTECTED float fieldOfView;
	PROTECTED float nearClip;
	PROTECTED float farClip;
	PROTECTED Constant constant;
	PROTECTED Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTarget = nullptr;
	PROTECTED Microsoft::WRL::ComPtr<ID3D11Texture2D> texture = nullptr;
	PROTECTED Microsoft::WRL::ComPtr<ID3D11Buffer> constantBuffer = nullptr;

	PUBLIC Camera() {
		Initialize();
		Setup();
	}
	PUBLIC virtual ~Camera() {
	}
	PUBLIC void SetPerspective(float fieldOfView, float nearClip, float farClip) {
		this->fieldOfView = fieldOfView;
		this->nearClip = nearClip;
		this->farClip = farClip;
		constant.projection = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(fieldOfView), App::GetWindowSize().x / (float)App::GetWindowSize().y, nearClip, farClip);
	}
	PUBLIC virtual void Update() {
		TryResize();

		constant.view =
			DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(angles.z)) *
			DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(angles.y)) *
			DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(angles.x)) *
			DirectX::XMMatrixTranslation(position.x, position.y, position.z);
		constant.view = DirectX::XMMatrixInverse(nullptr, constant.view);

		App::GetGraphicsContext().UpdateSubresource(constantBuffer.Get(), 0, nullptr, &constant, 0, 0);
		App::GetGraphicsContext().VSSetConstantBuffers(1, 1, constantBuffer.GetAddressOf());
		App::GetGraphicsContext().HSSetConstantBuffers(1, 1, constantBuffer.GetAddressOf());
		App::GetGraphicsContext().DSSetConstantBuffers(1, 1, constantBuffer.GetAddressOf());
		App::GetGraphicsContext().GSSetConstantBuffers(1, 1, constantBuffer.GetAddressOf());
		App::GetGraphicsContext().PSSetConstantBuffers(1, 1, constantBuffer.GetAddressOf());

		App::GetGraphicsContext().OMSetRenderTargets(1, renderTarget.GetAddressOf(), nullptr);

		static float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		App::GetGraphicsContext().ClearRenderTargetView(renderTarget.Get(), color);
	}
	PROTECTED void Initialize() {
		position = Float3(0.0f, 0.0f, -5.0f);
		angles = Float3(0.0f, 0.0f, 0.0f);

		SetPerspective(60.0f, 0.1f, 1000.0f);
	}
	PROTECTED void Setup() {
		App::GetGraphicsMemory().GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(texture.GetAddressOf()));
		App::GetGraphicsDevice().CreateRenderTargetView(texture.Get(), nullptr, renderTarget.GetAddressOf());

		D3D11_VIEWPORT viewPort = {};
		viewPort.Width = (float)App::GetWindowSize().x;
		viewPort.Height = (float)App::GetWindowSize().y;
		viewPort.MinDepth = 0.0f;
		viewPort.MaxDepth = 1.0f;
		viewPort.TopLeftX = 0;
		viewPort.TopLeftY = 0;
		App::GetGraphicsContext().RSSetViewports(1, &viewPort);

		D3D11_BUFFER_DESC constantBufferDesc = {};
		constantBufferDesc.ByteWidth = static_cast<UINT>(sizeof(Constant));
		constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constantBufferDesc.CPUAccessFlags = 0;
		App::GetGraphicsDevice().CreateBuffer(&constantBufferDesc, nullptr, constantBuffer.GetAddressOf());
	}
	PROTECTED void TryResize() {
		for (UINT message : App::GetWindowMessages()) {
			if (message != WM_SIZE) {
				continue;
			}
			if (App::GetWindowSize().x <= 0.0f || App::GetWindowSize().y <= 0.0f) {
				continue;
			}

			Microsoft::WRL::ComPtr<ID3D11RenderTargetView> nullRenderTarget = nullptr;
			App::GetGraphicsContext().OMSetRenderTargets(1, nullRenderTarget.GetAddressOf(), nullptr);
			renderTarget.Reset();
			texture.Reset();
			App::GetGraphicsContext().Flush();
			App::GetGraphicsMemory().ResizeBuffers(2, static_cast<UINT>(App::GetWindowSize().x), static_cast<UINT>(App::GetWindowSize().y), DXGI_FORMAT_R8G8B8A8_UNORM, 0);

			SetPerspective(fieldOfView, nearClip, farClip);
			Setup();
			return;
		}
	}
};

class Mesh {
	PROTECTED struct Constant {
		DirectX::XMMATRIX world;
		Float3 lightDirection;
	};

	PUBLIC Float3 position;
	PUBLIC Float3 angles;
	PUBLIC Float3 scale;
	PUBLIC std::vector<Vertex> vertices;
	PUBLIC std::vector<int> indices;
	PUBLIC Material material;
	PROTECTED Constant constant;
	PROTECTED Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer = nullptr;
	PROTECTED Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer = nullptr;

	PUBLIC Mesh() :
		material(
			"cbuffer Object : register(b0) {"
			"    matrix _world;"
			"    float3 _lightDirection;"
			"};"
			"cbuffer Camera : register(b1) {"
			"    matrix _view;"
			"    matrix _projection;"
			"};"
			"Texture2D tex : register(t0);"
			"SamplerState samp: register(s0);"
			"struct VSOutput {"
			"    float4 position : SV_POSITION;"
			"    float4 normal : NORMAL;"
			"    float2 uv : TEXCOORD;"
			"};"
			"VSOutput VS(float3 vertex : POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD) {"
			"    VSOutput output = (VSOutput)0;"
			"    output.position = mul(_world, float4(vertex, 1.0));"
			"    output.position = mul(_view, output.position);"
			"    output.position = mul(_projection, output.position);"
			"    output.normal = normalize(mul(_world, float4(normal, 1)));"
			"    output.uv = uv;"
			"    return output;"
			"}"
			"float4 PS(VSOutput pixel) : SV_TARGET {"
			"    float diffuse = dot(-_lightDirection, pixel.normal.xyz);"
			"    return max(0, float4(tex.Sample(samp, pixel.uv).rgb * diffuse, 1));"
			"}") {
		Initialize();
		CreateCube();
		Setup();
	}
	PUBLIC virtual ~Mesh() {
	}
	PUBLIC void CreateQuad(bool shouldClear = true) {
		if (shouldClear) {
			vertices.clear();
			indices.clear();
		}

		vertices.push_back(Vertex(Float3(-0.5f, 0.5f, 0.0f), Float3(0.0f, 0.0f, -1.0f), Float2(0.0f, 0.0f)));
		vertices.push_back(Vertex(Float3(0.5f, 0.5f, 0.0f), Float3(0.0f, 0.0f, -1.0f), Float2(1.0f, 0.0f)));
		vertices.push_back(Vertex(Float3(-0.5f, -0.5f, 0.0f), Float3(0.0f, 0.0f, -1.0f), Float2(0.0f, 1.0f)));
		vertices.push_back(Vertex(Float3(0.5f, -0.5f, 0.0f), Float3(0.0f, 0.0f, -1.0f), Float2(1.0f, 1.0f)));

		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);
		indices.push_back(3);
		indices.push_back(2);
		indices.push_back(1);
	}
	PUBLIC void CreateCube(bool shouldClear = true) {
		if (shouldClear) {
			vertices.clear();
			indices.clear();
		}

		vertices.push_back(Vertex(Float3(-0.5f, 0.5f, -0.5f), Float3(0.0f, 0.0f, -1.0f), Float2(0.0f, 0.0f)));
		vertices.push_back(Vertex(Float3(0.5f, 0.5f, -0.5f), Float3(0.0f, 0.0f, -1.0f), Float2(1.0f, 0.0f)));
		vertices.push_back(Vertex(Float3(-0.5f, -0.5f, -0.5f), Float3(0.0f, 0.0f, -1.0f), Float2(0.0f, 1.0f)));
		vertices.push_back(Vertex(Float3(0.5f, -0.5f, -0.5f), Float3(0.0f, 0.0f, -1.0f), Float2(1.0f, 1.0f)));

		vertices.push_back(Vertex(Float3(0.5f, 0.5f, -0.5f), Float3(1.0f, 0.0f, 0.0f), Float2(0.0f, 0.0f)));
		vertices.push_back(Vertex(Float3(0.5f, 0.5f, 0.5f), Float3(1.0f, 0.0f, 0.0f), Float2(1.0f, 0.0f)));
		vertices.push_back(Vertex(Float3(0.5f, -0.5f, -0.5f), Float3(1.0f, 0.0f, 0.0f), Float2(0.0f, 1.0f)));
		vertices.push_back(Vertex(Float3(0.5f, -0.5f, 0.5f), Float3(1.0f, 0.0f, 0.0f), Float2(1.0f, 1.0f)));
		
		vertices.push_back(Vertex(Float3(0.5f, 0.5f, 0.5f), Float3(0.0f, 0.0f, 1.0f), Float2(0.0f, 0.0f)));
		vertices.push_back(Vertex(Float3(-0.5f, 0.5f, 0.5f), Float3(0.0f, 0.0f, 1.0f), Float2(1.0f, 0.0f)));
		vertices.push_back(Vertex(Float3(0.5f, -0.5f, 0.5f), Float3(0.0f, 0.0f, 1.0f), Float2(0.0f, 1.0f)));
		vertices.push_back(Vertex(Float3(-0.5f, -0.5f, 0.5f), Float3(0.0f, 0.0f, 1.0f), Float2(1.0f, 1.0f)));
		
		vertices.push_back(Vertex(Float3(-0.5f, 0.5f, 0.5f), Float3(-1.0f, 0.0f, 0.0f), Float2(0.0f, 0.0f)));
		vertices.push_back(Vertex(Float3(-0.5f, 0.5f, -0.5f), Float3(-1.0f, 0.0f, 0.0f), Float2(1.0f, 0.0f)));
		vertices.push_back(Vertex(Float3(-0.5f, -0.5f, 0.5f), Float3(-1.0f, 0.0f, 0.0f), Float2(0.0f, 1.0f)));
		vertices.push_back(Vertex(Float3(-0.5f, -0.5f, -0.5f), Float3(-1.0f, 0.0f, 0.0f), Float2(1.0f, 1.0f)));
		
		vertices.push_back(Vertex(Float3(-0.5f, 0.5f, 0.5f), Float3(0.0f, 1.0f, 0.0f), Float2(0.0f, 0.0f)));
		vertices.push_back(Vertex(Float3(0.5f, 0.5f, 0.5f), Float3(0.0f, 1.0f, 0.0f), Float2(1.0f, 0.0f)));
		vertices.push_back(Vertex(Float3(-0.5f, 0.5f, -0.5f), Float3(0.0f, 1.0f, 0.0f), Float2(0.0f, 1.0f)));
		vertices.push_back(Vertex(Float3(0.5f, 0.5f, -0.5f), Float3(0.0f, 1.0f, 0.0f), Float2(1.0f, 1.0f)));
		
		vertices.push_back(Vertex(Float3(-0.5f, -0.5f, -0.5f), Float3(0.0f, -1.0f, 0.0f), Float2(0.0f, 0.0f)));
		vertices.push_back(Vertex(Float3(0.5f, -0.5f, -0.5f), Float3(0.0f, -1.0f, 0.0f), Float2(1.0f, 0.0f)));
		vertices.push_back(Vertex(Float3(-0.5f, -0.5f, 0.5f), Float3(0.0f, -1.0f, 0.0f), Float2(0.0f, 1.0f)));
		vertices.push_back(Vertex(Float3(0.5f, -0.5f, 0.5f), Float3(0.0f, -1.0f, 0.0f), Float2(1.0f, 1.0f)));

		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);
		indices.push_back(3);
		indices.push_back(2);
		indices.push_back(1);

		indices.push_back(4);
		indices.push_back(5);
		indices.push_back(6);
		indices.push_back(7);
		indices.push_back(6);
		indices.push_back(5);

		indices.push_back(8);
		indices.push_back(9);
		indices.push_back(10);
		indices.push_back(11);
		indices.push_back(10);
		indices.push_back(9);

		indices.push_back(12);
		indices.push_back(13);
		indices.push_back(14);
		indices.push_back(15);
		indices.push_back(14);
		indices.push_back(13);

		indices.push_back(16);
		indices.push_back(17);
		indices.push_back(18);
		indices.push_back(19);
		indices.push_back(18);
		indices.push_back(17);

		indices.push_back(20);
		indices.push_back(21);
		indices.push_back(22);
		indices.push_back(23);
		indices.push_back(22);
		indices.push_back(21);
	}
	PUBLIC void Apply() {
		Setup();
	}
	PUBLIC virtual void Draw() {
		material.Attach();

		constant.world =
			DirectX::XMMatrixScaling(scale.x, scale.y, scale.z) *
			DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(angles.z)) *
			DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(angles.y)) *
			DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(angles.x)) *
			DirectX::XMMatrixTranslation(position.x, position.y, position.z);
		DirectX::XMFLOAT3 lightDirection;
		DirectX::XMStoreFloat3(&lightDirection, DirectX::XMVector3Normalize(DirectX::XMVectorSet(0.25f, -1.0f, 0.5f, 0.0f)));
		constant.lightDirection = lightDirection;

		UINT stride = static_cast<UINT>(sizeof(Vertex));
		UINT offset = 0;
		App::GetGraphicsContext().IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);

		App::GetGraphicsContext().IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

		App::GetGraphicsContext().DrawIndexed(static_cast<UINT>(indices.size()), 0, 0);
	}
	PROTECTED void Initialize() {
		position = Float3(0.0f, 0.0f, 0.0f);
		angles = Float3(0.0f, 0.0f, 0.0f);
		scale = Float3(1.0f, 1.0f, 1.0f);
	}
	PROTECTED void Setup() {
		D3D11_BUFFER_DESC vertexBufferDesc = {};
		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.ByteWidth = static_cast<UINT>(sizeof(Vertex) * vertices.size());
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = 0;
		D3D11_SUBRESOURCE_DATA vertexSubresourceData = {};
		vertexSubresourceData.pSysMem = &vertices[0];
		App::GetGraphicsDevice().CreateBuffer(&vertexBufferDesc, &vertexSubresourceData, vertexBuffer.GetAddressOf());

		D3D11_BUFFER_DESC indexBufferDesc = {};
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = static_cast<UINT>(sizeof(int) * indices.size());
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		D3D11_SUBRESOURCE_DATA indexSubresourceData = {};
		indexSubresourceData.pSysMem = &indices[0];
		App::GetGraphicsDevice().CreateBuffer(&indexBufferDesc, &indexSubresourceData, indexBuffer.GetAddressOf());

		material.SetCBuffer(&constant, sizeof(Constant));
	}
};

class Sprite {
	PROTECTED struct ConstantBuffer {
		DirectX::XMMATRIX world;
		Float4 color;
	};

	PUBLIC Float3 position;
	PUBLIC Float3 angles;
	PUBLIC Float3 scale;
	PUBLIC Float4 color;
	PROTECTED UINT width;
	PROTECTED UINT height;
	PROTECTED Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
	PROTECTED ConstantBuffer cbuffer;
	PRIVATE int indexCount;
	PRIVATE Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
	PRIVATE Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer;
	PRIVATE Microsoft::WRL::ComPtr<ID3D11Buffer> constantBuffer;
	PRIVATE Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView;
	PRIVATE Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState;

	PUBLIC Sprite() {
		Initialize();
	}
	PUBLIC Sprite(const wchar_t* filePath) {
		CoInitializeEx(nullptr, COINIT_MULTITHREADED);

		Microsoft::WRL::ComPtr<IWICImagingFactory> factory = nullptr;
		CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(factory.GetAddressOf()));

		Microsoft::WRL::ComPtr<IWICBitmapDecoder> decoder = nullptr;
		BYTE* textureBuffer = nullptr;

		if (SUCCEEDED(factory->CreateDecoderFromFilename(filePath, 0, GENERIC_READ, WICDecodeMetadataCacheOnDemand, decoder.GetAddressOf()))) {
			Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> frame = nullptr;
			decoder->GetFrame(0, frame.GetAddressOf());
			frame->GetSize(&width, &height);

			WICPixelFormatGUID pixelFormat;
			frame->GetPixelFormat(&pixelFormat);
			textureBuffer = new BYTE[width * height * 4];

			if (pixelFormat != GUID_WICPixelFormat32bppRGBA) {
				Microsoft::WRL::ComPtr<IWICFormatConverter> formatConverter = nullptr;
				factory->CreateFormatConverter(formatConverter.GetAddressOf());

				formatConverter->Initialize(frame.Get(), GUID_WICPixelFormat32bppRGBA, WICBitmapDitherTypeErrorDiffusion, 0, 0, WICBitmapPaletteTypeCustom);

				formatConverter->CopyPixels(0, width * 4, width * height * 4, textureBuffer);
			}
			else {
				frame->CopyPixels(0, width * 4, width * height * 4, textureBuffer);
			}
		}
		else {
			width = height = 100;
			textureBuffer = new BYTE[width * height * 4];
			for (UINT y = 0; y < height; y++) {
				for (UINT x = 0; x < width; x++) {
					BYTE color[4] = { 0xff, 0x00, 0xff, 0xff };
					memcpy(&textureBuffer[x * 4 + y * (width * 4)], color, sizeof(DWORD));
				}
			}
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
		textureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		textureDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA textureSubresourceData;
		textureSubresourceData.pSysMem = textureBuffer;
		textureSubresourceData.SysMemPitch = width * 4;
		textureSubresourceData.SysMemSlicePitch = width * height * 4;
		App::GetGraphicsDevice().CreateTexture2D(&textureDesc, &textureSubresourceData, texture.GetAddressOf());

		delete[] textureBuffer;

		Initialize();
	}
	PUBLIC virtual ~Sprite() {
	}
	PUBLIC DirectX::XMINT2 GetSize() {
		return DirectX::XMINT2(width, height);
	}
	PUBLIC void Draw() {
		cbuffer.world = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z) * DirectX::XMMatrixRotationRollPitchYaw(DirectX::XMConvertToRadians(angles.x), DirectX::XMConvertToRadians(angles.y), DirectX::XMConvertToRadians(angles.z))* DirectX::XMMatrixTranslation(position.x, position.y, position.z);
		cbuffer.color = color;
		App::GetGraphicsContext().UpdateSubresource(constantBuffer.Get(), 0, nullptr, &cbuffer, 0, 0);
		App::GetGraphicsContext().VSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());
		App::GetGraphicsContext().PSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());

		App::GetGraphicsContext().PSSetShaderResources(0, 1, shaderResourceView.GetAddressOf());
		App::GetGraphicsContext().PSSetSamplers(0, 1, samplerState.GetAddressOf());

		App::GetGraphicsContext().DrawIndexed(indexCount, 0, 0);
	}
	PROTECTED void Initialize() {
		position = Float3(0.0f, 0.0f, 0.0f);
		angles = Float3(0.0f, 0.0f, 0.0f);
		scale = Float3(1.0f, 1.0f, 1.0f);
		color = Float4(1.0f, 1.0f, 1.0f, 1.0f);

		Vertex quad[] = {
			{ Float3(-0.5f, 0.5f, 0.0f), Float3(0.0f, 0.0f, -1.0f), Float2(0.0f, 0.0f) },
			{ Float3(0.5f, 0.5f, 0.0f), Float3(0.0f, 0.0f, -1.0f), Float2(1.0f, 0.0f) },
			{ Float3(-0.5f, -0.5f, 0.0f), Float3(0.0f, 0.0f, -1.0f), Float2(0.0f, 1.0f) },
			{ Float3(0.5f, -0.5f, 0.0f), Float3(0.0f, 0.0f, -1.0f), Float2(1.0f, 1.0f) },
		};
		int vertexCount = sizeof(quad) / sizeof(quad[0]);

		int index[] = {
			0, 1, 2,
			3, 2, 1,
		};
		indexCount = sizeof(index) / sizeof(index[0]);

		int x = App::GetWindowSize().x;
		int y = App::GetWindowSize().y;

		D3D11_BUFFER_DESC vertexBufferDesc = {};
		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.ByteWidth = sizeof(Vertex) * vertexCount;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = 0;
		D3D11_SUBRESOURCE_DATA vertexSubresourceData = {};
		vertexSubresourceData.pSysMem = quad;
		App::GetGraphicsDevice().CreateBuffer(&vertexBufferDesc, &vertexSubresourceData, vertexBuffer.GetAddressOf());

		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		App::GetGraphicsContext().IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
		App::GetGraphicsContext().IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		D3D11_BUFFER_DESC indexBufferDesc = {};
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = sizeof(int) * indexCount;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		D3D11_SUBRESOURCE_DATA indexSubresourceData = {};
		indexSubresourceData.pSysMem = index;
		App::GetGraphicsDevice().CreateBuffer(&indexBufferDesc, &indexSubresourceData, indexBuffer.GetAddressOf());

		App::GetGraphicsContext().IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

		D3D11_BUFFER_DESC constantBufferDesc = {};
		constantBufferDesc.ByteWidth = sizeof(ConstantBuffer);
		constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constantBufferDesc.CPUAccessFlags = 0;
		App::GetGraphicsDevice().CreateBuffer(&constantBufferDesc, nullptr, constantBuffer.GetAddressOf());

		D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc = {};
		shaderResourceViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		shaderResourceViewDesc.Texture2D.MipLevels = 1;
		App::GetGraphicsDevice().CreateShaderResourceView(texture.Get(), &shaderResourceViewDesc, shaderResourceView.GetAddressOf());

		D3D11_SAMPLER_DESC samplerDesc;
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.MipLODBias = 0.0f;
		samplerDesc.MaxAnisotropy = 1;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		samplerDesc.BorderColor[0] = 0.0f;
		samplerDesc.BorderColor[1] = 0.0f;
		samplerDesc.BorderColor[2] = 0.0f;
		samplerDesc.BorderColor[3] = 0.0f;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
		App::GetGraphicsDevice().CreateSamplerState(&samplerDesc, samplerState.GetAddressOf());
	}
};

class Text : public Sprite {
	PUBLIC Text(const wchar_t* text = L"", const wchar_t* fontFamily = L"") {
		if (text == L"") {
			text = L"\uFFFD";
		}

		LOGFONTW logFont = {};
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
		StringCchCopyW(logFont.lfFaceName, 32, fontFamily);
		HFONT font = CreateFontIndirectW(&logFont);

		HDC dc = GetDC(nullptr);
		HFONT oldFont = (HFONT)SelectObject(dc, font);
		UINT code = text[0];

		TEXTMETRICW textMetrics = {};
		GetTextMetricsW(dc, &textMetrics);
		GLYPHMETRICS glyphMetrics = {};
		const MAT2 matrix = { { 0, 1 }, { 0, 0 }, { 0, 0 }, { 0, 1 } };
		DWORD size = GetGlyphOutlineW(dc, code, GGO_GRAY4_BITMAP, &glyphMetrics, 0, nullptr, &matrix);
		BYTE* textureBuffer = new BYTE[size];
		GetGlyphOutlineW(dc, code, GGO_GRAY4_BITMAP, &glyphMetrics, size, textureBuffer, &matrix);

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

		App::GetGraphicsDevice().CreateTexture2D(&textureDesc, nullptr, texture.GetAddressOf());

		D3D11_MAPPED_SUBRESOURCE mapped;
		App::GetGraphicsContext().Map(texture.Get(), D3D11CalcSubresource(0, 0, 1), D3D11_MAP_WRITE_DISCARD, 0, &mapped);

		BYTE* bits = (BYTE*)mapped.pData;
		DirectX::XMINT2 origin;
		origin.x = glyphMetrics.gmptGlyphOrigin.x;
		origin.y = textMetrics.tmAscent - glyphMetrics.gmptGlyphOrigin.y;
		DirectX::XMINT2 bitmapSize;
		bitmapSize.x = glyphMetrics.gmBlackBoxX + (4 - (glyphMetrics.gmBlackBoxX % 4)) % 4;
		bitmapSize.y = glyphMetrics.gmBlackBoxY;
		const int LEVEL = 17;
		memset(bits, 0, mapped.RowPitch * textMetrics.tmHeight);

		for (int y = origin.y; y < origin.y + bitmapSize.y; y++) {
			for (int x = origin.x; x < origin.x + bitmapSize.x; x++) {
				DWORD alpha = (255 * textureBuffer[x - origin.x + bitmapSize.x * (y - origin.y)]) / (LEVEL - 1);
				DWORD color = 0x00ffffff | (alpha << 24);
				memcpy((BYTE*)bits + mapped.RowPitch * y + 4 * x, &color, sizeof(DWORD));
			}
		}

		App::GetGraphicsContext().Unmap(texture.Get(), D3D11CalcSubresource(0, 0, 1));
		delete[] textureBuffer;
	}
};


}
