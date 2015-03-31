//======================================================================
//File: LinkContact.cpp
//Author: Matt Struble
//======================================================================
#include "LinkContact.h"
//======================================================================
float LinkContact::currentLength() const
{
	Vector3D relPos = Object[0]->GetPosition() - Object[1]->GetPosition();

	return relPos.Magnitude();
}