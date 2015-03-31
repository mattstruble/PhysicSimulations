//======================================================================
//File: Debug.h
//Author: Matt Struble
//======================================================================
#ifndef DEBUG_H
#define DEBUG_H
//======================================================================
#pragma once
//======================================================================
#include <GL\glut.h>
#include <string>
#include <vector>
#include "Color.h"
//======================================================================
struct Log
{
	float TIME;
	char *STRING;
	Color COLOR;

	Log(Color c, char *string, float time)
	{
		COLOR = c;
		STRING = string;
		TIME = time;
	}

	bool Remove()
	{
		return TIME <= 0;
	}

	bool operator==(const Log& rhs)
	{
		return strcmp(STRING, rhs.STRING) == 0 && TIME == rhs.TIME && COLOR == rhs.COLOR;
	}

	void Clear()
	{
		delete [] STRING;
	}

};
//======================================================================
class Debug
{
public:
	Debug(float x = 0, float y = 715);
	~Debug();

	static void LOG(Color c, char *string, float time = 10);
	static void LOG(Color c, std::string , float time = 10);

	static void UPDATE(float dt);

	static void DRAW();

private:
	static std::vector<Log> m_Logs;
	static float m_StartX;
	static float m_StartY;
};
#endif