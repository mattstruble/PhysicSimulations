//======================================================================
//File: RBGroundContact.h
//Author: Matt Struble
//======================================================================
#ifndef RB_GROUND_CONTACT_H
#define RB_GROUND_CONTACT_H
//======================================================================
#pragma once
//======================================================================
#include "ContactGenerator.h"
#include "CollisionPlane.h"
//======================================================================
class RBGroundContact : public ContactGenerator
{
public:
	RBGroundContact(float groundY = 0);
	~RBGroundContact();

	void AddContact(CollisionHandler* handler) const;

private:
	CollisionPlane m_CollisionPlane;
};
#endif