//======================================================================
//File: RBCollisionPrimitive.h
//Author: Matt Struble
//======================================================================
#ifndef RB_COLLISION_PRIMITIVE_H
#define RB_COLLISION_PRIMITIVE_H
//=============================================================================
#pragma once
//=============================================================================
#include "Matrix.h"
//=============================================================================
class RigidBody;
//=============================================================================
class RBCollisionPrimitive
{
protected:
	RigidBody* mp_RigidBody;

	Matrix m_Offset;
	Matrix m_Transform;

public:
	RBCollisionPrimitive(RigidBody* rigidBody, Matrix offset = Matrix());
	~RBCollisionPrimitive();

	void CalculateInternals();

	inline Vector3D GetAxis(unsigned int index) const { return m_Transform.GetAxisVector(index); };
	inline Matrix GetTransform() const { return m_Transform; };
	inline RigidBody* GetRigidBody() const { return mp_RigidBody; };
};
#endif 