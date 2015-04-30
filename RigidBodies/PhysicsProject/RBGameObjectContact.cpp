//======================================================================
//File: RBGameObjectContact.cpp
//Author: Matt Struble
//======================================================================
#include "RBGameObjectContact.h"
#include "RigidBody.h"
#include "CollisionHandler.h"
#include "RBCollisionDetector.h"
//======================================================================
RBGameObjectContact::RBGameObjectContact()
{
}

//-----------------------------------------------------------------------------
RBGameObjectContact::~RBGameObjectContact()
{
}

//-----------------------------------------------------------------------------
void RBGameObjectContact::AddContact(CollisionHandler* collisionHandler) const
{
	std::vector<RigidBody*> rigidBodies = collisionHandler->GetRigidBodies();

	for (unsigned int i = 0; i < rigidBodies.size(); ++i)
	{
		for (unsigned int j = i + 1; j < rigidBodies.size(); j++)
		{
			RigidBody* rigidBodyOne = rigidBodies[i];
			RigidBody* rigidBodyTwo = rigidBodies[j];

			collisionHandler->GetRBCollisionDetector()->CheckCollision(rigidBodyOne, rigidBodyTwo, collisionHandler);
		}
	}
}