//======================================================================
//File: SpringForceGenerator.cpp
//Author: Matt Struble
//======================================================================
#include "SpringForceGenerator.h"
#include <math.h>
//======================================================================
SpringForceGenerator::SpringForceGenerator(PhysicObject* endPosition, float k, float restLength)
	:mp_EndPosition(endPosition),
	m_K(k),
	m_RestLength(restLength)
{

}

//--------------------------------------------------------------------------------
SpringForceGenerator::~SpringForceGenerator()
{

}

//--------------------------------------------------------------------------------
void SpringForceGenerator::UpdateForce(PhysicObject* object, float dt)
{
	Vector3D force;
	force = object->GetPosition();
	force -= mp_EndPosition->GetPosition();

	float magnitude = force.Magnitude();
	magnitude = m_K * (magnitude - m_RestLength);

	force.Normalize();
	force *= -magnitude; 
	object->AddForce(force);
}