//======================================================================
//File: RBCollisionPrimitive..cpp
//Author: Matt Struble
//======================================================================
#include "RBCollisionPrimitive.h"
#include "RigidBody.h"
//=============================================================================
RBCollisionPrimitive::RBCollisionPrimitive(RigidBody* rigidBody, Matrix offset)
{
	mp_RigidBody = rigidBody;
	m_Offset = offset;

	CalculateInternals();
}

//-----------------------------------------------------------------------------
RBCollisionPrimitive::~RBCollisionPrimitive()
{
}

void RBCollisionPrimitive::CalculateInternals()
{
	m_Transform = mp_RigidBody->GetTransform() * m_Offset;
}
//=============================================================================