#if !defined(GRAPHICS_H)
#define GRAPHICS_H

#include <d3dx9.h>

class Graphics
{
public:
	const DWORD WINDOW_STYLE = WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX;
	const char TITLE[10] = "GDK";
	const int CLIENT_WIDTH = 1280, CLIENT_HEIGHT = 720;

	Graphics();
	~Graphics();
	void Render();
private:
	int frame;
	HINSTANCE instanceHandle;
	HWND windowHandle;
	LPDIRECT3D9 direct3D;
	LPDIRECT3DDEVICE9 device;
	LPD3DXEFFECT shader;
	LPD3DXMESH mesh;
	LPDIRECT3DTEXTURE9 texture;
	D3DXMATRIX worldMatrix;
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projectionMatrix;
	D3DXVECTOR3 lightDirection;

	static LRESULT __stdcall WindowProcedure(HWND windowHandle, UINT windowMessage, WPARAM wParam, LPARAM lParam);
	bool CreateDevice(LPDIRECT3D9 direct3D, LPDIRECT3DDEVICE9 *device, HWND windowHandle, D3DPRESENT_PARAMETERS *presentParameter, D3DDEVTYPE deviceType, DWORD behaviourFlag);
};

#endif
