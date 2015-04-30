//======================================================================
//File: RigidBodySystem.h
//Author: Matt Struble
//======================================================================
#ifndef RIGID_BODY_SYSTEM_H
#define RIGID_BODY_SYSTEM_H
//======================================================================
#pragma once
//======================================================================
#include <vector>
//======================================================================
#include "Plane.h"
#include "ForceGenerator.h"
#include "ForceRegistry.h"
#include "GravityForceGenerator.h"
#include "RigidBody.h"
#include "RBGameObject.h"
#include "PhysicObjectHandler.h"
#include "ContactGenerator.h"
#include "GameObject.h"
//======================================================================
class RigidBodySystem
{
public:
	RigidBodySystem() {};
	~RigidBodySystem() {};

	void Initialize(PhysicObjectHandler* handler);
	void Update(float dt) {};
	void Draw();
	void Reset() {};
	void Clear() {};

private:
	PhysicObjectHandler* mp_Handler;

	std::vector<RBGameObject*> mp_RBGameObjects;
};
#endif