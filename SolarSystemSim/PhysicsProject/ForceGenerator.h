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
//======================================================================

class ForceGenerator
{
public:
	ForceGenerator() {};
	~ForceGenerator() {};

	virtual void UpdateForce(PhysicObject* object, float dt) = 0;
};
#endif