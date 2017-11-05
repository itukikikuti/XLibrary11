// (c) 2017 Naoki Nakagawa
#if !defined(SPRITE_H)
#define SPRITE_H

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

#endif
