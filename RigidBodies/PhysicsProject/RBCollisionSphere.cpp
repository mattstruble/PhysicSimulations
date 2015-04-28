//======================================================================
//File: RBCollisionSphere.cpp
//Author: Matt Struble
//======================================================================
#include "RBCollisionSphere.h"
//=============================================================================
RBCollisionSphere::RBCollisionSphere(RigidBody* rigidBody, float radius, Matrix offset)
:RBCollisionPrimitive(rigidBody, offset)
{
	m_Radius = radius;
}

//-----------------------------------------------------------------------------
RBCollisionSphere::~RBCollisionSphere()
{
}