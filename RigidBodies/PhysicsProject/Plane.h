//======================================================================
//File: Plane.h
//Author: Matt Struble
//======================================================================
#ifndef PLANE_H
#define PLANE_H
//======================================================================
#pragma once
//======================================================================
#include "Primitive.h"
#include "Vector3D.h"
//======================================================================
class Plane : public Primitive
{
public:
	Plane(Vector3D dimensions);
	~Plane();

	virtual void Draw() override;

	inline void SetDimensions(Vector3D dimensions) { m_Dimensions = dimensions; };
	inline Vector3D GetDimensions() { return m_Dimensions; };

private:
	Vector3D m_Dimensions;
};
#endif