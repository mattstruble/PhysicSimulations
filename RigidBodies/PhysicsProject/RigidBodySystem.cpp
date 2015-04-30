//======================================================================
//File: RigidBodySystem.cpp
//Author: Matt Struble
//======================================================================
#include "RigidBodySystem.h"
#include "RBGroundContact.h"
#include "ConstantGravityForceGenerator.h"
#include "Sphere.h"
//======================================================================
void RigidBodySystem::Initialize(PhysicObjectHandler* handler)
{
	mp_Handler = handler;

	Plane* groundPlane = new Plane(Vector3D(60, 1, 60));
	GameObject* ground = new GameObject();
	ground->Initialize(Vector3D(0, -1, 0));
	ground->SetPrimitive(groundPlane);

	handler->Add(ground);
	handler->AddContactGenerator(new RBGroundContact());

	ConstantGravityForceGenerator* gravity = new ConstantGravityForceGenerator(Vector3D(0, -9.8f, 0));

	Sphere* sphere = new Sphere(1, 36, 36);
	sphere->SetColor(Color::MAGENTA);

	RBGameObject* rbSphere = new RBGameObject();
	rbSphere->Initialize(Vector3D(0, 10, 0), 5, Color::MAGENTA);
	rbSphere->SetPrimitive(sphere);

	mp_RBGameObjects.push_back(rbSphere);

	handler->AddCollisionObject(rbSphere);
	handler->AddToRegistry(rbSphere, gravity);
}

void RigidBodySystem::Draw()
{
	for (unsigned int i = 0; i < mp_RBGameObjects.size(); i++)
	{
		mp_RBGameObjects[i]->Draw();
	}
}