//======================================================================
//File: CubeMA.cpp
//Author: Matt Struble
//======================================================================
#include "CubeMA.h"
//======================================================================
void CubeMA::Initialize(Vector3D position, Color color, float size, float mass)
{
	m_Size = size;
	float dist = size / 2;

	GameObject* LTF = new GameObject();
	Vector3D LTFPos = Vector3D(position.X - dist, position.Y + dist, position.Z + dist);
	LTF->Initialize(LTFPos, mass, color);
	mp_GameObjects.push_back(LTF);

	GameObject* RTF = new GameObject();
	Vector3D RTFPos = Vector3D(position.X + dist, position.Y + dist, position.Z + dist);
	RTF->Initialize(RTFPos, mass, color);
	mp_GameObjects.push_back(RTF);

	GameObject* LTB = new GameObject();
	Vector3D LTBPos = Vector3D(position.X - dist, position.Y + dist, position.Z - dist);
	LTB->Initialize(LTBPos, mass, color);
	mp_GameObjects.push_back(LTB);

	GameObject* RTB = new GameObject();
	Vector3D RTBPos = Vector3D(position.X + dist, position.Y + dist, position.Z - dist);
	RTB->Initialize(RTBPos, mass, color);
	mp_GameObjects.push_back(RTB);

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

	createRodContact(LTF, RTF);
	createRodContact(LTF, LBF);
	createRodContact(LTF, LTB);
	createRodContact(RTF, RBF);
	createRodContact(RTF, RTB);
	createRodContact(LBF, RBF);
	createRodContact(LBF, LBB);
	createRodContact(RBF, RBB);
	createRodContact(LTB, LBB);
	createRodContact(LTB, RTB);
	createRodContact(RTB, RBB);
	createRodContact(RBB, LBB);

	createRodContact(LTF, RTB);
	createRodContact(RTF, LTB);
	createRodContact(LBF, RBB);
	createRodContact(RBF, LBB);

	createRodContact(LTF, LBB);
	createRodContact(LBF, LTB);
	createRodContact(RTF, RBB);
	createRodContact(RBF, RTB);
}