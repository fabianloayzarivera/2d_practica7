#include <font.h>
#include <iostream>


Font*  Font::load(const char* filename, float height) {
	Font *resultFont = nullptr;
	FILE *ptr;
	size_t size = 128;
	
	std::vector<unsigned char> pixels(size * size);
	std::vector<unsigned char> colorBuffer;
	std::vector<stbtt_bakedchar> charData(96);
	ptr = fopen(filename, "rb");
	if (ptr == NULL) {
		return nullptr;
	}
	else {
		fseek(ptr, 0, SEEK_END);
		size_t sizeBuffer = ftell(ptr);
		fseek(ptr, 0, SEEK_SET);
		std::vector<unsigned char> ttf_buffer(sizeBuffer);
		fread_s(ttf_buffer.data(), sizeBuffer, 1, sizeBuffer, ptr);
		fclose(ptr);
	
		while (stbtt_BakeFontBitmap(ttf_buffer.data(), 0, height, pixels.data(), size, size, 32, 96, charData.data()) <= 0) {
			size *= 2;
			pixels.resize(size * size);
		}

		for (std::vector<unsigned char>::iterator i = pixels.begin(); i != pixels.end(); ++i) {
			colorBuffer.push_back(255);
			colorBuffer.push_back(255);
			colorBuffer.push_back(255);
			colorBuffer.push_back(*i);
		}
		lgfx_setblend(BLEND_ALPHA);
		ltex_t * tex = ltex_alloc(size, size, 0);
		ltex_setpixels(tex, colorBuffer.data());

		resultFont = new Font();
		resultFont->height = height;
		resultFont->texture = tex;
		resultFont->textureWidth = size;
		resultFont->textureHeight = size;
		resultFont->charData = charData;
		
		pixels.clear();
		colorBuffer.clear();
		ttf_buffer.clear();
		

	}
		
	return resultFont;
}

void Font::draw(const char* text, const Vec2& pos) const {
	
	stbtt_aligned_quad *aligned_quad = new stbtt_aligned_quad();
	float xPos = pos.x;
	float yPos = pos.y;
	for (int i = 0; i < strlen(text); i++) {
		int carIndex = text[i] - 32;
		stbtt_GetBakedQuad(charData.data(), textureWidth, textureHeight, carIndex, &xPos, &yPos, aligned_quad, true);
		ltex_drawrotsized(texture, aligned_quad->x0, aligned_quad->y0, 0, 0, 0, (aligned_quad->x1 - aligned_quad->x0), (aligned_quad->y1 - aligned_quad->y0), aligned_quad->s0, aligned_quad->t0, aligned_quad->s1, aligned_quad->t1);
	}

}

Vec2 Font::getTextSize(const char* text) const {
	float textWidth = 0;
	float textHeight = 0;
	stbtt_aligned_quad *aligned_quad = new stbtt_aligned_quad();
	float xPos = 0.0f;
	float yPos = 0.0f;
	for (int i = 0; i < strlen(text); i++) {
		int carIndex = text[i] - 32;
		stbtt_GetBakedQuad(charData.data(), textureWidth, textureHeight, carIndex, &xPos, &yPos, aligned_quad, true);
		//textWidth += (aligned_quad->x1 - aligned_quad->x0);
		if (i == strlen(text) - 1) {
			textWidth = aligned_quad->x1;
		}
		float letterHeight = abs(abs(aligned_quad->y1) - abs(aligned_quad->y0));
		if (letterHeight  > textHeight) {
			textHeight = letterHeight;
		}
	}

	return Vec2(textWidth, textHeight);

}

ltex_t* Font::getTexture() {
	return texture;
}
float Font::getHeight() const {
	return height;
}
Font::Font() {}
Font::~Font() {
	ltex_free(texture);
	charData.clear();
}

