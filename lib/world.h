#pragma once
#include "sprite.h"

class World {
private:
	Sprite* sprite;
	float clearRed;
	float clearGreen;
	float clearBlue;
	ltex_t* textures[255];
	//ltex_t* back0;
	//ltex_t* back1;
	//ltex_t* back2;
	//ltex_t* back3;
	lblend_t backgroundBlend;
	float scrollRatios[255];
	//float scrollRatio0;
	//float scrollRatio1;
	//float scrollRatio2;
	//float scrollRatio3;
	float back3FrameX;
	float back3FrameY;
	Vec2 scrollSpeeds[255];
	Vec2 scrollSpeedFrames[255];

	int textureAmount;
	Vec2 cameraPosition;
	Vec2 screenSize;
	Vec2 worldSize;

public:
	World();
	~World();
	float getClearRed() const { return clearRed; }
	float getClearGreen() const { return clearGreen; }
	float getClearBlue() const { return clearBlue; }
	const ltex_t* getBackground(size_t layer) const;
	void World::setBackground(size_t layer, ltex_t* tex);
	float getScrollRatio(size_t layer) const;
	void setScrollRatio(size_t layer, float ratio);
	const Vec2& getScrollSpeed(size_t layer) const;
	void setScrollSpeed(size_t layer, const Vec2& speed);
	const Vec2& getCameraPosition() const { return cameraPosition; }
	void setCameraPosition(const Vec2& pos) { cameraPosition = pos; }
	const Vec2& getScreenSize() const { return screenSize; }
	void setScreenSize(const Vec2& screen) { screenSize = screen; }
	const Vec2& getWorldSize() const { return worldSize; }
	void setWorldSize(const Vec2& size) { worldSize = size; }
	void addSprite(Sprite& s) { sprite = &s; }
	void removeSprite(Sprite& s) { delete(sprite); sprite = &s;	}
	void updateSpritePosition(const Vec2& pos) { sprite->setPosition(pos); }
	void updateSpriteAngle(const float angle) { sprite->setAngle(angle); }
	void updateWorldSize();
	void updateCameraPosition(const Vec2& pos, float deltaTime);
	void update(float deltaTime);
	void draw(const Vec2& screenSize);
};
	

