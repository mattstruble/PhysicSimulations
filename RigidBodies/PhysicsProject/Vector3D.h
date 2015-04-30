//======================================================================
//File: Vector3D.h
//Author: Matt Struble
//======================================================================
#ifndef VECTOR3D_H
#define VECTOR3D_H
//======================================================================
#pragma once
//======================================================================
#include <string>
//======================================================================
class Vector3D
{
public:
	float X;
	float Y;
	float Z;
	static const Vector3D Zero;

	Vector3D();
	Vector3D(float x, float y, float z);
	~Vector3D();

	Vector3D operator*(const float&) const;
	Vector3D operator*(const Vector3D&) const;
	Vector3D operator/(const float&) const;
	Vector3D operator+(const Vector3D&) const;
	Vector3D operator-(const Vector3D&) const;
	Vector3D operator-() const;
	Vector3D& operator=(const Vector3D&);
	Vector3D& operator*=(const float&);
	Vector3D& operator*=(const Vector3D&);
	Vector3D& operator/=(const float&);
	Vector3D& operator+=(const Vector3D&);
	Vector3D& operator-=(const Vector3D&);
	bool operator==(const Vector3D&) const;
	bool operator!=(const Vector3D&) const;

	static float Dot(const Vector3D&, const Vector3D&);
	static Vector3D Cross(const Vector3D&, const Vector3D&);

	static Vector3D Lerp(const Vector3D&, const Vector3D&, const float&);
	static Vector3D SLerp(const Vector3D&, const Vector3D&, const float&);
	static Vector3D NLerp(const Vector3D&, const Vector3D&, const float&);
	
	static float Distance(const Vector3D&, const Vector3D&);
	static float DistanceSQ(const Vector3D&, const Vector3D&);

	float Magnitude() const;
	float MagnitudeSquared() const;

	void Normalize();
	Vector3D Normalized();

	void SetIndex(int index, float value);
	float GetIndex(int index) const;

	std::string ToString();
};
#endif
//======================================================================
