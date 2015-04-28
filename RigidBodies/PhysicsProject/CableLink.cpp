//======================================================================
//File: CableLink.cpp
//Author: Matt Struble
//======================================================================
#include "CableLink.h"
//======================================================================
CableLink::CableLink(PhysicObject* one, PhysicObject* two, float length, float restitution)
{
	Object[0] = one;
	Object[1] = two;

	MaxLength = length;
	Restitution = restitution;
}

void CableLink::AddContact(CollisionHandler* handler) const
{
	float length = currentLength();

	if (length < MaxLength) return;

	Contact contact;

	contact.Object[0] = Object[0];
	contact.Object[1] = Object[1];

	Vector3D normal = Object[1]->GetPosition() - Object[0]->GetPosition();
	normal.Normalize();

	contact.ContactNormal = normal;

	contact.Penetration = length - MaxLength;
	contact.Restitution = Restitution;

	handler->AddContact(contact);
}