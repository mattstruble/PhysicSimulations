//======================================================================
//File: CubeMA.h
//Author: Matt Struble
//======================================================================
#ifndef CUBE_MA_H
#define CUBE_MA_H
//======================================================================
#pragma once
//======================================================================
#include "MassAggregate.h"
//======================================================================
class CubeMA : public MassAggregate
{
public:
	CubeMA() {};
	~CubeMA() {};

	void Initialize(Vector3D position, Color color = Color::GREY, float size = 1, float mass = 1);

protected:

	float m_Size;
};
#endif