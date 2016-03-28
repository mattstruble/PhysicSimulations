//======================================================================
//File: CollisionHandler.cpp
//Author: Matt Struble
//======================================================================
#include "CollisionHandler.h"
#include "ContactGenerator.h"
#include "RBCollisionDetector.h"
#include "RBGameObjectContact.h"
//======================================================================
CollisionHandler::CollisionHandler()
{
	m_MaxIterations = 4;
	m_Collisions = 0;

	m_MaxPosIterations = 5;
	m_PositionEpsilon = 0.1f;

	m_MaxVelIterations = 5;
	m_VelocityEpsilon = 0.1f;

	m_Restitution = 0.5f;
	m_Friction = 0.1f;

	mp_RBCollisionDetector = new RBCollisionDetector();
}

//-----------------------------------------------------------------------------
CollisionHandler::~CollisionHandler()
{
	Clear();
}

//-----------------------------------------------------------------------------
void CollisionHandler::Initialize()
{
}

//-----------------------------------------------------------------------------
void CollisionHandler::Update(float dt)
{
	int iterations = collisions() * 2 - 1;

	m_Collisions = m_Contacts.size();

	if (iterations > m_MaxIterations)
	{
		iterations = m_MaxIterations;
	}

	for (int i = 0; i < iterations; i++)
	{
		collisions();
		resolveContacts(dt);
	}
}

//-----------------------------------------------------------------------------
void CollisionHandler::Reset()
{
	
}

//-----------------------------------------------------------------------------
void CollisionHandler::Clear()
{
	m_Contacts.clear();
	mp_ContactGenerators.clear();
}

//-----------------------------------------------------------------------------
void CollisionHandler::AddCollisionObject(PhysicObject* object)
{
	mp_PhysicObjects.push_back(object);
}

//-----------------------------------------------------------------------------
void CollisionHandler::AddCollisionObject(std::vector<PhysicObject*> objects)
{
	std::vector<PhysicObject*>::iterator iter;
	for (iter = objects.begin(); iter != objects.end(); iter++)
	{
		mp_PhysicObjects.push_back(*iter);
	}
}

//-----------------------------------------------------------------------------
void CollisionHandler::AddCollisionObject(RigidBody* rigidBody)
{
	mp_RigidBodies.push_back(rigidBody);
}

//-----------------------------------------------------------------------------
void CollisionHandler::AddCollisionObject(std::vector<RigidBody*> rigidBodies)
{
	std::vector<RigidBody*>::iterator iter;
	for (iter = rigidBodies.begin(); iter != rigidBodies.end(); iter++)
	{
		mp_RigidBodies.push_back(*iter);
	}
}

//-----------------------------------------------------------------------------
void CollisionHandler::AddContactGenerator(ContactGenerator* generator)
{
	mp_ContactGenerators.push_back(generator);
}

//-----------------------------------------------------------------------------
void CollisionHandler::AddContactGenerator(std::vector<ContactGenerator*> generators)
{
	std::vector<ContactGenerator*>::iterator iter;
	for (iter = generators.begin(); iter != generators.end(); iter++)
	{
		mp_ContactGenerators.push_back(*iter);
	}
}

//-----------------------------------------------------------------------------
bool CollisionHandler::Remove(PhysicObject* object)
{
	for (unsigned int i = 0; i < mp_PhysicObjects.size(); i++)
	{
		if (object == mp_PhysicObjects[i])
		{
			delete object;
			mp_PhysicObjects.erase(mp_PhysicObjects.begin() + i);
			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------
bool CollisionHandler::Remove(RigidBody* rigidBody)
{
	for (unsigned int i = 0; i < mp_RigidBodies.size(); i++)
	{
		if (rigidBody == mp_RigidBodies[i])
		{
			delete rigidBody;
			mp_RigidBodies.erase(mp_RigidBodies.begin() + i);
			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------
int CollisionHandler::collisions()
{
	int count = 0;
	std::vector<ContactGenerator*>::iterator iter;
	for (iter = mp_ContactGenerators.begin(); iter != mp_ContactGenerators.end(); iter++)
	{
		(*iter)->AddContact(this);
		count++;
	}

	int rbCount = 0;
	std::vector<ContactGenerator*>::iterator RBContactGeneratorIter;
	for (RBContactGeneratorIter = mp_RBContactGenerators.begin(); RBContactGeneratorIter != mp_RBContactGenerators.end(); RBContactGeneratorIter++)
	{
		(*RBContactGeneratorIter)->AddContact(this);
		rbCount++;
	}

	return count + rbCount;
}

//-----------------------------------------------------------------------------
void CollisionHandler::resolveContacts(float dt)
{
	std::vector<Contact>::iterator iter;
	for (iter = m_Contacts.begin(); iter != m_Contacts.end(); iter++)
	{
		(*iter).Resolve(dt);
	}

	resolveRBContacts(dt);

	m_Contacts.clear();
	m_RBContacts.clear();
}

//-----------------------------------------------------------------------------
void CollisionHandler::resolveRBContacts(float dt)
{
	setRBContacts(dt);
	adjustPositions(dt);
	adjustVelocities(dt);
}

//-----------------------------------------------------------------------------
void CollisionHandler::setRBContacts(float dt)
{
	std::vector<RBContact>::iterator rbContactIter;
	for (rbContactIter = m_RBContacts.begin(); rbContactIter != m_RBContacts.end(); rbContactIter++)
	{
		(*rbContactIter).CalculateInternals(dt);
	}
}

//-----------------------------------------------------------------------------
void CollisionHandler::adjustPositions(float dt)
{
	unsigned int i;
	unsigned int index;
	Vector3D linearChange[2];
	Vector3D angularChange[2];
	float max;
	Vector3D deltaPosition;

	m_PosIterations = 0;
	while (m_PosIterations < m_MaxPosIterations)
	{
		max = m_PositionEpsilon;
		index = m_RBContacts.size();

		for (i = 0; i < m_RBContacts.size(); i++)
		{
			float penetration = m_RBContacts[i].GetPenetration();
			if (penetration > max)
			{
				max = penetration;
				index = i;
			}
		}
		if (index == m_RBContacts.size())
			break;

		m_RBContacts[index].MatchAwakeState();
		m_RBContacts[index].ApplyPositionChange(linearChange, angularChange, max, dt);

		for (i = 0; i < m_RBContacts.size(); i++)
		{
			for (unsigned int body = 0; body < 2; body++)
			{
				if (m_RBContacts[i].GetRigidBody(body))
				{
					for (unsigned int d = 0; d < 2; d++)
					{
						if (m_RBContacts[i].GetRigidBody(body) == m_RBContacts[index].GetRigidBody(d))
						{
							deltaPosition = linearChange[d] + angularChange[d] * m_RBContacts[i].GetRelativeContactPosition(body);

							float penetration = m_RBContacts[i].GetPenetration();
							penetration += Vector3D::Dot(deltaPosition, m_RBContacts[i].GetContactNormal()) * (body ? 1 : -1);
							m_RBContacts[i].SetPenetration(penetration);
						}
					}
				}
			}
		}
		m_PosIterations++;
	}
}

//-----------------------------------------------------------------------------
void CollisionHandler::adjustVelocities(float dt)
{
	Vector3D velocityChange[2];
	Vector3D rotationChange[2];
	Vector3D deltaVelocity;

	m_VelIterations = 0;
	while (m_VelIterations < m_MaxVelIterations)
	{
		float max = m_VelocityEpsilon;
		unsigned int index = m_RBContacts.size();
		for (unsigned int i = 0; i < m_RBContacts.size(); i++)
		{
			if (m_RBContacts[i].GetDesiredDeltaVelocity() > max)
			{
				max = m_RBContacts[i].GetDesiredDeltaVelocity();
				index = i;
			}
		}

		if (index == m_RBContacts.size())
			break;

		m_RBContacts[index].MatchAwakeState();
		m_RBContacts[index].ApplyVelocityChange(velocityChange, rotationChange, dt);

		for (unsigned int i = 0; i < m_RBContacts.size(); i++)
		{
			for (unsigned int b = 0; b < 2; b++)
			{
				if (m_RBContacts[i].GetRigidBody(b))
				{
					for (unsigned d = 0; d < 2; d++)
					{
						if (m_RBContacts[i].GetRigidBody(b) == m_RBContacts[index].GetRigidBody(d))
						{
							deltaVelocity = velocityChange[d] + rotationChange[d] * m_RBContacts[i].GetRelativeContactPosition(b);

							m_RBContacts[i].SetContactVelocity(m_RBContacts[i].GetContactVelocity() + m_RBContacts[i].GetContactToWorld().TransformTranspose(deltaVelocity) * (float)(b ? -1 : 1));
							m_RBContacts[i].CalculateDesiredDeltavelocity(dt);
						}
					}
				}
			}
		}
		m_VelIterations++;
	}
}