//======================================================================
//File: GlutTime.cpp
//Author: Jake Ellenberg - used with permission
//Edited: Matt Struble
//Purpose: Keep track of time for a constant frame rate
//======================================================================
#include "GlutTime.h"
#include <iostream>
#include <Windows.h>
#include <gl\glut.h>
//================================================================================
GlutTime::GlutTime()
{

}

//--------------------------------------------------------------------------------
GlutTime::~GlutTime()
{

}

//--------------------------------------------------------------------------------
void GlutTime::Init()
{
	m_LastFrameEnd = m_StartTime = glutGet(GLUT_ELAPSED_TIME);
	m_CurrentFrameNum = 0;
}

//--------------------------------------------------------------------------------
bool GlutTime::UpdateTime()
{
	double endFrameTime = m_StartTime + (m_CurrentFrameNum + 1) * TIME_PER_FRAME;
	double endRenderTime = glutGet(GLUT_ELAPSED_TIME);
	double idleTime = endFrameTime - endRenderTime;
	if (idleTime <= 0.0)
	{
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------------
void GlutTime::IncrementFrame()
{
	m_CurrentFrameNum++;
	m_LastFrameEnd = glutGet(GLUT_ELAPSED_TIME);;
}

//--------------------------------------------------------------------------------
float GlutTime::GetDeltaTime()
{
	int renderTime = glutGet(GLUT_ELAPSED_TIME);

	return (renderTime - m_LastFrameEnd) / 1000.0f;
}
//================================================================================