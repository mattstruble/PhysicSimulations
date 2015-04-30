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

	void UpdateForce(PhysicObject* object, float dt);
	void UpdateForce(RigidBody* rigidBody, float dt);
private:
	Vector3D m_Gravity;
};
#endif