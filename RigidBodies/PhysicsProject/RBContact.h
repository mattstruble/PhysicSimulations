//======================================================================
//File: RBContact.h
//Author: Matt Struble
//Resource: https://github.com/idmillington/cyclone-physics
//======================================================================
#ifndef RB_CONTACT_H
#define RB_CONTACT_H
//=============================================================================
#pragma once
//=============================================================================
#include "Vector3D.h"
#include "RigidBody.h"
//=============================================================================
class RBContact
{

public:
	RBContact();
	~RBContact();

	void Initialize(RigidBody* rigidBodyOne, RigidBody* rigidBodyTwo, Vector3D contactPoint, Vector3D contactNormal, float penetration, float restitution, float friction);

	void CalculateInternals(float deltaTime);
	void CalculateDesiredDeltavelocity(float deltaTime);

	void MatchAwakeState();

	void ApplyPositionChange(Vector3D linearChange[2], Vector3D angularChange[2], float penetration);
	void ApplyVelocityChange(Vector3D velocityChange[2], Vector3D rotationChange[2]);

	void SetPenetration(float penetration) { m_Penetration = penetration; };
	float GetPenetration() { return m_Penetration; };

	inline Vector3D GetContactNormal() { return m_ContactNormal; };
	RigidBody* GetRigidBody(int index);
	Vector3D GetRelativeContactPosition(int index);

	inline float GetDesiredDeltaVelocity() { return m_DesiredDeltaVelocity; };

	inline void SetContactVelocity(Vector3D contactVelocity) { m_ContactVelocity = contactVelocity; };

	inline Vector3D GetContactVelocity() { return m_ContactVelocity; };
	inline Matrix GetContactToWorld() { return m_ContactToWorld; };

private:
	void calculateContactBasis();

	Vector3D calculateLocalVelocity(unsigned int rigidBodyIndex, float deltaTime);
	Vector3D calculateImpulse(Matrix* inverseInertiaTensor);
	Vector3D calculateFrictionImpulse(Matrix* inverseInertiaTensor);

	RigidBody* mp_RigidBodyOne;
	RigidBody* mp_RigidBodyTwo;

	Vector3D m_ContactPoint;
	Vector3D m_ContactNormal;
	Vector3D m_ContactVelocity;

	float m_Penetration;
	float m_Restitution;
	float m_Friction;
	float m_DesiredDeltaVelocity;

	Matrix m_ContactToWorld;

	Vector3D m_RelativeContactPositionOne;
	Vector3D m_RelativeContactPositionTwo;
};
#endif