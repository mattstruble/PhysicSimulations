//======================================================================
//File: SolarSystemParser.cpp
//Author: Matt Struble
//======================================================================
#include "SolarSystemParser.h"
//======================================================================
using namespace tinyxml2;
//======================================================================
bool SolarSystemParser::Parse(const std::string& path)
{
	XMLDocument document;

	document.LoadFile(path.c_str());

	XMLElement* root = document.FirstChildElement("solarsystem");

	for (XMLElement* it = root->FirstChildElement("planet"); it != NULL; it = it->NextSiblingElement())
	{
		ParsePlanetData(it);
	}

	return true;
}

//--------------------------------------------------------------------------------
void SolarSystemParser::ParsePlanetData(XMLElement* dataElement)
{
	PlanetData planetData;

	XMLElement* it = dataElement->FirstChildElement("name");
	planetData.Name = std::string(it->GetText());

	it = it->NextSiblingElement("mass");
	planetData.Mass = atof(it->GetText());

	it = it->NextSiblingElement("radius");
	planetData.Radius = atof(it->GetText());

	it = it->NextSiblingElement("distance");
	planetData.Distance = atof(it->GetText());

	it = it->NextSiblingElement("velocity");
	planetData.Velocity = atof(it->GetText());

	it = it->NextSiblingElement("color");
	float r = it->FloatAttribute("r");
	float g = it->FloatAttribute("g");
	float b = it->FloatAttribute("b");
	planetData.Color = Color(r, g, b);

	m_PlanetData.push_back(planetData);
}
//================================================================================