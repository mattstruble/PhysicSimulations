//======================================================================
//File: BlobSystem.h
//Author: Matt Struble
//======================================================================
#ifndef BLOB_SYSTEM_H
#define BLOB_SYSTEM_H
//======================================================================
#pragma once
//======================================================================
#include <vector>
//======================================================================
#include "ForceGenerator.h"
#include "Plane.h"
#include "Vector3D.h"
#include "ForceRegistry.h"
#include "MassAggregate.h"
#include "ContactGenerator.h"
#include "PhysicObjectHandler.h"
//======================================================================
class BlobSystem
{
public:
	BlobSystem();
	~BlobSystem();

	void Initialize(PhysicObjectHandler* handler);

private:
	std::vector<MassAggregate*> mp_MassAggregates;
};
#endif