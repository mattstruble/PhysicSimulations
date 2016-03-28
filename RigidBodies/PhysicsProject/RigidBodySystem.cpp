//======================================================================
//File: RigidBodySystem.cpp
//Author: Matt Struble
//======================================================================
#include "RigidBodySystem.h"
#include "RBGroundContact.h"
#include "ConstantGravityForceGenerator.h"
#include "RBGameObjectContact.h"
#include "Sphere.h"
#include "Cube.h"
//======================================================================
void RigidBodySystem::Initialize(PhysicObjectHandler* handler)
{
	mp_Handler = handler;

	Plane* groundPlane = new Plane(Vector3D(60, 3, 60));
	GameObject* ground = new GameObject();
	ground->Initialize(Vector3D(0, -3, 0));
	ground->SetPrimitive(groundPlane);

	handler->Add(ground);
	handler->AddContactGenerator(new RBGroundContact());
	/*
	ConstantGravityForceGenerator* gravity = new ConstantGravityForceGenerator(Vector3D(0, -9.8f, 0));

	for (int i = 0; i < 10; i++)
	{
		Color c = Color(rand() % 256, rand() % 256, rand() % 256);
		c.ConvertToDecimal();

		Sphere* sphere = new Sphere(1, 36, 36);
		sphere->SetColor(c);

		RBGameObject* rbSphere = new RBGameObject();
		rbSphere->Initialize(Vector3D(rand() % 10 + 1, rand() % 10 + 1, rand() % 10 + 1), 1, c);
		rbSphere->SetPrimitive(sphere);

		mp_RBGameObjects.push_back(rbSphere);

		handler->AddCollisionObject(rbSphere);
		handler->AddToRegistry(rbSphere, gravity);
	}*/
	/*
	Cube* cube1 = new Cube(2);
	cube1->SetColor(Color::AZURE);

	RBGameObject* rbCube1 = new RBGameObject();
	rbCube1->Initialize(Vector3D(10, 6, 10), 1, Color::AZURE);
	rbCube1->SetPrimitive(cube1);
	rbCube1->SetCollisionType(e_CollisionType::CUBE);

	mp_RBGameObjects.push_back(rbCube1);

	handler->AddCollisionObject(rbCube1);
	handler->AddToRegistry(rbCube1, gravity);
	*/

	handler->AddContactGenerator(new RBGameObjectContact()); 
}

void RigidBodySystem::Spawn(int num)
{
	ConstantGravityForceGenerator* gravity = new ConstantGravityForceGenerator(Vector3D(0, -9.8f, 0));

	for (int i = 0; i < num; i++)
	{
		Color c = Color(rand() % 256, rand() % 256, rand() % 256);
		c.ConvertToDecimal();

		Sphere* sphere = new Sphere(1, 36, 36);
		sphere->SetColor(c);

		RBGameObject* rbSphere = new RBGameObject();
		rbSphere->Initialize(Vector3D(rand() % 10 + 1, rand() % 10 + 1, rand() % 10 + 1), 1, c);
		rbSphere->SetPrimitive(sphere);

		mp_RBGameObjects.push_back(rbSphere);

		mp_Handler->AddCollisionObject(rbSphere);
		mp_Handler->AddToRegistry(rbSphere, gravity);
	}
}

void RigidBodySystem::Draw()
{
	for (unsigned int i = 0; i < mp_RBGameObjects.size(); i++)
	{
		mp_RBGameObjects[i]->Draw();
	}
}