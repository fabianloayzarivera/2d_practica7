#include <world.h>

World::World() {
	sprite = nullptr;
	clearRed = 0.8f;
	clearGreen = 0.7f;
	clearBlue = 0.8f;
	backgroundBlend = BLEND_ALPHA;
	cameraPosition = Vec2(0,0);
	screenSize = Vec2(800.0f, 600.0f);
	worldSize = screenSize;
	back3FrameX = 0;
	back3FrameY = 0;
	textureAmount = 0;
}

void World::updateCameraPosition(const Vec2& pos, float deltaTime) {
		
	cameraPosition.x = pos.x - (screenSize.x / 2.0f);
	cameraPosition.y = pos.y - (screenSize.y / 2.0f);
	if (cameraPosition.x < 0)
		cameraPosition.x = 0;
	if (cameraPosition.y < 0)
		cameraPosition.y = 0;

	if (cameraPosition.x > worldSize.x - screenSize.x)
		cameraPosition.x = worldSize.x - screenSize.x;
	if (cameraPosition.y > worldSize.y - screenSize.y)
		cameraPosition.y = worldSize.y - screenSize.y;

}

void World::update(float deltaTime) {
	sprite->update(deltaTime);
	/*back3FrameX += scrollSpeed3.x * deltaTime;
	back3FrameY += scrollSpeed3.y * deltaTime;*/
	for (int i = 0; i < textureAmount; i++) {
		scrollSpeedFrames[i].x += scrollSpeeds[i].x * deltaTime;
		scrollSpeedFrames[i].y += scrollSpeeds[i].y * deltaTime;
	}
}

void World::draw(const Vec2& screenSize) {
	lgfx_setblend(backgroundBlend);

	for (int i = 0; i < textureAmount; i++) {
		/*float u0 = (cameraPosition.x / textures[i]->width) * scrollRatios[i];
		float v0 = (cameraPosition.y / textures[i]->height) * scrollRatios[i];*/
		float u0 = ((cameraPosition.x * scrollRatios[i]) + scrollSpeedFrames[i].x) / textures[i]->width;
		float v0 = ((cameraPosition.y * scrollRatios[i]) + scrollSpeedFrames[i].y) / textures[i]->height;
		float u1 = (screenSize.x / textures[i]->width) + u0;
		float v1 = (screenSize.y / textures[i]->height) + v0;

		ltex_drawrotsized(textures[i], cameraPosition.x, cameraPosition.y, 0, 0, 0, screenSize.x + u0, screenSize.y + v0, u0, v0, u1, v1);
	}
	
	////Sprite
	sprite->draw();
}

const ltex_t* World::getBackground(size_t layer) const {
	return textures[layer];
}

void World::setBackground(size_t layer, ltex_t* tex) {
	textures[layer] = tex;
	textureAmount++;
}

float World::getScrollRatio (size_t layer) const{
	return scrollRatios[layer];
}

void World::setScrollRatio(size_t layer, float ratio) {
	scrollRatios[layer] = ratio;
}

const Vec2& World::getScrollSpeed(size_t layer) const {
	return scrollSpeeds[layer];
}

void World::setScrollSpeed(size_t layer, const Vec2& speed) {
	scrollSpeeds[layer] = speed;
}

World::~World() {
	for (int i = 0; i < textureAmount; i++) {
		ltex_free(textures[i]);		
	}
}

void World::updateWorldSize() {
	for (int i = 0; i < textureAmount; i++) {
		if (textures[i]->width > worldSize.x)
			worldSize.x = textures[i]->width;
		if (textures[i]->height > worldSize.y)
			worldSize.y = textures[i]->height;

	}
}