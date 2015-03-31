//======================================================================
//File: CollisionHandler.cpp
//Author: Matt Struble
//======================================================================
#include "CollisionHandler.h"
#include "ContactGenerator.h"
//======================================================================
CollisionHandler::CollisionHandler()
{
	m_MaxIterations = 5;
	m_Collisions = 0;
}

CollisionHandler::~CollisionHandler()
{
	Clear();
}

void CollisionHandler::Initialize()
{
}

void CollisionHandler::Update(float dt)
{
	int iterations = collisions();

	m_Collisions = m_Contacts.size();

	if (iterations > m_MaxIterations)
	{
		iterations = m_MaxIterations;
	}

	for (int i = 0; i < iterations; i++)
	{
		collisions();
		resolveContacts(dt);
	}
}

void CollisionHandler::Reset()
{
	
}

void CollisionHandler::Clear()
{
	m_Contacts.clear();
	mp_ContactGenerators.clear();
}

void CollisionHandler::AddCollisionObject(PhysicObject* object)
{
	mp_PhysicObjects.push_back(object);
}

void CollisionHandler::AddCollisionObject(std::vector<PhysicObject*> objects)
{
	std::vector<PhysicObject*>::iterator iter;
	for (iter = objects.begin(); iter != objects.end(); iter++)
	{
		mp_PhysicObjects.push_back(*iter);
	}
}

void CollisionHandler::AddContactGenerator(ContactGenerator* generator)
{
	mp_ContactGenerators.push_back(generator);
}

void CollisionHandler::AddContactGenerator(std::vector<ContactGenerator*> generators)
{
	std::vector<ContactGenerator*>::iterator iter;
	for (iter = generators.begin(); iter != generators.end(); iter++)
	{
		mp_ContactGenerators.push_back(*iter);
	}
}

bool CollisionHandler::Remove(PhysicObject* object)
{
	for (unsigned int i = 0; i < mp_PhysicObjects.size(); i++)
	{
		if (object == mp_PhysicObjects[i])
		{
			delete object;
			mp_PhysicObjects.erase(mp_PhysicObjects.begin() + i);
			return true;
		}
	}

	return false;
}

int CollisionHandler::collisions()
{
	int count = 0;

	std::vector<ContactGenerator*>::iterator iter;
	for (iter = mp_ContactGenerators.begin(); iter != mp_ContactGenerators.end(); iter++)
	{
		(*iter)->AddContact(this);
		count++;
	}

	return count;
}

void CollisionHandler::resolveContacts(float dt)
{
	std::vector<Contact>::iterator iter;
	for (iter = m_Contacts.begin(); iter != m_Contacts.end(); iter++)
	{
		(*iter).Resolve(dt);
	}

	m_Contacts.clear();
}