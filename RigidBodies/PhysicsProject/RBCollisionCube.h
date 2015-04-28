//======================================================================
//File: RBCollisionCube.h
//Author: Matt Struble
//======================================================================
#ifndef RB_COLLISION_BOX_H
#define RB_COLLISION_BOX_H
//=============================================================================
#pragma once
//=============================================================================
#include "RBCollisionPrimitive.h"
//=============================================================================
class RBCollisionCube :	public RBCollisionPrimitive
{
protected:
	Vector3D m_HalfSize;
	Vector3D m_Vertices[8];

public:
	RBCollisionCube(RigidBody* rigidBody, Vector3D halfSize, Matrix offset = Matrix());
	~RBCollisionCube();

	inline Vector3D GetHalfSize() const { return m_HalfSize; };
};
//=============================================================================
#endif COLLISION_BOX_H

