//======================================================================
//File: RigidBodySystem.cpp
//Author: Matt Struble
//======================================================================
#include "RigidBodySystem.h"
#include "RBGroundContact.h"
#include "ConstantGravityForceGenerator.h"
#include "RBGameObjectContact.h"
#include "Sphere.h"
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

	Sphere* sphere = new Sphere(1, 36, 36);
	sphere->SetColor(Color::MAGENTA);

	RBGameObject* rbSphere = new RBGameObject();
	rbSphere->Initialize(Vector3D(0, 5, 5), 100, Color::MAGENTA);
	rbSphere->SetPrimitive(sphere);

	mp_RBGameObjects.push_back(rbSphere);

	handler->AddCollisionObject(rbSphere);
	handler->AddToRegistry(rbSphere, gravity);

	
	Sphere* sphere2 = new Sphere(1, 36, 36);
	sphere2->SetColor(Color::GREEN);

	RBGameObject* rbSphere2 = new RBGameObject();
	rbSphere2->Initialize(Vector3D(0, 10, 5.1), 100, Color::GREEN);
	rbSphere2->SetPrimitive(sphere2);

	mp_RBGameObjects.push_back(rbSphere2);

	handler->AddCollisionObject(rbSphere2);
	handler->AddToRegistry(rbSphere2, gravity);

	Sphere* sphere3 = new Sphere(1, 36, 36);
	sphere3->SetColor(Color::RED);

	RBGameObject* rbSphere3 = new RBGameObject();
	rbSphere3->Initialize(Vector3D(10, 10, 0), 100, Color::RED);
	rbSphere3->SetPrimitive(sphere3);

	mp_RBGameObjects.push_back(rbSphere3);

	handler->AddCollisionObject(rbSphere3);
	handler->AddToRegistry(rbSphere3, gravity);
	

	handler->AddContactGenerator(new RBGameObjectContact()); 
}

void RigidBodySystem::Draw()
{
	for (unsigned int i = 0; i < mp_RBGameObjects.size(); i++)
	{
		mp_RBGameObjects[i]->Draw();
	}
}