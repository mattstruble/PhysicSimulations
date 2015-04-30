//======================================================================
//File: RBGroundContact.h
//Author: Matt Struble
//======================================================================
#include "RBGroundContact.h"
#include "RigidBody.h"
#include "CollisionHandler.h"
#include "RBContact.h"
#include "RBCollisionDetector.h"
//======================================================================
RBGroundContact::RBGroundContact(float groundY)
{
	m_CollisionPlane = CollisionPlane();
	m_CollisionPlane.SetDirection(Vector3D(0, 1, 0));
	m_CollisionPlane.SetOffset(groundY);
}

//----------------------------------------------------------------------
RBGroundContact::~RBGroundContact()
{

}

//-----------------------------------------------------------------------------
void RBGroundContact::AddContact(CollisionHandler* collisionHandler) const
{
	std::vector<RigidBody*> rigidBodies = collisionHandler->GetRigidBodies();

	std::vector<RigidBody*>::iterator rigidBodyIter;
	for (rigidBodyIter = rigidBodies.begin(); rigidBodyIter != rigidBodies.end(); rigidBodyIter++)
	{
		switch ((*rigidBodyIter)->GetCollisionType())
		{
			case e_CollisionType::SPHERE:
				collisionHandler->GetRBCollisionDetector()->SphereAndHalfSpace((*rigidBodyIter)->GetCollisionSphere(), m_CollisionPlane, collisionHandler);
				break;
		}
		
	}
}