//======================================================================
//File: RodLink.cpp
//Author: Matt Struble
//======================================================================
#include "RodLink.h"
//======================================================================
RodLink::RodLink(PhysicObject* one, PhysicObject* two, float length)
{
	Object[0] = one;
	Object[1] = two;

	MaxLength = length;
}

void RodLink::AddContact(CollisionHandler* handler) const
{
	float currLen = currentLength();

	if (currLen == MaxLength)	return;

	Contact contact;

	contact.Object[0] = Object[0];
	contact.Object[1] = Object[1];

	Vector3D normal = Object[1]->GetPosition() - Object[0]->GetPosition();
	normal.Normalize();

	if (currLen > MaxLength)
	{
		contact.ContactNormal = normal;
		contact.Penetration = currLen - MaxLength;
	}
	else
	{
		contact.ContactNormal = -normal;
		contact.Penetration = MaxLength - currLen;
	}

	contact.Restitution = 0;

	handler->AddContact(contact);
}
