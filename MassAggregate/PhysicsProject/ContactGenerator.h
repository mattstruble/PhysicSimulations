//======================================================================
//File: ContactGenerator.h
//Author: Matt Struble
//======================================================================
#ifndef CONTACT_GENERATOR_H
#define CONTACT_GENERATOR_H
//======================================================================
#pragma once
//======================================================================
#include "Contact.h"
#include "CollisionHandler.h"
//======================================================================
class CollisionHandler;

class ContactGenerator
{
public:
	ContactGenerator() {};
	~ContactGenerator() {};

	virtual void AddContact(CollisionHandler* handler) const = 0;
};
#endif