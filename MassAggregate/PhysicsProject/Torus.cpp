//======================================================================
//File: Torus.cpp
//Author: Matt Struble
//======================================================================
#include "Torus.h"
//======================================================================
Torus::Torus(double innerRadius, double outerRadius, int sides, int rings)
{
	m_InnerRadius = innerRadius;
	m_OuterRadius = outerRadius;
	m_Sides = sides;
	m_Rings = rings;
}

//--------------------------------------------------------------------------------
void Torus::Draw()
{
	if (m_WireFrame)
	{
		glutWireTorus(m_InnerRadius, m_OuterRadius, m_Sides, m_Rings);
	}
	else
	{
		glutSolidTorus(m_InnerRadius, m_OuterRadius, m_Sides, m_Rings);
	}
}
//================================================================================