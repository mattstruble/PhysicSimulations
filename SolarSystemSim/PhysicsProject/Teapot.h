//======================================================================
//File: Teapot.h
//Author: Matt Struble
//======================================================================
#ifndef TEAPOT_H
#define TEAPOT_H
//======================================================================
#pragma once
//======================================================================
#include "Primitive.h"
//======================================================================
class Teapot : public Primitive
{
public:
	Teapot(double size);
	~Teapot();

	virtual void Draw() override;

	inline void SetSize(double size) { m_Size = size; };

	inline double GetSize() { return m_Size; };

private:
	double m_Size;
};
#endif