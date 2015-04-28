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
	double X;
	double Y;
	double Z;
	static const Vector3D Zero;

	Vector3D();
	Vector3D(double x, double y, double z);
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

	static double Dot(const Vector3D&, const Vector3D&);
	static Vector3D Cross(const Vector3D&, const Vector3D&);

	static Vector3D Lerp(const Vector3D&, const Vector3D&, const float&);
	static Vector3D SLerp(const Vector3D&, const Vector3D&, const float&);
	static Vector3D NLerp(const Vector3D&, const Vector3D&, const float&);
	
	static double Distance(const Vector3D&, const Vector3D&);
	static double DistanceSQ(const Vector3D&, const Vector3D&);

	double Magnitude() const;
	double MagnitudeSquared() const;

	void Normalize();
	Vector3D Normalized();

	void SetIndex(int index, float value);
	float GetIndex(int index) const;

	std::string ToString();
};
#endif
//======================================================================
