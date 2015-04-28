//======================================================================
//File: SolarSystem.h
//Author: Matt Struble
//======================================================================
#ifndef SOLAR_SYSTEM_H
#define SOLAR_SYSTEM_H
//======================================================================
#pragma once
//======================================================================
#include "Planet.h"
#include <vector>
#include "SolarSystemParser.h"
#include "PhysicObjectHandler.h"
//======================================================================
class SolarSystem
{
public:
	SolarSystem();
	~SolarSystem();

	void Initialize(PhysicObjectHandler* handler);

	inline const std::vector<Planet*> GetPlanets() const { return m_Planets; };
private:
	std::vector<Planet*> m_Planets;
};
#endif