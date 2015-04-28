//======================================================================
//File: AnchorSpringForceGenerator.h
//Author: Matt Struble
//======================================================================
#ifndef ANCHOR_SPRING_FORCE_GENERATOR_H
#define ANCHOR_SPRING_FORCE_GENERATOR_H
//======================================================================
#pragma once
//======================================================================
#include "ForceGenerator.h"
//======================================================================
class AnchorSpringForceGenerator : public ForceGenerator
{
public:
	AnchorSpringForceGenerator(Vector3D endPosition, float k, float restLength);
	~AnchorSpringForceGenerator();

	virtual void UpdateForce(PhysicObject* object, float dt);

private:
	Vector3D m_EndPosition;
	float const m_K;
	float const m_RestLength;
};
#endif