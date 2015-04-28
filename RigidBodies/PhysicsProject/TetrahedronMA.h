//======================================================================
//File: TetrahedronMA.h
//Author: Matt Struble
//======================================================================
#ifndef TETRAHEDRON_MA_H
#define TETRAHEDRON_MA_H
//======================================================================
#pragma once
//======================================================================
#include "MassAggregate.h"
//======================================================================
class TetrahedronMA : public MassAggregate
{
public:
	TetrahedronMA() {};
	~TetrahedronMA() {};

	void Initialize(Vector3D position, Color color = Color::GREY, float size = 1, float mass = 1);

protected:
	float m_Size;
};
#endif