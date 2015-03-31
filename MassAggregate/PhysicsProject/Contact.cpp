//======================================================================
//File: Contact.cpp
//Author: Matt Struble
//======================================================================
#include "Contact.h"
//======================================================================
void Contact::Resolve(float dt)
{
	resolveVelocity(dt);
	resolveInterpenetration(dt);
}

float Contact::CalculateSeparatingVelocity() const
{
	Vector3D relativeVel = Object[0]->GetVelocity();
	if (Object[1])
		relativeVel -= Object[1]->GetVelocity();
	return Vector3D::Dot(relativeVel, ContactNormal);
}

void Contact::resolveVelocity(float dt)
{
	float separatingVel = CalculateSeparatingVelocity();

	if (separatingVel > 0)
	{
		return;
	}

	float newSepVel = -separatingVel * Restitution;

	
	Vector3D accVel = Object[0]->GetAcceleration();
	if (Object[1]) accVel -= Object[1]->GetAcceleration();

	float accSepVel = Vector3D::Dot(accVel, ContactNormal) * dt;

	//Check for resting contact
	if (accSepVel < 0)
	{
		/*
		newSepVel += Restitution * accSepVel;

		if (newSepVel < 0) newSepVel = 0;*/
		separatingVel -= accSepVel;
	}

	float deltaVel = newSepVel - separatingVel;

	float totalInverseMass = Object[0]->GetInverseMass();
	if (Object[1])
		totalInverseMass += Object[1]->GetInverseMass();

	if (totalInverseMass <= 0) return;

	float impulse = deltaVel / totalInverseMass;

	Vector3D impulsePerMass = ContactNormal * impulse;

	Object[0]->SetVelocity(Object[0]->GetVelocity() + impulsePerMass * Object[0]->GetInverseMass());

	if (Object[1])
		Object[1]->SetVelocity(Object[1]->GetVelocity() + impulsePerMass * -Object[1]->GetInverseMass());
}

void Contact::resolveInterpenetration(float dt)
{
	if (Penetration <= 0) return;

	float totalInverseMass = Object[0]->GetInverseMass();
	if (Object[1])
		totalInverseMass += Object[1]->GetInverseMass();

	if (totalInverseMass <= 0) return;

	Vector3D movePerMass = ContactNormal * (Penetration / totalInverseMass);

	ObjectMovement[0] = movePerMass * Object[0]->GetInverseMass() * dt;

	if (Object[1])
	{
		ObjectMovement[1] = movePerMass * -Object[1]->GetInverseMass() * dt;
	}
	else
		ObjectMovement[1] = Vector3D::Zero;

	Object[0]->SetPosition(Object[0]->GetPosition() + ObjectMovement[0]);

	if (Object[1])
		Object[1]->SetPosition(Object[1]->GetPosition() + ObjectMovement[1]);
}