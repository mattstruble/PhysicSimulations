//======================================================================
//File: SolarSystemParser.h
//Author: Matt Struble
//======================================================================
#ifndef SOLAR_SYSTEM_PARSER_H
#define SOLAR_SYSTEM_PARSER_H
//======================================================================
#pragma once
//======================================================================
#include "tinyxml2.h"
#include "Color.h"
#include <string>
#include <vector>
//======================================================================
class SolarSystemParser
{
public:
	struct PlanetData
	{
		std::string Name;
		double Mass;
		float Radius;
		double Distance;
		double Velocity;
		Color Color;
	};

	SolarSystemParser() {};

	bool Parse(const std::string& path);

	const std::vector<PlanetData>& GetPlanetData() const { return m_PlanetData; };

private:
	void ParsePlanetData(tinyxml2::XMLElement* dataElement);

	std::vector<PlanetData> m_PlanetData;
};
#endif