//======================================================================
//File: GravityForceGenerator.h
//Author: Matt Struble
//======================================================================
#ifndef GRAVITY_FORCE_GENERATOR_H
#define GRAVITY_FORCE_GENERATOR_H
//======================================================================
#pragma once
//======================================================================
#include "ForceGenerator.h"
#include "PhysicObjectHandler.h"
//======================================================================
class GravityForceGenerator : public ForceGenerator
{
public:
	GravityForceGenerator(PhysicObjectHandler* physicObjects);
	~GravityForceGenerator();

	virtual void UpdateForce(PhysicObject* object, float dt) override;

private:
	static const float GRAVITY;
	PhysicObjectHandler* mp_PhysicObjects;
};
#endif