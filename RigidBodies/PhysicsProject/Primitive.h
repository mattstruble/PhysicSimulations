//======================================================================
//File: Primitive.h
//Author: Matt Struble
//======================================================================
#ifndef PRIMITIVE_H
#define PRIMITIVE_H
//======================================================================
#pragma once
//======================================================================
#include <GL\glut.h>
#include "Color.h"
//======================================================================
class Primitive
{
public:
	Primitive() { m_WireFrame = false; m_Color = Color::GREY; };
	~Primitive() {};

	virtual void Draw() = 0; 

	inline void SetWireFrame() { m_WireFrame = true; };
	inline void SetSolid() { m_WireFrame = false; };
	inline void SetColor(Color c) { m_Color = c; };
	inline Color GetColor() { return m_Color; };
protected:
	bool m_WireFrame;
	Color m_Color;
};
#endif