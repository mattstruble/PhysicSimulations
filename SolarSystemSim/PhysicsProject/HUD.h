//======================================================================
//File: HUD.h
//Author: Matt Struble
//======================================================================
#ifndef HUD_H
#define HUD_H
//======================================================================
#pragma once
//======================================================================
#include <gl\glut.h>
#include "Debug.h"
#include "PhysicObject.h"
//======================================================================
class HUD
{
public:
	HUD();
	~HUD();

	void Init(int x, int y);
	void Draw();
	void Update(float dt);
	void HandleKey(unsigned char key);
	
	inline void SetTarget(PhysicObject* object) { mp_TargetObject = object; };

private:

	void DrawObjectInfo();

	Debug* mp_Debugger;
	bool m_DebugOn;
	PhysicObject* mp_TargetObject;
	std::vector<char*> m_ObjectText;

	int m_ObjectTextX;
	int m_ObjectTextY;
};
#endif