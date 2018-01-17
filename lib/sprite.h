#pragma once
#include <stb_truetype.h>
#include <litegfx.h>
#include <Vec2.h>
#include <conio.h>
#include <vector>
#include <math.h>
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
	int horizontalFrames;
	int verticalFrames;
	int fps;
	float currentFrame;
	
	
public :
	Sprite(const ltex_t* tex, int hframes = 1, int vframes = 1);
	const ltex_t* getTexture() const;
	void setTexture(const ltex_t* tex);


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

	// Este valor se pasa a ltex_drawrotsized en el pintado
	// para indicar el pivote de rotación
	const Vec2& getPivot() const;
	void setPivot(const Vec2& pivot);

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


};