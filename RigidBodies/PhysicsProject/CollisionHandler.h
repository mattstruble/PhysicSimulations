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
#include "RBContact.h"
#include <vector>
//======================================================================
class PhysicObject;
class RigidBody;
class ContactGenerator;
class RBCollisionDetector;
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
	void AddCollisionObject(RigidBody* rigidBody);
	void AddCollisionObjects(std::vector<RigidBody*> rigidBodies);

	void AddContactGenerator(ContactGenerator* generator);
	void AddContactGenerator(std::vector<ContactGenerator*> generators);

	void AddContact(Contact contact) { m_Contacts.push_back(contact); };
	
	bool Remove(PhysicObject* object);

	const std::vector<PhysicObject*>& GetPhysicObjects() const { return mp_PhysicObjects; };
	const std::vector<RigidBody*>& GetRigidBodies() { return mp_RigidBodies; };

	inline int GetCollisions() { return m_Collisions; };

	inline RBCollisionDetector* GetRBCollisionDetector() { return mp_RBCollisionDetector; };

private:
	int collisions();
	void resolveContacts(float dt);
	void resolveRBContacts(float deltaTime);

	void setRBContacts(float deltaTime);
	void adjustPositions(float deltaTime);
	void adjustVelocities(float deltaTime);

	std::vector<PhysicObject*> mp_PhysicObjects;
	std::vector<RigidBody*> mp_RigidBodies;
	std::vector<ContactGenerator*> mp_ContactGenerators;
	std::vector<ContactGenerator*> mp_RBContactGenerators;
	std::vector<Contact> m_Contacts;
	std::vector<RBContact> m_RBContacts;

	RBCollisionDetector* mp_RBCollisionDetector;

	int m_MaxIterations;
	int m_Collisions;

	int m_MaxPosIterations;
	int m_PosIterations;
	int m_MaxVelIterations;
	int m_VelIterations;

	float m_Restitution;
	float m_Friction;

	float m_PositionEpsilon;
	float m_VelocityEpsilon;
};
#endif