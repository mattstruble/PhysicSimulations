//======================================================================
//File: SolarSystem.cpp
//Author: Matt Struble
//======================================================================
#include "SolarSystem.h"
//======================================================================
SolarSystem::SolarSystem()
{

}

//--------------------------------------------------------------------------------
SolarSystem::~SolarSystem()
{

}

//--------------------------------------------------------------------------------
void SolarSystem::Initialize()
{
	SolarSystemParser parser;
	parser.Parse("../data/SolarSystem.xml");

	for (auto it = parser.GetPlanetData().cbegin(); it != parser.GetPlanetData().cend(); ++it)
	{
		Planet* planet = new Planet();

		planet->Initialize(it->Name, it->Radius, it->Mass, Vector3D(it->Distance, 0, 0), Vector3D(0, 0, it->Velocity));
		planet->SetColor(it->Color);
		m_Planets.push_back(planet);
	}
}
//================================================================================