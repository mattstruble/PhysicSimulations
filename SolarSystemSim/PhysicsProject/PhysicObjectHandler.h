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

	bool Remove(PhysicObject* object);

	void AddToRegistry(std::vector<PhysicObject*> objects, ForceGenerator* generator);
	void RemoveFromRegistry(std::vector<PhysicObject*> objects, ForceGenerator* generator);

	const std::vector<PhysicObject*>& GetPhysicObjects() const { return m_PhysicObjects; };
	PhysicObject*& GetTarget() { return mp_Target; };

private:
	std::vector<PhysicObject*> m_PhysicObjects;
	ForceRegistry* mp_ForceRegistry;
	PhysicObject* mp_Target;
};
#endif