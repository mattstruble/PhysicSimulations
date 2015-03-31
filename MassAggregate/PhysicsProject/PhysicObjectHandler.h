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
	void Add(const std::vector<PhysicObject*>& objects);

	void AddCollisionObject(PhysicObject* object);
	void AddCollisionObject(std::vector<PhysicObject*> objects);

	void AddContactGenerator(ContactGenerator* generator);
	void AddContactGenerator(std::vector<ContactGenerator*> generators);

	bool Remove(PhysicObject* object);
	bool RemoveCollisionObject(PhysicObject* object);

	void AddToRegistry(PhysicObject* object, ForceGenerator* generator);
	void AddToRegistry(std::vector<PhysicObject*> objects, ForceGenerator* generator);
	void RemoveFromRegistry(std::vector<PhysicObject*> objects, ForceGenerator* generator);

	const std::vector<PhysicObject*>& GetPhysicObjects() const { return m_PhysicObjects; };
	PhysicObject*& GetTarget() { return mp_Target; };
	inline void SetTarget(PhysicObject* target) { mp_Target = target; };

private:
	std::vector<PhysicObject*> m_PhysicObjects;
	ForceRegistry* mp_ForceRegistry;
	CollisionHandler* mp_CollisionHandler;
	PhysicObject* mp_Target;
};
#endif