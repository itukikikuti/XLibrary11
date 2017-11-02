// (c) 2017 Naoki Nakagawa
#if !defined(SPRITE_H)
#define SPRITE_H

class Sprite
{
public:
	Sprite();
	~Sprite();
	void Draw(float x, float y, float angle, float scale);

private:
	struct Constant {
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
	};

	int vertexCount;
	int indexCount;
	Constant constant;
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	ID3D11Buffer* constantBuffer;
};

#endif
