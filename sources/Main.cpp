#include <cstdio>
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr.h>
#include <crtdbg.h>
#include <math.h>
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxerr.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")

struct  Vertex {
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DXVECTOR2 uv;
};

bool CreateDevice(LPDIRECT3D9 direct3D, LPDIRECT3DDEVICE9 *device, HWND windowHandle, D3DPRESENT_PARAMETERS *presentParameter, D3DDEVTYPE deviceType, DWORD behaviourFlag) {
	if (SUCCEEDED(direct3D->CreateDevice(D3DADAPTER_DEFAULT, deviceType, windowHandle, behaviourFlag, presentParameter, device))) {
		return true;
	}
	return false;
}

LRESULT __stdcall WindowProcedure(HWND windowHandle, UINT windowMessage, WPARAM wParam, LPARAM lParam) {
	if (windowMessage == WM_DESTROY) {
		PostQuitMessage(0);
	}
	return DefWindowProc(windowHandle, windowMessage, wParam, lParam);
}

void OutputErrorMessage(HRESULT hresult) {
	OutputDebugString(DXGetErrorDescription(hresult));
	MessageBox(nullptr, DXGetErrorDescription(hresult), "Error", MB_OK | MB_ICONINFORMATION);
}

//int main() {
int __stdcall WinMain(HINSTANCE, HINSTANCE, LPTSTR, int) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	char title[10] = "GDK";
	HWND windowHandle;
	WNDCLASSEX windowClass = {};
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WindowProcedure;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = GetModuleHandle(0);
	windowClass.hIcon = LoadIcon(windowClass.hInstance, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	windowClass.lpszMenuName = nullptr;
	windowClass.lpszClassName = title;
	windowClass.hIconSm = LoadIcon(windowClass.hInstance, IDI_APPLICATION);
	if (!RegisterClassEx(&windowClass)) return 0;

	DWORD windowStyle = WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX;
	windowHandle = CreateWindow(title, title, windowStyle, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, nullptr, nullptr, windowClass.hInstance, nullptr);
	if (!windowHandle) return -1;

	RECT windowRect = {};
	RECT clientRect = {};
	GetWindowRect(windowHandle, &windowRect);
	GetClientRect(windowHandle, &clientRect);
	int clientWidth = 1280, clientHeight = 720;
	int windowWidth = (windowRect.right - windowRect.left) - (clientRect.right - clientRect.left) + clientWidth;
	int windowHeight = (windowRect.bottom - windowRect.top) - (clientRect.bottom - clientRect.top) + clientHeight;
	SetWindowPos(windowHandle, nullptr, 0, 0, windowWidth, windowHeight, SWP_NOMOVE | SWP_NOZORDER);

	ShowWindow(windowHandle, SW_SHOWNORMAL);

	LPDIRECT3D9 direct3D;
	direct3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!direct3D) return -1;

	LPDIRECT3DDEVICE9 device;
	D3DPRESENT_PARAMETERS presentParameter = {};
	presentParameter.BackBufferWidth = clientWidth;
	presentParameter.BackBufferHeight = clientHeight;
	presentParameter.BackBufferFormat = D3DFMT_UNKNOWN;
	presentParameter.BackBufferCount = 0;
	presentParameter.MultiSampleType = D3DMULTISAMPLE_NONE;
	presentParameter.MultiSampleQuality = 0;
	presentParameter.SwapEffect = D3DSWAPEFFECT_DISCARD;
	presentParameter.hDeviceWindow = nullptr;
	presentParameter.Windowed = true;
	presentParameter.EnableAutoDepthStencil = true;
	presentParameter.AutoDepthStencilFormat = D3DFMT_D24S8;
	presentParameter.Flags = 0;
	presentParameter.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	presentParameter.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	if (!CreateDevice(direct3D, &device, windowHandle, &presentParameter, D3DDEVTYPE_HAL, D3DCREATE_HARDWARE_VERTEXPROCESSING)) {
		if (!CreateDevice(direct3D, &device, windowHandle, &presentParameter, D3DDEVTYPE_HAL, D3DCREATE_SOFTWARE_VERTEXPROCESSING)) {
			if (!CreateDevice(direct3D, &device, windowHandle, &presentParameter, D3DDEVTYPE_REF, D3DCREATE_HARDWARE_VERTEXPROCESSING)) {
				if (!CreateDevice(direct3D, &device, windowHandle, &presentParameter, D3DDEVTYPE_REF, D3DCREATE_SOFTWARE_VERTEXPROCESSING)) {
					direct3D->Release();
					return -1;
				}
			}
		}
	}

	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	device->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	device->SetRenderState(D3DRS_ZWRITEENABLE, true);
	device->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1);

	D3DXVECTOR3 lightDirection;
	D3DXVec3Normalize(&lightDirection, &D3DXVECTOR3(0.25f, -1.0f, 0.5f));

	ID3DXBuffer *materials;
	DWORD materialCount;
	LPD3DXMESH mesh;
	if (FAILED(D3DXLoadMeshFromX("monkey.x", D3DXMESH_MANAGED, device, nullptr, &materials, nullptr, &materialCount, &mesh))) {
		device->Release();
		direct3D->Release();
		return -1;
	}

	HRESULT hresult = {};

	LPDIRECT3DTEXTURE9 texture;
	hresult = D3DXCreateTextureFromFile(device, "box.jpg", &texture);
	if (FAILED(hresult)) {
		device->Release();
		direct3D->Release();
		OutputErrorMessage(hresult);
		return -1;
	}

	LPD3DXEFFECT shader = {};
	hresult = D3DXCreateEffectFromFile(device, "shader.fx", nullptr, nullptr, D3DXSHADER_DEBUG, nullptr, &shader, nullptr);
	if (FAILED(hresult)) {
		texture->Release();
		device->Release();
		direct3D->Release();
		OutputErrorMessage(hresult);
		return -1;
	}

	D3DXMATRIX worldMatrix;
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projectionMatrix;
	D3DXMatrixIdentity(&worldMatrix);
	D3DXMatrixIdentity(&viewMatrix);
	D3DXMatrixIdentity(&projectionMatrix);

	int frame = 0;
	MSG windowMessage = {};
	while (windowMessage.message != WM_QUIT) {
		if (PeekMessage(&windowMessage, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&windowMessage);
			DispatchMessage(&windowMessage);
		}
		else {
			frame++;
			device->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(128, 192, 255), 1.0f, 0);
			device->BeginScene();

			D3DXMatrixRotationY(&worldMatrix, frame * 0.01f);
			D3DXMatrixLookAtLH(&viewMatrix, &D3DXVECTOR3(0.0f, 1.0f, -2.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
			D3DXMatrixPerspectiveFovLH(&projectionMatrix, D3DXToRadian(60), clientWidth / (float)clientHeight, 0.01f, 100.0f);

			UINT passCount;
			shader->SetFloat("time", frame * 0.01f);
			shader->SetMatrix("worldMatrix", &worldMatrix);
			shader->SetMatrix("viewMatrix", &viewMatrix);
			shader->SetMatrix("projectionMatrix", &projectionMatrix);
			shader->SetVector("lightDirection", &(D3DXVECTOR4)lightDirection);
			shader->SetTexture("meshTexture", texture);
			shader->SetTechnique("main");
			shader->Begin(&passCount, 0);
			shader->BeginPass(0);

			mesh->DrawSubset(0);

			shader->EndPass();
			shader->End();

			device->EndScene();
			device->Present(nullptr, nullptr, nullptr, nullptr);
			Sleep(1);
		}
	}

	texture->Release();
	shader->Release();
	device->Release();
	direct3D->Release();

	return windowMessage.wParam;
}
