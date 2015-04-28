//======================================================================
//File: ConstantGravityForceGenerator.cpp
//Author: Matt Struble
//======================================================================
#include "ConstantGravityForceGenerator.h"
//======================================================================
ConstantGravityForceGenerator::ConstantGravityForceGenerator(const Vector3D& gravity)
:m_Gravity(gravity)
{

}

ConstantGravityForceGenerator::~ConstantGravityForceGenerator()
{

}

void ConstantGravityForceGenerator::UpdateForce(PhysicObject* object, float dt)
{
	object->AddForce(m_Gravity * object->GetMass());
}