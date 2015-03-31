//======================================================================
//File: AnchorBungeeForceGenerator.cpp
//Author: Matt Struble
//======================================================================
#include "AnchorBungeeForceGenerator.h"
#include <math.h>
//======================================================================
AnchorBungeeForceGenerator::AnchorBungeeForceGenerator(Vector3D endPosition, float k, float restLength)
	:m_EndPosition(endPosition),
	m_K(k),
	m_RestLength(restLength)
{

}

//--------------------------------------------------------------------------------
AnchorBungeeForceGenerator::~AnchorBungeeForceGenerator()
{

}

//--------------------------------------------------------------------------------
void AnchorBungeeForceGenerator::UpdateForce(PhysicObject* object, float dt)
{
	Vector3D force;
	force = object->GetPosition();
	force -= m_EndPosition;

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