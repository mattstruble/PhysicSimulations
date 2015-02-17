//======================================================================
//File: Sphere.cpp
//Author: Matt Struble
//======================================================================
#include "Sphere.h"
//======================================================================
Sphere::Sphere(double radius, int slices, int stacks)
{
	m_Radius = radius;
	m_Slices = slices;
	m_Stacks = stacks;
}

//--------------------------------------------------------------------------------
Sphere::~Sphere()
{

}

//--------------------------------------------------------------------------------
void Sphere::Draw()
{
	glColor3f(m_Color.R, m_Color.G, m_Color.B);

	if (m_WireFrame)
	{
		glutWireSphere(m_Radius, m_Slices, m_Stacks);
	}
	else
	{
		glutSolidSphere(m_Radius, m_Slices, m_Stacks);
	}
}
//================================================================================