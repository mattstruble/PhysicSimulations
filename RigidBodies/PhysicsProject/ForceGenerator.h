//======================================================================
//File: ForceGenerator.h
//Author: Matt Struble
//======================================================================
#ifndef FORCE_GENERATOR_H
#define FORCE_GENERATOR_H
//======================================================================
#pragma once
//======================================================================
#include "PhysicObject.h"
#include "RigidBody.h"
//======================================================================

class ForceGenerator
{
public:
	ForceGenerator() {};
	~ForceGenerator() {};

	virtual void UpdateForce(PhysicObject* object, float dt) = 0;
	virtual void UpdateForce(RigidBody* rigidBody, float dt) {};
};
#endif