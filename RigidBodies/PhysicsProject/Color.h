//======================================================================
//File: Color.h
//Author: Matt Struble
//======================================================================
#ifndef COLOR_H
#define COLOR_H
//======================================================================
#pragma once
//======================================================================
#include <GL\glut.h>
//======================================================================
struct Color
{
	float R, G, B, A;

	Color() {}

	Color(float r, float g, float b, float a = 255)
	{
		R = r;
		G = g;
		B = b;
		A = a;
	}

	void ConvertToDecimal()
	{
		R /= 255;
		G /= 255;
		B /= 255;
	}

	Color operator&=(const Color& rhs)
	{
		R = rhs.R;
		G = rhs.G;
		B = rhs.B;
	}

	bool operator==(const Color& rhs)
	{
		return R == rhs.R && B == rhs.B && G == rhs.G;
	}

	Color operator/(const Color& rhs)
	{
		return Color(R / rhs.R, G / rhs.G, B / rhs.B, A / rhs.A);
	} 

	
	static const struct Color RED;
	static const struct Color BLUE;
	static const struct Color GREEN;
	static const struct Color YELLOW;
	static const struct Color ORANGE;
	static const struct Color MAGENTA;
	static const struct Color WHITE;
	static const struct Color BLACK;
	static const struct Color TURQUOISE;
	static const struct Color AZURE;
	static const struct Color LIME;
	static const struct Color CORNFLOWERBLUE;
	static const struct Color GREY;
	static const struct Color RANDOM;

private:
	static const struct Color DEFAULT;
};
#endif