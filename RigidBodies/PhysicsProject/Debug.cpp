//======================================================================
//File: Debug.cpp
//Author: Matt Struble
//======================================================================
#include "Debug.h"
#include <iostream>
//======================================================================
float Debug::m_StartX = 0;
float Debug::m_StartY = 0;
std::vector<Log> Debug::m_Logs;
//======================================================================
Debug::Debug(float x, float y)
{
	Debug::m_StartX = x;
	Debug::m_StartY = y;
}

//--------------------------------------------------------------------------------
Debug::~Debug()
{
	for (unsigned int i = 0; i < Debug::m_Logs.size(); i++)
	{
		Debug::m_Logs[i].Clear();
	}

	Debug::m_Logs.clear();
}

//--------------------------------------------------------------------------------
void Debug::LOG(Color c, char *string, float time)
{
	Debug::m_Logs.push_back(Log(c, string, time));
	std::cout << "Debug: " << string << std::endl;
}

//--------------------------------------------------------------------------------
void Debug::LOG(Color c, std::string string, float time)
{
	char *cstr = new char[string.length() + 1];
	strcpy_s(cstr, string.length() + 1, string.c_str());
	LOG(c, cstr, time);
}

//--------------------------------------------------------------------------------
void Debug::UPDATE(float dt)
{
	for (int i = Debug::m_Logs.size() - 1; i >= 0; i--)
	{
		Debug::m_Logs[i].TIME -= dt;

		if (Debug::m_Logs[i].Remove())
		{
			std::cout << "Removing Debug: " << Debug::m_Logs[i].STRING << std::endl;
			auto it = std::find(Debug::m_Logs.begin(), Debug::m_Logs.end(), m_Logs[i]);
			if (it != Debug::m_Logs.end())
			{
				Debug::m_Logs.erase(it);
			}
		}
	}
}

//--------------------------------------------------------------------------------
void Debug::DRAW()
{
	for (unsigned int i = 0; i < Debug::m_Logs.size(); i++)
	{
		Log tmpLog = Debug::m_Logs[i];

		glColor3f(tmpLog.COLOR.R, tmpLog.COLOR.G, tmpLog.COLOR.B);
		glRasterPos2i((int)m_StartX, (int)m_StartY - (10 * i));
		
		int len;
		len = (int)strlen(tmpLog.STRING);
		for (int j = 0; j < len; j++)
		{
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, tmpLog.STRING[j]);
		}

	}
}
//================================================================================