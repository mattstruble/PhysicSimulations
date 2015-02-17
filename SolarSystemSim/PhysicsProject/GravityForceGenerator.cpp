//======================================================================
//File: GravityForceGenerator.cpp
//Author: Matt Struble
//======================================================================
#include "GravityForceGenerator.h"
#include <math.h>
//======================================================================
double const GravityForceGenerator::GRAVITY = 6.67384e-20; 
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
			double distanceSQ = static_cast<double>(Vector3D::DistanceSQ(object->GetPosition(), (*it)->GetPosition()));

			double mass = static_cast<double>(object->GetMass()) * static_cast<double>((*it)->GetMass());

			double force = GRAVITY * (mass / distanceSQ);

			Vector3D gravity = (*it)->GetPosition() - object->GetPosition();
			gravity.Normalize();
			gravity *= force;

			object->AddForce(gravity);
		}
	}
}
//================================================================================