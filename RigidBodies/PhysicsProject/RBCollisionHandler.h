//======================================================================
//File: RBCollisionDetector.h
//Author: Matt Struble
//======================================================================
#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H
//======================================================================
#pragma once
//======================================================================
#include <vector>
#include "Contact.h"
#include "RBContact.h"
//======================================================================
class PhysicsObject;
class RigidBody;
class ContactGenerator;
class CollisionDetector;
class RigidContactGenerator;
//======================================================================
class CollisionHandler
{
public:
	CollisionHandler();
	~CollisionHandler();

	void Initialize();
	void CleanUp();
	void Update(float deltaTime);
	void Reset();

	void AddGround(PhysicsObject* groundObject);
	void AddCollisionObject(PhysicsObject* physicsObject);
	void AddCollisionObjects(std::vector<PhysicsObject*> physicsObjects);
	void AddCollisionObject(RigidBody* rigidBody);
	void AddCollisionObjects(std::vector<RigidBody*> rigidBodies);

	void AddRunTimeContactGenerator(ContactGenerator* contactGeneraor);
	void AddContactGenerators(std::vector<ContactGenerator*> contactGenerators);

	std::vector<PhysicsObject*> GetPhysicsObjects() { return mp_PhysicsObjects; };
	std::vector<RigidBody*> GetRigidBodies() { return mp_RigidBodies; };

	void AddContact(Contact contact) { m_Contacts.push_back(contact); };
	void AddContact(RBContact rigidContact) { m_RigidContacts.push_back(rigidContact); };

	inline int GetCollisions() { return m_Collisions; };

	inline CollisionDetector* GetCollisionDetector() { return mp_CollisionDetector; };

	inline float GetRestitution() { return m_Restitution; };
	inline float GetFriction() { return m_Friction; };

private:
	int checkCollisions();
	void resolveContacts(float deltaTime);
	void resolveRigidBodyContacts(float deltaTime);

	void prepareRigidBodyContacts(float deltaTime);
	void adjustPositions(float deltaTime);
	void adjustVelocities(float deltaTime);

	void addRunTimeContactGenerators();

	std::vector<PhysicsObject*> mp_PhysicsObjects;
	std::vector<RigidBody*> mp_RigidBodies;

	std::vector<ContactGenerator*> mp_RigidContactGenerators;
	std::vector<ContactGenerator*> mp_ContactGenerators;
	std::vector<ContactGenerator*> mp_ToAddContactGenerators;
	std::vector<Contact> m_Contacts;
	std::vector<RBContact> m_RigidContacts;

	int m_MaxChecks;
	int m_Collisions;

	CollisionDetector* mp_CollisionDetector;

	float m_Restitution;
	float m_Friction;

	int m_PositionIterations;
	int m_PositionIterationsUsed;
	int m_VelocityIterations;
	int m_VelocityIterationsUsed;

	float m_PositionEpsilon;
	float m_VelocityEpsilon;
};
#endif