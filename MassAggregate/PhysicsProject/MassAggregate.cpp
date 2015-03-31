//======================================================================
//File: MassAggregate.cpp
//Author: Matt Struble
//======================================================================
#include "MassAggregate.h"
#include "Sphere.h"
#include "RodLink.h"
#include "CableLink.h"
//======================================================================
void MassAggregate::Initialize(Vector3D position, float mass)
{
	GameObject* object = new GameObject();
	object->Initialize(position, mass);
	object->SetPrimitive(new Sphere(1, 36, 36));
	mp_GameObjects.push_back(object);
}

void MassAggregate::Update(float dt)
{
	std::vector<GameObject*>::iterator iter;
	for (iter = mp_GameObjects.begin(); iter != mp_GameObjects.end(); iter++)
	{
		(*iter)->Update(dt);
	}
}

void MassAggregate::Draw()
{
	std::vector<GameObject*>::iterator iter;
	for (iter = mp_GameObjects.begin(); iter != mp_GameObjects.end(); iter++)
	{
		(*iter)->Draw();
	}
}

void MassAggregate::Clear()
{
	std::vector<GameObject*>::iterator iter;
	for (iter = mp_GameObjects.begin(); iter != mp_GameObjects.end(); iter++)
	{
		(*iter)->Clear();
		delete (*iter);
		(*iter) = nullptr;
	}

	mp_GameObjects.clear();
}

void MassAggregate::Reset()
{
	std::vector<GameObject*>::iterator iter;
	for (iter = mp_GameObjects.begin(); iter != mp_GameObjects.end(); iter++)
	{
		(*iter)->Reset();
	}

	//mp_ContactGenerators.clear();

	//generateContacts();
}

void MassAggregate::createRodContact(GameObject* one, GameObject* two)
{
	float distance = Vector3D::Distance(one->GetPosition(), two->GetPosition());

	mp_ContactGenerators.push_back(new RodLink(one, two, distance));
}

void MassAggregate::createCableContact(GameObject* one, GameObject* two)
{
	float distance = Vector3D::Distance(one->GetPosition(), two->GetPosition());

	mp_ContactGenerators.push_back(new CableLink(one, two, distance));
}