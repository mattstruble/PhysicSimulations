//======================================================================
//File: Cube.h
//Author: Matt Struble
//======================================================================
#ifndef CUBE_H
#define CUBE_H
//======================================================================
#pragma once
//======================================================================
#include "Primitive.h"
//======================================================================
class Cube : public Primitive
{
public:
	Cube(double size);
	~Cube() {};

	virtual void Draw() override;

	inline void SetSize(double size) { m_Size = size; };
	inline double GetSize() { return m_Size; };

private:
	double m_Size;
};
#endif