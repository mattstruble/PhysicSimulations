//======================================================================
//File: PhysicObjectHandler.cpp
//Author: Matt Struble
//======================================================================
#include "PhysicObjectHandler.h"
//======================================================================
PhysicObjectHandler::PhysicObjectHandler()
{
	mp_CollisionHandler = nullptr;
	mp_ForceRegistry = nullptr;
	mp_Target = nullptr;
}

//--------------------------------------------------------------------------------
PhysicObjectHandler::~PhysicObjectHandler()
{
	Clear();

	delete mp_ForceRegistry;
	mp_ForceRegistry = nullptr;

	delete mp_CollisionHandler;
	mp_CollisionHandler = nullptr;
}

//--------------------------------------------------------------------------------
void PhysicObjectHandler::Initialize()
{
	mp_ForceRegistry = new ForceRegistry();
	mp_CollisionHandler = new CollisionHandler();
	mp_CollisionHandler->Initialize();
}

//--------------------------------------------------------------------------------
void PhysicObjectHandler::Update(float dt)
{
	mp_ForceRegistry->UpdateForces(dt);
	
	for (unsigned int i = 0; i < m_PhysicObjects.size(); i++)
	{
		m_PhysicObjects[i]->Update(dt);
	}

	mp_CollisionHandler->Update(dt);
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
			if (static_cast<unsigned int>(key - '0') < m_PhysicObjects.size())
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

	mp_CollisionHandler->Reset();
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
	mp_CollisionHandler->Clear();
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

void PhysicObjectHandler::AddCollisionObject(PhysicObject* object)
{
	Add(object);

	mp_CollisionHandler->AddCollisionObject(object);
}

void PhysicObjectHandler::AddCollisionObject(std::vector<PhysicObject*> objects)
{
	Add(objects);

	mp_CollisionHandler->AddCollisionObject(objects);
}

void PhysicObjectHandler::AddContactGenerator(ContactGenerator* generator)
{
	mp_CollisionHandler->AddContactGenerator(generator);
}

void PhysicObjectHandler::AddContactGenerator(std::vector<ContactGenerator*> generators)
{
	mp_CollisionHandler->AddContactGenerator(generators);
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

bool PhysicObjectHandler::RemoveCollisionObject(PhysicObject* object)
{
	return mp_CollisionHandler->Remove(object);
}

void PhysicObjectHandler::AddToRegistry(PhysicObject* object, ForceGenerator* generator)
{
	mp_ForceRegistry->Add(object, generator);
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