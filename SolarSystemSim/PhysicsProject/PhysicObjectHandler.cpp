//======================================================================
//File: PhysicObjectHandler.cpp
//Author: Matt Struble
//======================================================================
#include "PhysicObjectHandler.h"
//======================================================================
PhysicObjectHandler::PhysicObjectHandler()
{
	mp_ForceRegistry = nullptr;
	mp_Target = nullptr;
}

//--------------------------------------------------------------------------------
PhysicObjectHandler::~PhysicObjectHandler()
{
	Clear();

	delete mp_ForceRegistry;
	mp_ForceRegistry = nullptr;

}

//--------------------------------------------------------------------------------
void PhysicObjectHandler::Initialize()
{
	mp_ForceRegistry = new ForceRegistry();
}

//--------------------------------------------------------------------------------
void PhysicObjectHandler::Update(float dt)
{
	mp_ForceRegistry->UpdateForces(dt);

	for (unsigned int i = 0; i < m_PhysicObjects.size(); i++)
	{
		m_PhysicObjects[i]->Update(dt);
	}
}

//--------------------------------------------------------------------------------
void PhysicObjectHandler::Draw()
{
	for (unsigned int i = 0; i < m_PhysicObjects.size(); i++)
	{
		m_PhysicObjects[i]->Draw();
	}
}

//--------------------------------------------------------------------------------
void PhysicObjectHandler::HandleKey(unsigned char key)
{
	if (isdigit(key))
	{
		if (key != '0')
		{
			if (key - '0' < m_PhysicObjects.size())
			{
				mp_Target = m_PhysicObjects[key - '0'];
			}
		}
		else
			mp_Target = nullptr;
	}
	else if (key == 'r')
	{
		Reset();
	}
}

//--------------------------------------------------------------------------------
void PhysicObjectHandler::Reset()
{
	for (unsigned int i = 0; i < m_PhysicObjects.size(); i++)
	{
		m_PhysicObjects[i]->Reset();
	}
}

//--------------------------------------------------------------------------------
void PhysicObjectHandler::Clear()
{
	for (unsigned int i = 0; i < m_PhysicObjects.size(); i++)
	{
		delete m_PhysicObjects[i];
		m_PhysicObjects[i] = nullptr;
	}

	m_PhysicObjects.clear();
}

//--------------------------------------------------------------------------------
void PhysicObjectHandler::Add(PhysicObject* object)
{
	m_PhysicObjects.push_back(object);
}

//--------------------------------------------------------------------------------
void PhysicObjectHandler::Add(const std::vector<PhysicObject*>& objects)
{
	for (unsigned int i = 0; i < objects.size(); i++)
	{
		m_PhysicObjects.push_back(objects[i]);
	}
}

//--------------------------------------------------------------------------------
bool PhysicObjectHandler::Remove(PhysicObject* object)
{
	for (unsigned int i = 0; i < m_PhysicObjects.size(); i++)
	{
		if (object == m_PhysicObjects[i])
		{
			delete object;
			m_PhysicObjects.erase(m_PhysicObjects.begin() + i);
			return true;
		}
	}

	return false;
}

//--------------------------------------------------------------------------------
void PhysicObjectHandler::AddToRegistry(std::vector<PhysicObject*> objects, ForceGenerator* generator)
{
	
	if (generator == nullptr)
	{
		return;
	}

	for (unsigned int i = 0; i < objects.size(); i++)
	{
		mp_ForceRegistry->Add(objects[i], generator);
	}
}

//--------------------------------------------------------------------------------
void PhysicObjectHandler::RemoveFromRegistry(std::vector<PhysicObject*> objects, ForceGenerator* generator )
{
	if (generator == nullptr)
	{
		return;
	}

	for (unsigned int i = 0; i < objects.size(); i++)
	{
		mp_ForceRegistry->Remove(objects[i], generator);
	}
}
//================================================================================