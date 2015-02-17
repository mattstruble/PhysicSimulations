//======================================================================
//File: Cube.cpp
//Author: Matt Struble
//======================================================================
#include "Cone.h"
//======================================================================
Cone::Cone(double base, double height, int slices, int stacks)
{
	m_Base = base;
	m_Height = height;
	m_Slices = slices;
	m_Stacks = stacks;
}

//--------------------------------------------------------------------------------
void Cone::Draw()
{
	if (m_WireFrame)
	{
		glutWireCone(m_Base, m_Height, m_Slices, m_Stacks);
	}
	else
	{
		glutSolidCone(m_Base, m_Height, m_Slices, m_Stacks);
	}
}
//================================================================================