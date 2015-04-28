//======================================================================
//File: Plane.cpp
//Author: Matt Struble
//======================================================================
#include "Plane.h"
//======================================================================
Plane::Plane(Vector3D dimensions)
:m_Dimensions(dimensions)
{
	
}

Plane::~Plane()
{

}

void Plane::Draw()
{
	glColor3f(m_Color.R, m_Color.G, m_Color.B);

	glBegin(GL_QUADS);
	
	glVertex3f(-m_Dimensions.X, m_Dimensions.Y, -m_Dimensions.Z);
	glVertex3f(m_Dimensions.X, m_Dimensions.Y, -m_Dimensions.Z);
	glVertex3f(m_Dimensions.X, m_Dimensions.Y, m_Dimensions.Z);
	glVertex3f(-m_Dimensions.X, m_Dimensions.Y, m_Dimensions.Z);

	glEnd();
}