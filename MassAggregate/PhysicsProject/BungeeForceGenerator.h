//======================================================================
//File: BungeeForceGenerator.h
//Author: Matt Struble
//======================================================================
#ifndef BUNGEE_FORCE_GENERATOR_H
#define BUNGEE_FORCE_GENERATOR_H
//======================================================================
#pragma once
//======================================================================
#include "ForceGenerator.h"
//======================================================================
class BungeeForceGenerator : public ForceGenerator
{
public:
	BungeeForceGenerator(PhysicObject* endPosition, float k, float restLength);
	~BungeeForceGenerator();

	virtual void UpdateForce(PhysicObject* object, float dt);

private:
	PhysicObject* mp_EndPosition;
	float const m_K;
	float const m_RestLength;
};
#endif 