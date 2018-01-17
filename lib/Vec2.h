#pragma once
#include "math.h"
#include <string>
#include <iostream>
#define PI 3.141592653589793

class Vec2 {
public:
	static double screenCenterX;
	static double screenCenterY;

	float x;
	float y;

	Vec2(float xNew = 0, float yNew = 0);
	//Vec2 sum(const Vec2 &other);
	Vec2 operator +(const Vec2& other);
	//Vec2 subs(const Vec2 &other);
	Vec2 operator -(const Vec2& other);
	//Vec2 mult(const Vec2 &other);
	Vec2 operator *(const Vec2& other);
	//Vec2 div(const Vec2 &other);
	Vec2 operator /(const Vec2& other);
	Vec2 abs();
	float lenght();
	Vec2 norm();
	float dot(const Vec2 &other);
	float angle(const Vec2& other) const;
	float distance(const Vec2& other) const;

};
