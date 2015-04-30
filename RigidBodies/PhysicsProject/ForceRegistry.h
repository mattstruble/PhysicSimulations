//======================================================================
//File: ForceRegistry.h
//Author: Matt Struble
//======================================================================
#ifndef FORCE_REGISTRY_H
#define FORCE_REGISTRY_H
//======================================================================
#pragma once
//======================================================================
#include "PhysicObject.h"
#include "RigidBody.h"
#include "ForceGenerator.h"
#include <vector>
//======================================================================
struct s_ForceGeneratorRegistry
{
	PhysicObject* m_Object;

	ForceGenerator* m_ForceGenerator;

	s_ForceGeneratorRegistry(PhysicObject* object, ForceGenerator* generator)
	{
		m_Object = object;
		m_ForceGenerator = generator;
	}

	bool operator==(const s_ForceGeneratorRegistry& rhs)
	{
		return (m_Object == rhs.m_Object) &&
			(m_ForceGenerator == rhs.m_ForceGenerator);
	}

	void UpdateForce(float dt)
	{
		if (m_Object == nullptr || m_ForceGenerator == nullptr)
		{
			return;
		}

		m_ForceGenerator->UpdateForce(m_Object, dt);
	}
};
//======================================================================
struct s_RBForceGeneratorRegistry
{
	RigidBody* m_RigidBody;

	ForceGenerator* m_ForceGenerator;

	s_RBForceGeneratorRegistry(RigidBody* rigidBody, ForceGenerator* generator)
	{
		m_RigidBody = rigidBody;
		m_ForceGenerator = generator;
	}

	bool operator==(const s_RBForceGeneratorRegistry& rhs)
	{
		return (m_RigidBody == rhs.m_RigidBody) &&
			(m_ForceGenerator == rhs.m_ForceGenerator);
	}

	void UpdateForce(float dt)
	{
		if (m_RigidBody == nullptr || m_ForceGenerator == nullptr)
		{
			return;
		}

		m_ForceGenerator->UpdateForce(m_RigidBody, dt);
	}
};
//======================================================================
class ForceRegistry
{
public:
	ForceRegistry();
	~ForceRegistry();

	bool Add(PhysicObject* object, ForceGenerator* generator);
	bool Add(RigidBody* rigidBody, ForceGenerator* generator);

	bool Remove(PhysicObject* object, ForceGenerator* generator);
	bool Remove(RigidBody* rigidBody, ForceGenerator* generator);

	void UpdateForces(float dt);
	void Clear();
private:
	std::vector<s_ForceGeneratorRegistry> m_ForceGeneratorRegistry;
	std::vector<s_RBForceGeneratorRegistry> m_RBForceGeneratorRegistry;
};
#endif