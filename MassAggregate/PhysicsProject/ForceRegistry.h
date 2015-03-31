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
class ForceRegistry
{
public:
	ForceRegistry();
	~ForceRegistry();

	bool Add(PhysicObject* object, ForceGenerator* generator);

	bool Remove(PhysicObject* object, ForceGenerator* generator);

	void UpdateForces(float dt);
	void Clear();
private:
	std::vector<s_ForceGeneratorRegistry> m_ForceGeneratorRegistry;
};
#endif