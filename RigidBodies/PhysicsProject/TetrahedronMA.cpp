//======================================================================
//File: TetrahedronMA.cpp
//Author: Matt Struble
//======================================================================
#include "TetrahedronMA.h"
//======================================================================
void TetrahedronMA::Initialize(Vector3D position, Color color, float size, float mass)
{
	m_Size = size;
	float dist = size / 2;

	GameObject* front = new GameObject();
	Vector3D frontPos = Vector3D(position.X, position.Y - dist, position.Z + dist);
	front->Initialize(frontPos, mass, color);
	mp_GameObjects.push_back(front);

	GameObject* left = new GameObject();
	Vector3D leftPos = Vector3D(position.X - dist, position.Y - dist, position.Z - dist);
	left->Initialize(leftPos, mass, color);
	mp_GameObjects.push_back(left);

	GameObject* right = new GameObject();
	Vector3D rightPos = Vector3D(position.X + dist, position.Y - dist, position.Z - dist);
	right->Initialize(rightPos, mass, color);
	mp_GameObjects.push_back(right);

	GameObject* top = new GameObject();
	Vector3D topPos = Vector3D(position.X, position.Y + dist, position.Z);
	top->Initialize(topPos, mass, color);
	mp_GameObjects.push_back(top);

	createRodContact(front, left);
	createRodContact(front, right);
	createRodContact(front, top);
	createRodContact(left, right);
	createRodContact(left, top);
	createRodContact(top, right);
}