//======================================================================
//File: Camera.cpp
//Author: Matt Struble
//======================================================================
#define _USE_MATH_DEFINES
//======================================================================
#include "Camera.h"
#include <gl\glut.h>
#include <math.h>
//======================================================================
Camera::Camera(int width, int height)
{
	m_Width = width;
	m_Height = height;

	m_Position = Vector3D(0, 10, 30);
	m_LastMousePosition = Vector2D(0, 0);
	m_Rotation = Vector2D(0, 0);

	m_MouseSpeed = 0.1f;
	m_CameraSpeed = 1.0f;

	m_TargetPosition = m_Position;

	m_InitPosition = m_Position;
	m_InitRotation = m_Rotation;

	m_RadianRotation = Vector2D(0, 0);

	m_MouseFree = false;
}

//--------------------------------------------------------------------------------
Camera::~Camera()
{
}

//--------------------------------------------------------------------------------
void Camera::HandleMouse(Vector2D mousePosition)
{
	Vector2D difference = mousePosition - m_LastMousePosition;
	m_LastMousePosition = mousePosition;

	m_Rotation.X = m_Rotation.X + difference.Y * m_MouseSpeed;
	m_Rotation.Y = m_Rotation.Y + difference.X * m_MouseSpeed;
}

//--------------------------------------------------------------------------------
void Camera::HandleMousePassive(int x, int y)
{
	if (m_MouseFree) return;

	if (x == m_Width / 2 && y == m_Height / 2) return;

	
}

//--------------------------------------------------------------------------------
void Camera::HandleKey(unsigned char key)
{
	Vector2D radian = Vector2D(0, 0);

	radian.Y = (float)(m_Rotation.Y / 180 * M_PI);
	radian.X = (float)(m_Rotation.X / 180 * M_PI);

	if (key == 'w')
	{

		m_TargetPosition.X += float(sin(radian.Y)) * m_CameraSpeed;
		m_TargetPosition.Z -= float(cos(radian.Y)) * m_CameraSpeed;
		m_TargetPosition.Y -= float(sin(radian.X)) * m_CameraSpeed;
	}

	if (key == 's')
	{
		m_TargetPosition.X -= float(sin(radian.Y)) * m_CameraSpeed;
		m_TargetPosition.Z += float(cos(radian.Y)) * m_CameraSpeed;
		m_TargetPosition.Y += float(sin(radian.X)) * m_CameraSpeed;
	}

	if (key == 'a')
	{
		m_TargetPosition.X -= float(cos(radian.Y)) * m_CameraSpeed;
		m_TargetPosition.Z -= float(sin(radian.Y)) * m_CameraSpeed;
	}

	if (key == 'd')
	{
		m_TargetPosition.X += float(cos(radian.Y)) * m_CameraSpeed;
		m_TargetPosition.Z += float(sin(radian.Y)) * m_CameraSpeed;
	}
}

//--------------------------------------------------------------------------------
void Camera::Update()
{
	
	if (m_TargetObject != nullptr)
	{
		SetTarget(m_TargetObject->GetDrawPosition());
	}

	glLoadIdentity();
	glRotatef(m_Rotation.X, 1.0, 0.0, 0.0);
	glRotatef(m_Rotation.Y, 0.0, 1.0, 0.0);
	glTranslated(-m_Position.X, -m_Position.Y, -m_Position.Z);

	m_Position = Vector3D::Lerp(m_Position, m_TargetPosition, 0.1f);
}

//--------------------------------------------------------------------------------
void Camera::SetTarget(Vector3D target)
{
	m_TargetPosition = target;

	m_TargetPosition.Y -= 2;

	m_Rotation = Vector2D(270, 0);
}

//--------------------------------------------------------------------------------
void Camera::SetTarget(PhysicObject* object)
{
	m_TargetObject = object;

	if (m_TargetObject != nullptr)
	{
		SetTarget(m_TargetObject->GetDrawPosition());
	}
	else
	{
		SetTarget(m_InitPosition);
	}
}

//--------------------------------------------------------------------------------
void Camera::moveBack(float amt)
{
	
}

//--------------------------------------------------------------------------------
void Camera::moveForward(float amt)
{
	
}

//--------------------------------------------------------------------------------
void Camera::moveRight(float amt)
{
	
}

//--------------------------------------------------------------------------------
void Camera::moveLeft(float amt)
{
	
}
//================================================================================