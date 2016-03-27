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

	ConstantGravityForceGenerator* gravity = new ConstantGravityForceGenerator(Vector3D(0, -9.8f, 0));

	for (int i = 0; i < 15; i++)
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
	}

	/*
	Sphere* sphere = new Sphere(1, 36, 36);
	sphere->SetColor(Color::MAGENTA);

	RBGameObject* rbSphere = new RBGameObject();
	rbSphere->Initialize(Vector3D(0, 5, 0), 1, Color::MAGENTA);
	rbSphere->SetPrimitive(sphere);

	mp_RBGameObjects.push_back(rbSphere);

	handler->AddCollisionObject(rbSphere);
	handler->AddToRegistry(rbSphere, gravity);

	
	Sphere* sphere2 = new Sphere(1, 36, 36);
	sphere2->SetColor(Color::GREEN);

	RBGameObject* rbSphere2 = new RBGameObject();
	rbSphere2->Initialize(Vector3D(0, 10, 0), 1, Color::GREEN);
	rbSphere2->SetPrimitive(sphere2);

	mp_RBGameObjects.push_back(rbSphere2);

	handler->AddCollisionObject(rbSphere2);
	handler->AddToRegistry(rbSphere2, gravity);

	Sphere* sphere3 = new Sphere(1, 36, 36);
	sphere3->SetColor(Color::RED);

	RBGameObject* rbSphere3 = new RBGameObject();
	rbSphere3->Initialize(Vector3D(10, 5, 0), 1, Color::RED);
	rbSphere3->SetPrimitive(sphere3);

	mp_RBGameObjects.push_back(rbSphere3);

	handler->AddCollisionObject(rbSphere3);
	handler->AddToRegistry(rbSphere3, gravity);

	Sphere* sphere4 = new Sphere(1, 36, 36);
	sphere4->SetColor(Color::ORANGE);

	RBGameObject* rbSphere4 = new RBGameObject();
	rbSphere4->Initialize(Vector3D(10.1, 10, 0), 1, Color::ORANGE);
	rbSphere4->SetPrimitive(sphere4);

	mp_RBGameObjects.push_back(rbSphere4);

	handler->AddCollisionObject(rbSphere4);
	handler->AddToRegistry(rbSphere4, gravity);
	
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

void RigidBodySystem::Draw()
{
	for (unsigned int i = 0; i < mp_RBGameObjects.size(); i++)
	{
		mp_RBGameObjects[i]->Draw();
	}
}