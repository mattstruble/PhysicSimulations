//======================================================================
//File: Sphere.h
//Author: Matt Struble
//======================================================================
#ifndef SPHERE_H
#define SPHERE_H
//======================================================================
#pragma once
//======================================================================
#include "Primitive.h"
//======================================================================
class Sphere : public Primitive
{
public:
	Sphere(double radius, int slices, int stacks);
	~Sphere();

	virtual void Draw() override;

	inline void SetRadius(double radius) { m_Radius = radius; };
	inline void SetSlices(int slices) { m_Slices = slices; };
	inline void SetStacks(int stacks) { m_Stacks = stacks; };

	inline double GetRadius() { return m_Radius; };
	inline int GetSize() { return m_Slices; };
	inline int GetStacks() { return m_Stacks; };

private: 
	double m_Radius;
	int m_Slices;
	int m_Stacks;
};
#endif