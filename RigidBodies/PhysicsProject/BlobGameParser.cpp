//======================================================================
//File: BlobGameParser.cpp
//Author: Matt Struble
//======================================================================
#include "BlobGameParser.h"
//======================================================================
using namespace tinyxml2;
//======================================================================
bool BlobGameParser::Parse(const std::string& path)
{
	XMLDocument document;

	document.LoadFile(path.c_str());

	XMLElement* root = document.FirstChildElement("blobgame");

	for (XMLElement* it = root->FirstChildElement(); it != NULL; it = it->NextSiblingElement())
	{
		if (static_cast<std::string>(it->Value()) == "ground" )
			ParseGround(it);
		else if (static_cast<std::string>(it->Value()) == "gravity")
			ParseGravity(it);
		else if (static_cast<std::string>(it->Value()) == "tetrahedron")
			ParseTetrahedronData(it);
		else if (static_cast<std::string>(it->Value()) == "cube")
			ParseCubeData(it);
		else if (static_cast<std::string>(it->Value()) == "pyramid")
			ParsePyramidData(it);
	}

	return true;
}

void BlobGameParser::ParseGround(XMLElement* dataElement)
{
	float x = dataElement->FloatAttribute("x");
	float y = dataElement->FloatAttribute("y");
	float z = dataElement->FloatAttribute("z");

	Plane* groundPlane = new Plane(Vector3D(x, y, z));

	mp_Ground = new GameObject();
	mp_Ground->Initialize(Vector3D(0, -y, 0));
	mp_Ground->SetPrimitive(groundPlane);
}

void BlobGameParser::ParseGravity(XMLElement* dataElement)
{
	float x = dataElement->FloatAttribute("x");
	float y = dataElement->FloatAttribute("y");
	float z = dataElement->FloatAttribute("z");

	mp_Gravity = new ConstantGravityForceGenerator(Vector3D(x, y, z));
}

BlobGameParser::AggregateData BlobGameParser::ParseAggregateData(XMLElement* dataElement)
{
	AggregateData data;

	XMLElement* it = dataElement->FirstChildElement("position");
	data.Position = Vector3D(it->FloatAttribute("x"), it->FloatAttribute("y"), it->FloatAttribute("z"));

	it = it->NextSiblingElement("color");
	data.Color = Color(it->FloatAttribute("r"), it->FloatAttribute("g"), it->FloatAttribute("b"));

	it = it->NextSiblingElement("size");
	data.Size = atof(it->GetText());

	it = it->NextSiblingElement("mass");
	data.Mass = atof(it->GetText());

	return data;
}

void BlobGameParser::ParseCubeData(XMLElement* dataElement)
{
	AggregateData data = ParseAggregateData(dataElement);

	CubeMA* ma = new CubeMA();
	ma->Initialize(data.Position, data.Color, data.Size, data.Mass);

	mp_MassAggregate.push_back(ma);
}

void BlobGameParser::ParsePyramidData(XMLElement* dataElement)
{
	AggregateData data = ParseAggregateData(dataElement);

	PyramidMA* ma = new PyramidMA();
	ma->Initialize(data.Position, data.Color, data.Size, data.Mass);

	mp_MassAggregate.push_back(ma);
}

void BlobGameParser::ParseTetrahedronData(XMLElement* dataElement)
{
	AggregateData data = ParseAggregateData(dataElement);

	TetrahedronMA* ma = new TetrahedronMA();
	ma->Initialize(data.Position, data.Color, data.Size, data.Mass);

	mp_MassAggregate.push_back(ma);
}