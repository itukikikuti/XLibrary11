// (c) 2017 Naoki Nakagawa
#pragma once
#include <list>
#include <windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

// (c) 2017 Naoki Nakagawa
#pragma once

namespace GameLibrary {
	class Sprite {
	public:
		Sprite();
		Sprite(wchar_t* path);
		virtual ~Sprite();
		void Draw(float x, float y, float angle, float scale);

	protected:
		void Initialize();

		UINT width;
		UINT height;
		ID3D11Texture2D* texture;

	private:
		struct Vertex {
			DirectX::XMFLOAT3 position;
			DirectX::XMFLOAT2 uv;
		};

		struct Constant {
			DirectX::XMMATRIX world;
			DirectX::XMMATRIX view;
			DirectX::XMMATRIX projection;
		};

		wchar_t* path;
		int indexCount;
		Constant constant;
		ID3D11Buffer* vertexBuffer;
		ID3D11Buffer* indexBuffer;
		ID3D11Buffer* constantBuffer;
		ID3D11ShaderResourceView* shaderResourceView;
		ID3D11SamplerState* samplerState;
	};
}

// (c) 2017 Naoki Nakagawa
#pragma once

namespace GameLibrary {
	class Text : public Sprite {
	public:
		Text(char* text, char* fontFamily = "‚l‚r –¾’©");
	};
}


namespace GameLibrary {
	class Game {
	public:
		Game() = delete;
		static HWND GetWindow();
		static DirectX::XMINT2 GetSize();
		static void SetSize(int width, int height);
		static char* GetTitle();
		static void SetTitle(char* title);
		static ID3D11Device& GetDevice();
		static IDXGISwapChain& GetSwapChain();
		static ID3D11DeviceContext& GetDeviceContext();
		static ID3D11RenderTargetView& GetRenderTargetView();
		static DirectX::XMINT2 GetMousePosition();
		static bool GetKey(int VK_CODE);
		static bool GetKeyUp(int VK_CODE);
		static bool GetKeyDown(int VK_CODE);
		static float GetDeltaTime();
		static void AddFont(char* path);
		static bool Update();

	private:
		static DirectX::XMINT2 size;
		static DirectX::XMINT2 mousePosition;
		static BYTE preKeyState[];
		static BYTE keyState[];
		static float deltaTime;
		static std::list<char*> fontPathList;

		static void Finalize();
		static void CompileShader(WCHAR* filePath, char* entryPoint, char* shaderModel, ID3DBlob** out);
		static void ProcessSize();
		static void ProcessMousePosition();
		static void ProcessKey();
		static void PrecessDeltaTime();
		static bool ProcessResponse();
		static LRESULT WINAPI ProcessWindow(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
	};
}
