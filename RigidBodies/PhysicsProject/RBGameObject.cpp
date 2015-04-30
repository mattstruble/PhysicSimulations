//======================================================================
//File: RBGameObject.cpp
//Author: Matt Struble
//======================================================================
#include "RBGameObject.h"
#include "Sphere.h"
#include "Cube.h"
//======================================================================
RBGameObject::RBGameObject()
{
	mp_Primitive = new Sphere(1, 36, 36);
}

RBGameObject::~RBGameObject()
{
	delete mp_Primitive;
	mp_Primitive = nullptr;
}

void RBGameObject::Initialize(Vector3D position, float mass, Color color)
{
	RigidBody::Initialize(mass, position);

	mp_Primitive->SetColor(color);
}

void RBGameObject::Draw()
{
	glPushMatrix();

	glTranslatef(m_Position.X, m_Position.Y, m_Position.Z);
	glRotatef(m_Orientation.R, m_Orientation.I, m_Orientation.J, m_Orientation.K);

	mp_Primitive->Draw();

	glPopMatrix();
}