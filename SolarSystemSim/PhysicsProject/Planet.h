//======================================================================
//File: Planet.h
//Author: Matt Struble
//======================================================================
#ifndef PLANET_H
#define PLANET_H
//======================================================================
#pragma once
//======================================================================
#include "PhysicObject.h"
#include "Sphere.h"
#include <string>
//======================================================================
class Planet : public PhysicObject
{
public:
	Planet();
	~Planet();

	void Initialize(std::string name = "", float radius = 1, double mass = 1, Vector3D position = Vector3D::Zero, Vector3D velocity = Vector3D::Zero);
	void Draw();
	void Update(float dt);

	inline void SetRadius(float radius) { m_Radius = radius; };
	inline void SetColor(Color c) { mp_Sphere->SetColor(c); };
	
	

	inline float GetRadius() { return m_Radius; };

private:
	void DrawDebugText();

	float m_Radius;
	float m_InitRadius;
	Sphere* mp_Sphere;
	std::vector<std::string> m_DebugText;

};
#endif