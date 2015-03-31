//======================================================================
//File: Contact.h
//Author: Matt Struble
//======================================================================
#ifndef CONTACT_H
#define CONTACT_H
//======================================================================
#pragma once
//======================================================================
#include "PhysicObject.h"
//======================================================================
class Contact
{

public:
	Contact() {};
	~Contact() {};

	void Resolve(float dt);

	float CalculateSeparatingVelocity() const;

	PhysicObject* Object[2];

	float Restitution;
	float Penetration;

	Vector3D ContactNormal;
	Vector3D ObjectMovement[2];

private:
	void resolveVelocity(float dt);
	void resolveInterpenetration(float dt);
};
#endif