//======================================================================
//File: GameObject.h
//Author: Matt Struble
//======================================================================
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
//======================================================================
#pragma once
//======================================================================
#include "PhysicObject.h"
#include "Primitive.h"
//======================================================================
class GameObject : public PhysicObject
{
public:
	GameObject();
	~GameObject();

	void Initialize(Vector3D position, float mass = 1, Color color = Color::GREY);

	inline void SetPrimitive(Primitive* primitive) { m_Primitive = primitive; };
	inline Primitive* GetPrimitive() { return m_Primitive; };

	inline void SetColor(Color c) { m_Primitive->SetColor(c); };

	virtual void Draw();

protected:
	Primitive* m_Primitive;
};
#endif