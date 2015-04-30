//======================================================================
//File: RBGameObject.h
//Author: Matt Struble
//======================================================================
#ifndef RB_GAME_OBJECT_H
#define RB_GAME_OBJECT_H
//======================================================================
#pragma once
//======================================================================
#include "RigidBody.h"
#include "Primitive.h"
//======================================================================
class RBGameObject : public RigidBody
{
public:
	RBGameObject();
	~RBGameObject();

	void Initialize(Vector3D position, float mass = 1, Color color = Color::GREY);

	inline void SetPrimitive(Primitive* primitive) { mp_Primitive = primitive; };
	inline Primitive* GetPrimitive() { return mp_Primitive; };

	inline void SetColor(Color c) { mp_Primitive->SetColor(c); };
	inline void SetCollisionType(e_CollisionType type) { m_CollisionType = type; };

	virtual void Draw();

protected:
	Primitive* mp_Primitive;
};
#endif