//======================================================================
//File: Cone.h
//Author: Matt Struble
//======================================================================
#ifndef CONE_H
#define CONE_H
//======================================================================
#pragma once
//======================================================================
#include "Primitive.h"
//======================================================================
class Cone : public Primitive
{
public:
	Cone(double base, double height, int slices, int stacks);
	~Cone();

	virtual void Draw() override;

	inline void SetBase(double base) { m_Base = base; };
	inline void SetHeight(double height) { m_Height = height; };
	inline void SetSlices(int slices) { m_Slices = slices; };
	inline void SetStacks(int stacks) { m_Stacks = stacks; };

	inline double GetBase() { return m_Base; };
	inline double GetHeight() { return m_Height; };
	inline int GetSize() { return m_Slices; };
	inline int GetStacks() { return m_Stacks; };

private:
	double m_Base;
	double m_Height;
	int m_Slices;
	int m_Stacks;
};
#endif