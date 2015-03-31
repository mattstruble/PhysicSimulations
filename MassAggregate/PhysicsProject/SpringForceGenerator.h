//======================================================================
//File: SpringForceGenerator.h
//Author: Matt Struble
//======================================================================
#ifndef SPRING_FORCE_GENERATOR_H
#define SPRING_FORCE_GENERATOR_H
//======================================================================
#pragma once
//======================================================================
#include "ForceGenerator.h"
//======================================================================
class SpringForceGenerator : public ForceGenerator
{
public:
	SpringForceGenerator(PhysicObject* endPosition, float k, float restLength);
	~SpringForceGenerator();

	virtual void UpdateForce(PhysicObject* object, float dt);

private:
	PhysicObject* mp_EndPosition;
	float const m_K;
	float const m_RestLength;
};
#endif