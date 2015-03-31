//======================================================================
//File: BungeeForceGenerator.cpp
//Author: Matt Struble
//======================================================================
#include "BungeeForceGenerator.h"
#include <math.h>
//======================================================================
BungeeForceGenerator::BungeeForceGenerator(PhysicObject* endPosition, float k, float restLength)
	:mp_EndPosition(endPosition),
	m_K(k),
	m_RestLength(restLength)
{

}

//--------------------------------------------------------------------------------
BungeeForceGenerator::~BungeeForceGenerator()
{

}

//--------------------------------------------------------------------------------
void BungeeForceGenerator::UpdateForce(PhysicObject* object, float dt)
{
	Vector3D force;
	force = object->GetPosition();
	force -= mp_EndPosition->GetPosition();

	float magnitude = force.Magnitude();
	if (magnitude <= m_RestLength)
	{
		return;
	}

	magnitude = m_K * (magnitude - m_RestLength);
	force.Normalize();
	force *= -magnitude;
	object->AddForce(force);
}