//======================================================================
//File: GravityForceGenerator.cpp
//Author: Matt Struble
//======================================================================
#include "GravityForceGenerator.h"
#include <math.h>
//======================================================================
float const GravityForceGenerator::GRAVITY = 6.67384e-20f; 
//======================================================================
GravityForceGenerator::GravityForceGenerator(PhysicObjectHandler* physicObjects)
{
	mp_PhysicObjects = physicObjects;
}

//--------------------------------------------------------------------------------
GravityForceGenerator::~GravityForceGenerator()
{

}

//--------------------------------------------------------------------------------
void GravityForceGenerator::UpdateForce(PhysicObject* object, float dt)
{ 
	
	for (auto it = mp_PhysicObjects->GetPhysicObjects().cbegin(); it != mp_PhysicObjects->GetPhysicObjects().cend(); ++it)
	{
		if (object != (*it))
		{
			float distanceSQ = Vector3D::DistanceSQ(object->GetPosition(), (*it)->GetPosition());

			float mass = object->GetMass() * (*it)->GetMass();

			float force = GRAVITY * (mass / distanceSQ);

			Vector3D gravity = (*it)->GetPosition() - object->GetPosition();
			gravity.Normalize();
			gravity *= force;

			object->AddForce(gravity);
		}
	}
}
//================================================================================