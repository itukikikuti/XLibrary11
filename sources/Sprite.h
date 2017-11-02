// (c) 2017 Naoki Nakagawa
#if !defined(SPRITE_H)
#define SPRITE_H
#include <string>

class Sprite
{
public:
	Sprite(std::wstring path);
	~Sprite();
	void Draw(float x, float y, float angle, float scale);
};

#endif
