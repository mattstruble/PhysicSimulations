//======================================================================
//File: RBCollisionPlane.h
//Author: Matt Struble
//======================================================================
#ifndef RB_COLLISION_PLANE_H
#define RB_COLLISION_PLANE_H
//======================================================================
#pragma once
//======================================================================
#include "Vector3D.h"
//======================================================================
class CollisionPlane
{
public:
	CollisionPlane() {};
	~CollisionPlane() {};

	inline void SetDirection(Vector3D direction) { m_Direction = direction; };
	inline Vector3D GetDirection() const { return m_Direction; };

	inline void SetOffset(float offset) { m_Offset = offset; };
	inline float GetOffset() const { return m_Offset; };

private:
	Vector3D m_Direction;

	float m_Offset;
};
#endif