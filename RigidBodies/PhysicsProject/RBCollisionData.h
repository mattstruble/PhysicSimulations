//======================================================================
//File: RBCollisionData.h
//Author: Matt Struble
//Resource: https://github.com/idmillington/cyclone-physics
//======================================================================
#ifndef RB_COLLISION_DATA_H
#define RB_COLLISION_DATA_H
//=============================================================================
#pragma once
//=============================================================================
#include "RBContact.h"
#include <vector>
//=============================================================================
class CollisionData
{
private:
	std::vector<RBContact*> mp_RigidContacts;

	int m_ContactsLeft;

	float m_Restitution;
	float m_Friction;

public:
	CollisionData() {};
	~CollisionData() {};

	inline void AddContacts(int contacts) { m_ContactsLeft += contacts; };

	inline std::vector<RBContact*> GetRigidContacts() { return mp_RigidContacts; };
	inline int GetContactsLeft() { return m_ContactsLeft; };

	inline float GetRestitution() { return m_Restitution; };
	inline float GetFriction() { return m_Friction; };
};
#endif