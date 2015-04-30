//======================================================================
//File: Planet.cpp
//Author: Matt Struble
//======================================================================
#include "Planet.h"
//======================================================================
Planet::Planet()
{

}

//--------------------------------------------------------------------------------
Planet::~Planet()
{
}

//--------------------------------------------------------------------------------
void Planet::Initialize(std::string name, float radius, float mass, Vector3D position, Vector3D velocity)
{
	PhysicObject::Initialize(mass, position, velocity);
	m_Name = name;
	m_Radius = radius;

	m_Primitive = new Sphere(radius, 36, 36);

	std::string output = name + " Initialized: Radius(" + std::to_string(radius) + "), Mass(" + std::to_string(mass) + ")";

	Debug::LOG(Color::LIME, output);

	m_DebugText.push_back("Acceleration");
	m_DebugText.push_back("Velocity");
	m_DebugText.push_back("Position");
	m_DebugText.push_back(m_Name);

	m_DrawPosition = Vector3D(position);
	m_DrawPosition *= 1.0e-7f;

}

//--------------------------------------------------------------------------------
void Planet::Update(float dt)
{
	PhysicObject::Update(dt);
}

//--------------------------------------------------------------------------------
void Planet::Draw()
{
	m_DrawPosition = m_Position * 1.0e-8f;

	glPushMatrix();

	glTranslatef(m_DrawPosition.X, m_DrawPosition.Y, m_DrawPosition.Z);
	m_Primitive->Draw();

	//DrawDebugText();

	glPopMatrix();
	
	
}

//--------------------------------------------------------------------------------
void Planet::DrawDebugText()
{
	Color color = m_Primitive->GetColor();
	
	glColor3f(color.R, color.G, color.B);
	
	m_DebugText[0] = "Acceleration: " + m_Acceleration.ToString();
	m_DebugText[1] = "Velocity: " + m_Velocity.ToString();
	m_DebugText[2] = "Position: " + m_Position.ToString();


	for (unsigned int i = 0; i < m_DebugText.size(); i++)
	{
		glRasterPos3f(m_DrawPosition.X - m_Velocity.X, m_DrawPosition.Y + m_Radius + (i / 10.0f), m_DrawPosition.Z + m_Velocity.Z);

		const char* cstr = m_DebugText[i].c_str();

		int len;
		len = (int)strlen(cstr);
		for (int i = 0; i < len; i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, cstr[i]);
		}
	}
}
//================================================================================