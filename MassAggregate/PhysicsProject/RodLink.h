//======================================================================
//File: RodLink.h
//Author: Matt Struble
//======================================================================
#ifndef ROD_LINK_H
#define ROD_LINK_H
//======================================================================
#pragma once
//======================================================================
#include "LinkContact.h"
//======================================================================
class RodLink : public LinkContact
{
public:
	RodLink(PhysicObject* one, PhysicObject* two, float length);
	~RodLink() {};

	virtual void AddContact(CollisionHandler* handler) const;

	float MaxLength;
};
#endif