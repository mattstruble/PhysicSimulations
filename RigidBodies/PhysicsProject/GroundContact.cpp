//======================================================================
//File: GroundContact.cpp
//Author: Matt Struble
//======================================================================
#include "GroundContact.h"
//======================================================================
GroundContact::GroundContact(float groundY)
{
	m_GroundY = groundY;
}

void GroundContact::AddContact(CollisionHandler* handler) const
{
	std::vector<PhysicObject*> objects = handler->GetPhysicObjects();

	std::vector<PhysicObject*>::iterator iter;

	for (iter = objects.begin(); iter != objects.end(); iter++)
	{
		float objectY = (*iter)->GetPosition().Y - (*iter)->GetRadius();
		
		if (objectY < m_GroundY)
		{

			float penetration = m_GroundY - objectY;

			Contact contact;

			contact.Object[0] = (*iter);
			contact.Object[1] = nullptr;
			contact.Penetration = penetration;
			contact.Restitution = (*iter)->GetRestitution();
			contact.ContactNormal = Vector3D(0, 1, 0);

			handler->AddContact(contact);
		}
	}
}