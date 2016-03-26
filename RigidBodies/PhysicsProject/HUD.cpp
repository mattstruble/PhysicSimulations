//======================================================================
//File: HUD.cpp
//Author: Matt Struble
//======================================================================
#include "HUD.h"
//======================================================================
HUD::HUD()
{
	m_DebugOn = true;
	mp_TargetObject = nullptr;

	m_ObjectText.push_back("Name");
	m_ObjectText.push_back("Draw Position");
	m_ObjectText.push_back("Actual Position");
	m_ObjectText.push_back("Velocity");
	m_ObjectText.push_back("Acceleration");
}

//--------------------------------------------------------------------------------
HUD::~HUD()
{

}

//--------------------------------------------------------------------------------
void HUD::Init(int x, int y)
{
	mp_Debugger = new Debug();

	m_ObjectTextX = x;
	m_ObjectTextY = y;
}

//--------------------------------------------------------------------------------
void HUD::Draw()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, 720, 720, 0.0, -1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	if (m_DebugOn)
		Debug::DRAW();

	if (mp_TargetObject != nullptr)
		DrawObjectInfo();

	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

//--------------------------------------------------------------------------------
void HUD::Update(float dt)
{
	Debug::UPDATE(dt);
}

//--------------------------------------------------------------------------------
void HUD::HandleKeyPressed(unsigned char key)
{
	if (key == '`')
	{
		m_DebugOn = !m_DebugOn;

		if (m_DebugOn)
			Debug::LOG(Color::ORANGE, "Debugger On");
	}
}

//--------------------------------------------------------------------------------
void HUD::DrawObjectInfo()
{
	std::string nameString = mp_TargetObject->GetName();
	std::string posString = "Draw Position: " + mp_TargetObject->GetDrawPosition().ToString();
	std::string posAString = "Actual Position: " + mp_TargetObject->GetPosition().ToString();
	std::string velString = "Velocity: " + mp_TargetObject->GetVelocity().ToString();
	std::string accString = "Acceleration: " + mp_TargetObject->GetAcceleration().ToString();

	char *cstrName = new char[nameString.length() + 1];
	strcpy_s(cstrName, nameString.length() + 1, nameString.c_str());

	char *cstrPos = new char[posString.length() + 1];
	strcpy_s(cstrPos, posString.length() + 1, posString.c_str());

	char *cstrAPos = new char[posAString.length() + 1];
	strcpy_s(cstrAPos, posAString.length() + 1, posAString.c_str());

	char *cstrVel = new char[velString.length() + 1];
	strcpy_s(cstrVel, velString.length() + 1, velString.c_str());

	char *cstrAcc = new char[accString.length() + 1];
	strcpy_s(cstrAcc, accString.length() + 1, accString.c_str());

	m_ObjectText[0] = cstrName;
	m_ObjectText[1] = cstrPos;
	m_ObjectText[2] = cstrAPos;
	m_ObjectText[3] = cstrVel;
	m_ObjectText[4] = cstrAcc;

	Color color = Color::WHITE;

	for (unsigned int i = 0; i < m_ObjectText.size(); i++)
	{
		glColor3f(color.R, color.G, color.B);
		glRasterPos2i(m_ObjectTextX, m_ObjectTextY + (10 * i));

		int len;
		len = (int)strlen(m_ObjectText[i]);
		for (int j = 0; j < len; j++)
		{
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, m_ObjectText[i][j]);
		}
	}
}
//================================================================================