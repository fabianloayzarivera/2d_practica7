#pragma once
#include <stb_truetype.h>
#include <litegfx.h>
#include <Vec2.h>
#include <conio.h>
#include <vector>
class Font {
private:
	Font();
	float height;
	int textureHeight;
	int textureWidth;
	std::vector<stbtt_bakedchar> charData;
	ltex_t *texture;
	
public:
	static Font* load(const char* filename, float height);
	float getHeight() const;
	Vec2 getTextSize(const char* text) const;
	void draw(const char* text, const Vec2& pos) const;
	ltex_t* getTexture();
	~Font();
};