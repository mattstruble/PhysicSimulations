//======================================================================
//File: PyramidMA.cpp
//Author: Matt Struble
//======================================================================
#include "PyramidMA.h"
//======================================================================
void PyramidMA::Initialize(Vector3D position, Color color, float size, float mass)
{
	m_Size = size;
	float dist = size / 2;

	GameObject* LBF = new GameObject();
	Vector3D LBFPos = Vector3D(position.X - dist, position.Y - dist, position.Z + dist);
	LBF->Initialize(LBFPos, mass, color);
	mp_GameObjects.push_back(LBF);

	GameObject* RBF = new GameObject();
	Vector3D RBFPos = Vector3D(position.X + dist, position.Y - dist, position.Z + dist);
	RBF->Initialize(RBFPos, mass, color);
	mp_GameObjects.push_back(RBF);

	GameObject* LBB = new GameObject();
	Vector3D LBBPos = Vector3D(position.X - dist, position.Y - dist, position.Z - dist);
	LBB->Initialize(LBBPos, mass, color);
	mp_GameObjects.push_back(LBB);

	GameObject* RBB = new GameObject();
	Vector3D RBBPos = Vector3D(position.X + dist, position.Y - dist, position.Z - dist);
	RBB->Initialize(RBBPos, mass, color);
	mp_GameObjects.push_back(RBB);

	GameObject* top = new GameObject();
	Vector3D topPos = Vector3D(position.X, position.Y + dist, position.Z);
	top->Initialize(topPos, mass, color);
	mp_GameObjects.push_back(top);

	createRodContact(LBF, RBF);
	createRodContact(LBF, LBB);
	createRodContact(RBF, RBB);
	createRodContact(RBB, LBB);
	createRodContact(RBB, top);
	createRodContact(LBB, top);
	createRodContact(LBF, top);
	createRodContact(RBF, top);

	createRodContact(LBB, RBF);
	createRodContact(LBF, RBB);
}