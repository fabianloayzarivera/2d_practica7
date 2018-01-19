#pragma once
#include "sprite.h"
#include "pugiconfig.hpp"
#include "pugixml.hpp"

class World {
private:
	Sprite* sprite;
	float clearRed;
	float clearGreen;
	float clearBlue;
	ltex_t* textures[255];
	ltex_t* mapTiles;
	lblend_t backgroundBlend;
	float scrollRatios[255];
	Vec2 scrollSpeeds[255];
	Vec2 scrollSpeedFrames[255];
	std::vector<int> tileIds;
	int tileWidth;
	int tileHeight;
	int mapWidthTileCount;
	int mapHeightTileCount;
	uint16_t firstCollisionableId;
	int firstgId;
	int textureAmount;
	Vec2 cameraPosition;
	Vec2 screenSize;
	Vec2 worldSize;
	Vec2 mapSize;

public:
	World();
	~World();
	float getClearRed() const { return clearRed; }
	float getClearGreen() const { return clearGreen; }
	float getClearBlue() const { return clearBlue; }
	const ltex_t* getBackground(size_t layer) const;
	void setBackground(size_t layer, ltex_t* tex);
	void setMapTiles(ltex_t* tex) { mapTiles = tex; }
	ltex_t* getMapTiles() { return mapTiles; }
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
	void updateCameraPosition(float deltaTime);
	void update(float deltaTime);
	void draw(const Vec2& screenSize);
	bool loadMap(const char* filename, uint16_t firstColId);
	void drawMap();
	Vec2 getMapSize() const;
	bool moveSprite(const Vec2& amount);
	void calculateUV(int gid, float &u0, float &v0, float &u1, float &v1);

};
	

