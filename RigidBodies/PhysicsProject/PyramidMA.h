//======================================================================
//File: PyramidMA.h
//Author: Matt Struble
//======================================================================
#ifndef PYRAMID_MA_H
#define PYRAMID_MA_H
//======================================================================
#pragma once
//======================================================================
#include "MassAggregate.h"
//======================================================================
class PyramidMA : public MassAggregate
{
public:
	PyramidMA() {};
	~PyramidMA() {};

	void Initialize(Vector3D position, Color color = Color::GREY, float size = 1, float mass = 1);

protected:
	float m_Size;
};
#endif