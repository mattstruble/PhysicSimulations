//======================================================================
//File: Vector2D.cpp
//Author: Matt Struble
//======================================================================
#ifndef VECTOR2D_H
#define VECTOR2D_H
//======================================================================
#pragma once
//======================================================================
#include <string>
//======================================================================
class Vector2D
{
public:
	float X;
	float Y;

	Vector2D();
	Vector2D(float x, float y);
	~Vector2D();

	Vector2D operator*(const float&) const;
	Vector2D operator/(const float&) const;
	Vector2D operator+(const Vector2D&) const;
	Vector2D operator-(const Vector2D&) const;
	Vector2D& operator=(const Vector2D&);
	Vector2D& operator*=(const float&);
	Vector2D& operator/=(const float&);
	Vector2D& operator+=(const Vector2D&);
	Vector2D& operator-=(const Vector2D&);
	bool operator==(const Vector2D&) const;
	bool operator!=(const Vector2D&) const;

	static Vector2D Lerp(const Vector2D&, const Vector2D&, const float&);

	std::string ToString();
};
#endif