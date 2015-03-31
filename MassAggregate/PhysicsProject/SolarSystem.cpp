//======================================================================
//File: SolarSystem.cpp
//Author: Matt Struble
//======================================================================
#include "SolarSystem.h"
#include "GravityForceGenerator.h"
//======================================================================
SolarSystem::SolarSystem()
{

}

//--------------------------------------------------------------------------------
SolarSystem::~SolarSystem()
{

}

//--------------------------------------------------------------------------------
void SolarSystem::Initialize(PhysicObjectHandler* handler)
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

	GravityForceGenerator* gravity = new GravityForceGenerator(handler);

	std::vector<PhysicObject*> po_Planets;

	for (unsigned int i = 0; i < m_Planets.size(); i++)
	{
		po_Planets.push_back(m_Planets[i]);
	}

	handler->Add(po_Planets);
	handler->AddToRegistry(po_Planets, gravity);
}
//================================================================================