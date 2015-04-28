//======================================================================
//File: Torus.h
//Author: Matt Struble
//======================================================================
#ifndef TORUS_H
#define TORUS_H
//======================================================================
#pragma once
//======================================================================
#include "Primitive.h"
//======================================================================
class Torus : public Primitive
{
public:
	Torus(double innerRadius, double outerRadius, int sides, int rings);
	~Torus();

	virtual void Draw() override;

	inline void SetInnerRadius(double radius) { m_InnerRadius = radius; };
	inline void SetOuterRadius(double radius) { m_OuterRadius = radius; };
	inline void SetSides(int sides) { m_Sides = sides; };
	inline void SetRings(int rings) { m_Rings = rings; };

	inline double GetInnerRadius() { return m_InnerRadius; };
	inline double GetOuterRadius() { return m_OuterRadius; };
	inline int GetSides() { return m_Sides; };
	inline int GetRings() { return m_Rings; };

private:
	double m_InnerRadius;
	double m_OuterRadius;
	int m_Sides;
	int m_Rings;
};
#endif