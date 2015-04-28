//======================================================================
//File: GlutTime.h
//Author: Jake Ellenberg - used with permission
//Edited: Matt Struble
//Purpose: Keep track of time for a constant frame rate
//======================================================================
#ifndef GLUTTIME_H
#define GLUTTIME_H
//======================================================================
#pragma once
//======================================================================
const unsigned int TARGET_FPS = 60;
const double TIME_PER_FRAME = 1000.0 / TARGET_FPS;
//======================================================================
class GlutTime
{
public:
	GlutTime();
	~GlutTime();
	void Init();
	bool UpdateTime();
	void IncrementFrame();
	float GetDeltaTime();
private:
	int m_StartTime;
	int m_CurrentFrameNum;
	int m_LastFrameEnd;
};
#endif