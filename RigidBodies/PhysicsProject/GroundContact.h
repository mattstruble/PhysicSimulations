//======================================================================
//File: GroundContact.h
//Author: Matt Struble
//======================================================================
#ifndef GROUND_CONTACT_H
#define GROUND_CONTACT_H
//======================================================================
#pragma once
//======================================================================
#include "ContactGenerator.h"
//======================================================================
class GroundContact : public ContactGenerator
{
public:
	GroundContact(float groundY = 0);
	~GroundContact() {};

	virtual void AddContact(CollisionHandler* handler) const;

private:
	float m_GroundY;
};
#endif