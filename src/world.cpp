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
	textureAmount = 0;
	mapSize = Vec2(0, 0);
	firstgId = 0;
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
	for (int i = 0; i < textureAmount; i++) {
		scrollSpeedFrames[i].x += scrollSpeeds[i].x * deltaTime;
		scrollSpeedFrames[i].y += scrollSpeeds[i].y * deltaTime;
	}
}

void World::draw(const Vec2& screenSize) {
	lgfx_setblend(backgroundBlend);

	for (int i = 0; i < textureAmount; i++) {
		float u0 = ((cameraPosition.x * scrollRatios[i]) + scrollSpeedFrames[i].x) / textures[i]->width;
		float v0 = ((cameraPosition.y * scrollRatios[i]) + scrollSpeedFrames[i].y) / textures[i]->height;
		float u1 = (screenSize.x / textures[i]->width) + u0;
		float v1 = (screenSize.y / textures[i]->height) + v0;

		ltex_drawrotsized(textures[i], cameraPosition.x, cameraPosition.y, 0, 0, 0, screenSize.x + u0, screenSize.y + v0, u0, v0, u1, v1);
	}
	
	////Sprite
	sprite->draw();
	drawMap();
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

	if (mapSize.x > worldSize.x)
		worldSize.x = mapSize.x;
	if (mapSize.y > worldSize.y)
		worldSize.y = mapSize.y;


	
}

bool World::loadMap(const char* filename, uint16_t firstColId) {
	firstCollisionableId = firstColId;

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(filename);
	if (result) {
		// Cargado correctamente, podemos analizar su contenido ...
		printf("LOADED!");

		pugi::xml_node mapNode = doc.child("map");

		for (pugi::xml_node tileNode = mapNode.child("layer").child("data").child("tile"); tileNode; tileNode = tileNode.next_sibling("tile")) {
			// Iteramos por todos los tiles
			int gid = tileNode.attribute("gid").as_int();
			tileIds.push_back(gid);
			
		}
		tileWidth = mapNode.attribute("tilewidth").as_int();
		tileHeight= mapNode.attribute("tileheight").as_int();
		mapWidthTileCount = mapNode.child("layer").attribute("width").as_int();
		mapHeightTileCount = mapNode.child("layer").attribute("height").as_int();
		firstgId = mapNode.child("tileset").attribute("firstgid").as_int();

		mapSize.x = mapWidthTileCount * tileWidth;
		mapSize.y = mapHeightTileCount * tileHeight;
		return true;
	}
	else {
		// No se ha podido cargar
		std::cout << result.description() << std::endl;
		return false;
	}

}

void World::drawMap() {
	
	float u0, v0, u1, v1;

	
	for (int i = 0; i < mapHeightTileCount; i++) {
		for (int j = 0; j < mapWidthTileCount; j++) {
			int gidPos = (i * mapWidthTileCount) + j;
			float xPos = j * tileWidth;
			float yPos = i * tileHeight;
			calculateUV(tileIds.at(gidPos), u0, v0, u1, v1);
			ltex_drawrotsized(mapTiles, xPos, yPos, 0.0f, 0.0f, 0.0f, tileWidth, tileWidth, u0, v0, u1, v1);
				
		}	
	}


}


Vec2 World::getMapSize() const {

	return mapSize;
}

bool World::moveSprite(Sprite& sprite, const Vec2& amount) {

	return true;
}

void World::calculateUV(int gid, float &u0, float &v0, float &u1, float &v1) {
	
	u0 = 0;
	u1 = 0;
	v0 = 0;
	v1 = 0;

	gid -= firstgId;
	if (gid >= 0) {
		int row = (gid / (mapTiles->width / tileWidth));
		int column = gid - (row * (mapTiles->width / tileWidth));



		u0 = static_cast<float>(column * tileWidth) / mapTiles->width;
		v0 = static_cast<float>(row * tileHeight) / mapTiles->height;
		u1 = u0 + (static_cast<float>(tileWidth) / mapTiles->width);
		v1 = v0 + (static_cast<float>(tileHeight) / mapTiles->height);
	}

}

