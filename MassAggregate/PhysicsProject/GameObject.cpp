//======================================================================
//File: GameObject.cpp
//Author: Matt Struble
//======================================================================
#include "GameObject.h"
#include "Sphere.h"
//======================================================================
GameObject::GameObject()
{
	m_Primitive = new Sphere(1, 36, 36);
	m_Radius = 1;
	m_Restitution = 0.5f;
}

GameObject::~GameObject()
{
	delete m_Primitive;
	m_Primitive = nullptr;
}

void GameObject::Initialize(Vector3D position, float mass, Color color)
{
	PhysicObject::Initialize(mass, position);

	m_Primitive->SetColor(color);
}

void GameObject::Draw()
{
	glPushMatrix();

	glTranslatef(m_Position.X, m_Position.Y, m_Position.Z);
	m_Primitive->Draw();
	glPopMatrix();
}