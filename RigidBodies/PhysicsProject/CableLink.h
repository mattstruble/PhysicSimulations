//======================================================================
//File: CableLink.h
//Author: Matt Struble
//======================================================================
#ifndef CABLE_LINK_H
#define CABLE_LINK_H
//======================================================================
#pragma once
//======================================================================
#include "LinkContact.h"
//======================================================================
class CableLink : public LinkContact
{
public:
	CableLink(PhysicObject* one, PhysicObject* two, float length, float restitution = 0.0f);
	~CableLink() {};

	virtual void AddContact(CollisionHandler* handler) const;

	float MaxLength;
	float Restitution;
};
#endif