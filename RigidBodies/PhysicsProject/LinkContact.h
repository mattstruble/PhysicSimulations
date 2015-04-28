//======================================================================
//File: LinkContact.h
//Author: Matt Struble
//======================================================================
#ifndef LINK_CONTACT_H
#define LINK_CONTACT_H
//======================================================================
#pragma once
//======================================================================
#include "ContactGenerator.h"
//======================================================================
class LinkContact : public ContactGenerator
{
public:
	LinkContact() {};
	~LinkContact() {};

	virtual void AddContact(CollisionHandler* handler) const = 0;

	PhysicObject* Object[2];

protected:
	float currentLength() const;
};
#endif