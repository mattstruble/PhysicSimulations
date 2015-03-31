//======================================================================
//File: AnchorSpringForceGenerator.cpp
//Author: Matt Struble
//======================================================================
#include "AnchorSpringForceGenerator.h"
#include <math.h>
//======================================================================
AnchorSpringForceGenerator::AnchorSpringForceGenerator(Vector3D endPosition, float k, float restLength)
	:m_EndPosition(endPosition),
	m_K(k),
	m_RestLength(restLength)
{

}

//--------------------------------------------------------------------------------
AnchorSpringForceGenerator::~AnchorSpringForceGenerator()
{

}

//--------------------------------------------------------------------------------
void AnchorSpringForceGenerator::UpdateForce(PhysicObject* object, float dt)
{
	Vector3D force;
	force = object->GetPosition();
	force -= m_EndPosition;

	float magnitude = force.Magnitude();
	magnitude = fabs(magnitude - m_RestLength);
	magnitude *= m_K;

	force.Normalize();
	force *= -magnitude;
	object->AddForce(force);
}