//======================================================================
//File: ContactResolver.h
//Author: Matt Struble
//======================================================================
#ifndef CONTACT_RESOLVER_H
#define CONTACT_RESOLVER_H
//======================================================================
#pragma once
//======================================================================
#include "Contact.h"
//======================================================================
class ContactResolver
{

public:
	ContactResolver(unsigned int iterations);
	~ContactResolver();

	void SetIterations(unsigned int iterations);

	void ResolveContacts(Contact *contactArray, unsigned int numContacts, float dt);

protected:
	unsigned int m_Iterations;
	unsigned int m_IterationsUsed;
};
#endif