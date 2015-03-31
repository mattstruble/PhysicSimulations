//======================================================================
//File: CollisionHandler.h
//Author: Matt Struble
//======================================================================
#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H
//======================================================================
#pragma once
//======================================================================
#include "Contact.h"
#include <vector>
//======================================================================
class PhysicObject;
class ContactGenerator;
//======================================================================
class CollisionHandler
{
public:
	CollisionHandler();
	~CollisionHandler();

	void Initialize();
	void Update(float dt);
	void Reset();
	void Clear();

	void AddCollisionObject(PhysicObject* object);
	void AddCollisionObject(std::vector<PhysicObject*> objects);

	void AddContactGenerator(ContactGenerator* generator);
	void AddContactGenerator(std::vector<ContactGenerator*> generators);

	void AddContact(Contact contact) { m_Contacts.push_back(contact); };
	
	bool Remove(PhysicObject* object);

	const std::vector<PhysicObject*>& GetPhysicObjects() const { return mp_PhysicObjects; };

	inline int GetCollisions() { return m_Collisions; };

private:
	int collisions();
	void resolveContacts(float dt);

	std::vector<PhysicObject*> mp_PhysicObjects;
	std::vector<ContactGenerator*> mp_ContactGenerators;
	std::vector<Contact> m_Contacts;

	int m_MaxIterations;
	int m_Collisions;
};
#endif