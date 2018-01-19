#include <sprite.h>

Sprite::Sprite(const ltex_t* tex, int hframes, int vframes) {
	texture = tex;
	horizontalFrames = hframes;
	verticalFrames = vframes;
	textureHorizontalDirection = 1;
	textureVerticalDirection = 1;
	position = Vec2(0, 0);
	scale = Vec2(1, 1);
	size = Vec2(0, 0);
	pivot = Vec2(0, 0);
	topLeft = Vec2(0, 0);
	radio = (size.x * scale.x) > (size.y * scale.y) ? (size.x * scale.x) / 2 : (size.y * scale.y) / 2;
	currentFrame = 0;
	red = 1;
	blue = 1;
	green = 1;
	alpha = 1;

}

const ltex_t* Sprite::getTexture() const { return texture; }
void Sprite::setTexture(const ltex_t* tex) { texture = tex; }


lblend_t Sprite::getBlend() const { return blend; }
void Sprite::setBlend(lblend_t mode) { blend = mode; }

int Sprite::getTextureHorizontalDirection() { return textureHorizontalDirection; }
void Sprite::setTextureHorizontalDirection(int dir) { textureHorizontalDirection = dir; }

int Sprite::getTextureVerticalDirection() { return textureVerticalDirection; }
void Sprite::setTextureVerticalDirection(int dir) { textureVerticalDirection = dir; }

float Sprite::getRed() const { return red; }
float Sprite::getGreen() const { return green; }
float Sprite::getBlue() const { return blue; }
float Sprite::getAlpha() const { return alpha; }
void Sprite::setColor(float r, float g, float b, float a) { red = r; green = g; blue = b; alpha = a; }

const Vec2& Sprite::getPosition() const { return position; }
void Sprite::setPosition(const Vec2& pos) { 
	position = pos; 
	radio = (size.x * scale.x) > (size.y * scale.y) ? (size.x * scale.x) / 2 : (size.y * scale.y) / 2;
	topLeft = Vec2(position.x - (size.x * scale.x * pivot.x), position.y - (size.y * scale.y * pivot.y));
}

float Sprite::getAngle() const { return angle; }
void Sprite::setAngle(float a) { angle = a; }

const Vec2& Sprite::getScale() const { return scale; }
void Sprite::setScale(const Vec2& s) {
	scale = s;
	radio = (size.x * scale.x) > (size.y * scale.y) ? (size.x * scale.x) / 2 : (size.y * scale.y) / 2;
	topLeft = Vec2(position.x - (size.x * scale.x * pivot.x), position.y - (size.y * scale.y * pivot.y));
	scaledSize = Vec2(size.x * scale.x, size.y * scale.y);
} //Update radio and topleft too

  // Tamaño de un frame multiplicado por la escala
Vec2 Sprite::getSize() const { return Vec2(texture->width, texture->height); }
void Sprite::setSize(const Vec2& s) { size = s; };

const Vec2& Sprite::getTopLeft() const { return topLeft; }
void Sprite::setTopLeft(const Vec2& t) { topLeft = t; }

const Vec2& Sprite::getScaledSize() const { return scaledSize; }
void Sprite::setScaledSize(const Vec2& t) { scaledSize = t; }

// Este valor se pasa a ltex_drawrotsized en el pintado
// para indicar el pivote de rotación
const Vec2& Sprite::getPivot() const { return pivot; }
void Sprite::setPivot(const Vec2& p) { pivot = p; }

void Sprite::setRadio(const float& r) { radio = r; };
float Sprite::getRadio() { return radio; };

int Sprite::getHframes() const { return horizontalFrames; }
int Sprite::getVframes() const { return verticalFrames; }
void Sprite::setFrames(int hframes, int vframes) { horizontalFrames = hframes; verticalFrames = vframes; }


// Veces por segundo que se cambia el frame de animación
int Sprite::getFps() const { return fps; }
void Sprite::setFps(int f) { fps = f; }


// Frame actual de animación
float Sprite::getCurrentFrame() const { return currentFrame; }
void Sprite::setCurrentFrame(int frame) { currentFrame = frame; }

void Sprite::update(float deltaTime) {
	float frame = getCurrentFrame() + fps * deltaTime;
	currentFrame = frame;

}

void Sprite::draw() const {

	float frameWidth = texture->width / horizontalFrames;
	float widthRatio = 1.0f / horizontalFrames;
	float u0 = widthRatio * static_cast<int>(currentFrame);
	float u1 = u0 + widthRatio;
	lgfx_setblend(blend);
	lgfx_setcolor(red, green, blue, alpha);
	ltex_drawrotsized(texture, position.x, position.y, angle, pivot.x, pivot.y, frameWidth * scale.x, texture->height * scale.x, u0 * textureHorizontalDirection, 0 * textureVerticalDirection, u1 * textureHorizontalDirection, 1 * textureVerticalDirection);
}

void Sprite::setCollisionType(CollisionType type) {

	if (type == COLLISION_NONE) {
		delete(collider);
	}
	if (type == COLLISION_CIRCLE) {
		delete(collider);
		CircleCollider *colCirc = new CircleCollider(position, radio);
		collider = colCirc;
		colliderType = type;
	}
	if (type == COLLISION_RECT) {
		delete(collider);
		RectCollider *colRect = new RectCollider(topLeft, scaledSize);
		collider = colRect;
		colliderType = type;
	}
	if (type == COLLISION_PIXELS) {
		delete(collider);
		std::vector<unsigned char> pixels(texture->width * texture->height * 4);
		ltex_getpixels(texture, pixels.data());
		//uint8_t* pix = pixels.data();
		PixelsCollider *colPix = new PixelsCollider(topLeft, scaledSize, pixels);
		collider = colPix;
		colliderType = type;
	}

};

CollisionType    Sprite::getCollisionType() const { return colliderType; };
const Collider*  Sprite::getCollider() const { return collider; };
bool             Sprite::collides(const Sprite& other) const { return collider->collides(*(other.getCollider())); };