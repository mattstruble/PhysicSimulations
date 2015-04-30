//======================================================================
//File: RBGameObjectContact.h
//Author: Matt Struble
//======================================================================
#ifndef RB_GAME_OBJECT_CONTACT_H
#define RB_GAME_OBJECT_CONTACT_H
//======================================================================
#pragma once
//======================================================================
#include "ContactGenerator.h"
//======================================================================
class RBGameObjectContact : public ContactGenerator
{
public:
	RBGameObjectContact();
	~RBGameObjectContact();

	void AddContact(CollisionHandler* collisionHandler) const;
};
#endif