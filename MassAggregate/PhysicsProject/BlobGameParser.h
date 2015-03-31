//======================================================================
//File: BlobGameParser.h
//Author: Matt Struble
//======================================================================
#ifndef BLOB_GAME_PARSER_H
#define BLOB_GAME_PARSER_H
//======================================================================
#pragma once
//======================================================================
#include "tinyxml2.h"
#include "Color.h"
#include <string>
#include <vector>
#include "CubeMA.h"
#include "PyramidMA.h"
#include "TetrahedronMA.h"
#include "ConstantGravityForceGenerator.h"
#include "Plane.h"
//======================================================================
class BlobGameParser
{
public:
	

	BlobGameParser() {};

	bool Parse(const std::string& path);

	std::vector<MassAggregate*> GetMassAggregates() { return mp_MassAggregate; }

	ConstantGravityForceGenerator* GetGravity(){ return mp_Gravity; };
	GameObject* GetGround() { return mp_Ground; };

private:
	
	struct AggregateData
	{
		Vector3D Position;
		Color Color;
		float Size;
		float Mass;
	};

	void ParseGround(tinyxml2::XMLElement* dataElement);
	void ParseGravity(tinyxml2::XMLElement* dataElement);
	void ParseTetrahedronData(tinyxml2::XMLElement* dataElement);
	void ParseCubeData(tinyxml2::XMLElement* dataElement);
	void ParsePyramidData(tinyxml2::XMLElement* dataElement);

	AggregateData ParseAggregateData(tinyxml2::XMLElement* dataElement);
	
	std::vector<MassAggregate*> mp_MassAggregate;

	ConstantGravityForceGenerator* mp_Gravity;

	GameObject* mp_Ground;

	
};
#endif