//======================================================================
//File: Teapot.cpp
//Author: Matt Struble
//======================================================================
#include "Teapot.h"
//======================================================================
Teapot::Teapot(double size)
{
	m_Size = size;
}

//--------------------------------------------------------------------------------
void Teapot::Draw()
{
	if (m_WireFrame)
	{
		glutWireTeapot(m_Size);
	}
	else
	{
		glutSolidTeapot(m_Size);
	}
}
//================================================================================