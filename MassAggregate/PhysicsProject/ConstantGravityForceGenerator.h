//======================================================================
//File: ConstantGravityForceGenerator.h
//Author: Matt Struble
//======================================================================
#ifndef CONSTANT_GRAVITY_FORCE_GENERATOR_H
#define CONSTANT_GRAVITY_FORCE_GENERATOR_H
//======================================================================
#pragma once
//======================================================================
#include "ForceGenerator.h"
//======================================================================
class ConstantGravityForceGenerator : public ForceGenerator
{
public: 
	ConstantGravityForceGenerator(const Vector3D& gravity);
	~ConstantGravityForceGenerator();

	virtual void UpdateForce(PhysicObject* object, float dt) override;

private:
	Vector3D m_Gravity;
};
#endif