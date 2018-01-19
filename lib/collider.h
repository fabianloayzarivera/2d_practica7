#pragma once
#include <litegfx.h>
#include <Vec2.h>
#include <vector>
#include <algorithm>
#include <iostream>

class Collider {
public:
	virtual bool collides(const Collider& other) const = 0;
	virtual bool collides(const Vec2& circlePos, float circleRadius) const = 0;
	virtual bool collides(const Vec2& rectPos, const Vec2& rectSize) const = 0;
	virtual bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const std::vector<unsigned char> pixels) const = 0;
};

bool checkCircleCircle(const Vec2& pos1, float radius1, const Vec2& pos2, float radius2);
bool checkCircleRect(const Vec2& circlePos, float circleRadius, const Vec2& rectPos, const Vec2& rectSize);
bool checkRectRect(const Vec2& rectPos1, const Vec2& rectSize1,	const Vec2& rectPos2, const Vec2& rectSize2);
bool checkPixelsPixels(const Vec2& pixelsPos1, const Vec2& pixelsSize1, const std::vector<unsigned char> pixels1, const Vec2& pixelsPos2, const Vec2& pixelsSize2, const std::vector<unsigned char> pixels2);
bool checkPixelsRect(const Vec2& pixelsPos1, const Vec2& pixelsSize1, const std::vector<unsigned char> pixels1, const Vec2& rectPos, const Vec2& rectSize);
bool checkCirclePixels(const Vec2& circlePos, float circleRadius,const Vec2& pixelsPos, const Vec2& pixelsSize, const std::vector<unsigned char> pixels);

class CircleCollider : public Collider {
private:
	Vec2  *pos;
	float *rad;
public:
	CircleCollider(Vec2& p, float& radio) { pos = &p; rad = &radio; };
	bool collides(const Collider & other) const { return other.collides(*pos, *rad); };
	bool collides(const Vec2& circlePos, float circleRadius) const { return checkCircleCircle(*pos, *rad, circlePos, circleRadius); };
	bool collides(const Vec2& rectPos, const Vec2& rectSize) const { return checkCircleRect(*pos, *rad, rectPos, rectSize); };
	bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const std::vector<unsigned char> pixels) const { return checkCirclePixels(*pos, *rad, pixelsPos, pixelsSize, pixels);};
};

class RectCollider : public Collider {
private:
	Vec2 *pos;
	Vec2 *size;
public:
	RectCollider(Vec2& p, Vec2& s) { pos = &p; size = &s; }; 
	bool collides(const Collider& other) const { return other.collides(*pos, *size); };
	bool collides(const Vec2& rectPos, const Vec2& rectSize) const { return checkRectRect(*pos, *size, rectPos, rectSize); };
	bool collides(const Vec2& circlePos, float circleRadius) const { return checkCircleRect(circlePos, circleRadius, *pos, *size); };
	bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const std::vector<unsigned char> pixels) const { 
		if (checkRectRect(pixelsPos, pixelsSize, *pos, *size))
			return checkPixelsRect(pixelsPos, pixelsSize, pixels, *pos, *size);
		else
			return false;
	};
};

class PixelsCollider : public Collider {
private:
	Vec2 *pos;
	Vec2 *size;
	std::vector<unsigned char> pixels;
public:
	PixelsCollider(Vec2& p, Vec2& s, std::vector<unsigned char> pix) { pos = &p; size = &s; pixels = pix;};
	bool collides(const Collider& other) const { return other.collides(*pos, *size, pixels); };
	bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const std::vector<unsigned char> pixels1) const {
		if (checkRectRect(pixelsPos, pixelsSize, *pos, *size))
			return checkPixelsPixels(*pos, *size, pixels, pixelsPos, pixelsSize, pixels1);
		else
			return false;
	};
	bool collides(const Vec2& circlePos, float circleRadius) const {
		return checkCirclePixels(circlePos, circleRadius, *pos, *size, pixels);
	};
	bool collides(const Vec2& rectPos, const Vec2& rectSize) const {
		if (checkRectRect(rectPos, rectSize, *pos, *size))
			return checkPixelsRect(*pos, *size, pixels, rectPos, rectSize);
		else
			return false;

	};
};
