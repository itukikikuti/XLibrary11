// (c) 2017 Naoki Nakagawa
#if !defined(TEXTURE_H)
#define TEXTURE_H
#include <string>

class Texture
{
public:
	Texture(std::wstring path);
	~Texture();
	void Draw(float x, float y, float angle, float scale);
};

#endif
