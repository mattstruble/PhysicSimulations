//======================================================================
//File: PhysicObjectHandler.h
//Author: Matt Struble
//======================================================================
#ifndef PHYSIC_OBJECT_HANDLER_H
#define PHYSIC_OBJECT_HANDLER_H
//======================================================================
#pragma once
//======================================================================
#include "PhysicObject.h"
#include "ForceGenerator.h"
#include "ForceRegistry.h"
#include "CollisionHandler.h"
#include <vector>
//======================================================================
class PhysicObjectHandler
{
public:
	PhysicObjectHandler();
	~PhysicObjectHandler();

	void Initialize();
	void Update(float dt);
	void Draw();
	void HandleKey(unsigned char key);
	void Reset();
	void Clear();

	void Add(PhysicObject* object);
	void Add(RigidBody* rigidBody);
	void Add(const std::vector<PhysicObject*>& objects);
	void Add(const std::vector<RigidBody*>& rigidBodies);

	void AddCollisionObject(PhysicObject* object);
	void AddCollisionObject(RigidBody* rigidBody);
	void AddCollisionObject(std::vector<PhysicObject*> objects);
	void AddCollisionObject(std::vector<RigidBody*> rigidBodies);

	void AddContactGenerator(ContactGenerator* generator);
	void AddContactGenerator(std::vector<ContactGenerator*> generators);

	bool Remove(PhysicObject* object);
	bool Remove(RigidBody* rigidBody);
	bool RemoveCollisionObject(PhysicObject* object);
	bool RemoveCollisionObject(RigidBody* rigidBody);

	void AddToRegistry(PhysicObject* object, ForceGenerator* generator);
	void AddToRegistry(RigidBody* rigidBody, ForceGenerator* generator);
	void AddToRegistry(std::vector<PhysicObject*> objects, ForceGenerator* generator);
	void AddToRegistry(std::vector<RigidBody*> RigidBodies, ForceGenerator* generator);

	void RemoveFromRegistry(std::vector<PhysicObject*> objects, ForceGenerator* generator);
	void RemoveFromRegistry(std::vector<RigidBody*> rigidBodies, ForceGenerator* generator);

	const std::vector<PhysicObject*>& GetPhysicObjects() const { return m_PhysicObjects; };
	const std::vector<RigidBody*>& GetRigidBodies() const { return m_RigidBodies; };

	PhysicObject*& GetTarget() { return mp_Target; };
	inline void SetTarget(PhysicObject* target) { mp_Target = target; };

	inline int GetCollisions() { return mp_CollisionHandler->GetCollisions(); };

private:
	std::vector<PhysicObject*> m_PhysicObjects;
	std::vector<RigidBody*> m_RigidBodies;
	ForceRegistry* mp_ForceRegistry;
	CollisionHandler* mp_CollisionHandler;
	PhysicObject* mp_Target;
};
#endif