#pragma once
#include <stb_truetype.h>
//#include <litegfx.h>
//#include <Vec2.h>
#include <conio.h>
#include <collider.h>
//#include <vector>
//#include <math.h>

enum CollisionType {
	COLLISION_NONE,
	COLLISION_CIRCLE,
	COLLISION_RECT,
	COLLISION_PIXELS
};

class Sprite {
private:
	const ltex_t* texture;
	lblend_t blend;
	float red;
	float green;
	float blue;
	float alpha;
	float angle;
	Vec2 position;
	Vec2 scale;
	Vec2 size;
	Vec2 pivot;
	Vec2 topLeft;
	Vec2 scaledSize;
	float radio;
	int horizontalFrames;
	int verticalFrames;
	int fps;
	float currentFrame;
	Collider *collider;
	CollisionType colliderType;
	int textureHorizontalDirection;
	int textureVerticalDirection;

public:
	Sprite(const ltex_t* tex, int hframes = 1, int vframes = 1);
	const ltex_t* getTexture() const;
	void setTexture(const ltex_t* tex);

	int getTextureHorizontalDirection();
	void setTextureHorizontalDirection(int dir);

	int getTextureVerticalDirection();
	void setTextureVerticalDirection(int dir);

	lblend_t getBlend() const;
	void setBlend(lblend_t mode);

	float getRed() const;
	float getGreen() const;
	float getBlue() const;
	float getAlpha() const;
	void setColor(float r, float g, float b, float a);

	const Vec2& getPosition() const;
	void setPosition(const Vec2& pos);

	float getAngle() const;
	void setAngle(float angle);

	const Vec2& getScale() const;
	void setScale(const Vec2& scale);


	// Tamaño de un frame multiplicado por la escala
	Vec2 getSize() const;
	void setSize(const Vec2& s); //added by me

	const Vec2& getTopLeft() const;
	void setTopLeft(const Vec2& p);

	const Vec2& getScaledSize() const;
	void setScaledSize(const Vec2& s);

	// Este valor se pasa a ltex_drawrotsized en el pintado
	// para indicar el pivote de rotación
	const Vec2& getPivot() const;
	void setPivot(const Vec2& pivot);

	void setRadio(const float& r);
	float getRadio();

	int getHframes() const;
	int getVframes() const;
	void setFrames(int hframes, int vframes);


	// Veces por segundo que se cambia el frame de animación
	int getFps() const;
	void setFps(int fps);


	// Frame actual de animación
	float getCurrentFrame() const;
	void setCurrentFrame(int frame);

	void update(float deltaTime);
	void draw() const;

	void             setCollisionType(CollisionType type);
	CollisionType    getCollisionType() const;
	const Collider*  getCollider() const;
	bool             collides(const Sprite& other) const;


};

