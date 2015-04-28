//======================================================================
//File: AnchorBungeeForceGenerator.h
//Author: Matt Struble
//======================================================================
#ifndef ANCHOR_BUNGEE_FORCE_GENERATOR_H
#define ANCHOR_BUNGEE_FORCE_GENERATOR_H
//======================================================================
#pragma once
//======================================================================
#include "ForceGenerator.h"
//======================================================================
class AnchorBungeeForceGenerator : public ForceGenerator
{
public:
	AnchorBungeeForceGenerator(Vector3D endPosition, float k, float restLength);
	~AnchorBungeeForceGenerator();

	virtual void UpdateForce(PhysicObject* object, float dt);

private:
	Vector3D m_EndPosition;
	float const m_K;
	float const m_RestLength;
};
#endif 