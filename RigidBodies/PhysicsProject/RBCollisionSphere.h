//======================================================================
//File: RBCollisionSphere.h
//Author: Matt Struble
//======================================================================
#ifndef RB_COLLISION_SPHERE_H
#define RB_COLLISION_SPHERE_H
//=============================================================================
#pragma once
//=============================================================================
#include "RBCollisionPrimitive.h"
//=============================================================================
class RBCollisionSphere : public RBCollisionPrimitive
{
protected:
	float m_Radius;

public:
	RBCollisionSphere(RigidBody* rigidBody, float radius = 1, Matrix offset = Matrix());
	~RBCollisionSphere();

	inline void SetRadius(float radius) { m_Radius = radius; };
	inline float GetRadius() const { return m_Radius; };
};
#endif 

