//======================================================================
//File: ForceRegistry.cpp
//Author: Matt Struble
//======================================================================
#include "ForceRegistry.h"
//======================================================================
ForceRegistry::ForceRegistry()
{

}

//--------------------------------------------------------------------------------
ForceRegistry::~ForceRegistry()
{
	Clear();
}

//--------------------------------------------------------------------------------
bool ForceRegistry::Add(PhysicObject* object, ForceGenerator* generator)
{
	s_ForceGeneratorRegistry tmpRegistry = s_ForceGeneratorRegistry(object, generator);
	m_ForceGeneratorRegistry.push_back(tmpRegistry);

	return true;
}

//--------------------------------------------------------------------------------
bool ForceRegistry::Add(RigidBody* rigidBody, ForceGenerator* generator)
{
	s_RBForceGeneratorRegistry tmpRegistry = s_RBForceGeneratorRegistry(rigidBody, generator);
	m_RBForceGeneratorRegistry.push_back(tmpRegistry);

	return true;
}

//--------------------------------------------------------------------------------
bool ForceRegistry::Remove(PhysicObject* object, ForceGenerator* generator)
{
	s_ForceGeneratorRegistry tmpRegistry = s_ForceGeneratorRegistry(object, generator);

	for (unsigned int i = 0; i < m_ForceGeneratorRegistry.size(); i++)
	{
		if (m_ForceGeneratorRegistry[i] == tmpRegistry)
		{
			m_ForceGeneratorRegistry.erase(m_ForceGeneratorRegistry.begin() + i);
			return true;
		}
	}

	return false;
}

//--------------------------------------------------------------------------------
bool ForceRegistry::Remove(RigidBody* rigidBody, ForceGenerator* generator)
{
	s_RBForceGeneratorRegistry tmpRegistry = s_RBForceGeneratorRegistry(rigidBody, generator);

	for (unsigned int i = 0; i < m_RBForceGeneratorRegistry.size(); i++)
	{
		if (m_RBForceGeneratorRegistry[i] == tmpRegistry)
		{
			m_RBForceGeneratorRegistry.erase(m_RBForceGeneratorRegistry.begin() + i);
			return true;
		}
	}

	return false;
}

//--------------------------------------------------------------------------------
void ForceRegistry::UpdateForces(float dt)
{
	for (unsigned int i = 0; i < m_ForceGeneratorRegistry.size(); i++)
	{
		m_ForceGeneratorRegistry[i].UpdateForce(dt);
	}

	for (unsigned int i = 0; i < m_RBForceGeneratorRegistry.size(); i++)
	{
		m_RBForceGeneratorRegistry[i].UpdateForce(dt);
	}
}

//--------------------------------------------------------------------------------
void ForceRegistry::Clear()
{
	m_ForceGeneratorRegistry.clear();
	m_RBForceGeneratorRegistry.clear();
}
//================================================================================