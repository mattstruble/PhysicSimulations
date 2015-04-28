//======================================================================
//File: Quaternion.h
//Author: Matt Struble
//======================================================================
#ifndef QUATERNION_H
#define QUATERNION_H
//======================================================================
#pragma once
//======================================================================
class Vector3D;
//======================================================================
class Quaternion
{
public: 
	float R;
	float I;
	float J;
	float K;

	Quaternion();
	Quaternion(float r, float i, float j, float k);
	Quaternion(const Vector3D& vec);
	Quaternion(const Quaternion&);
	~Quaternion();

	void Normalize();

	Quaternion operator*(const Quaternion&);
	Quaternion& operator*=(const Quaternion&);
	Quaternion& operator=(const Quaternion&);
	bool operator==(const Quaternion&) const;
	bool operator!=(const Quaternion&) const;

	void VectorRotation(const Vector3D& rhs);
	void VectorScaling(const Vector3D& rhs, float scale);
};
#endif