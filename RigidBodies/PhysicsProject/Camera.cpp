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
	m_LastMousePosition = Vector2D((float)(int)((m_Width / 2.0f)), (float)(int)((m_Height / 2.0f)));
	m_Rotation = Vector2D(0, 0);

	m_MouseSpeed = 0.1f;
	m_CameraSpeed = 2.0f / 10.0f;

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
void Camera::HandleKeyPressed(unsigned char key)
{
	switch (key)
	{
	case ('w') :
		m_MoveForward = true;
		break;
	case ('s') :
		m_MoveBackward = true;
		break;
	case ('a') :
		m_MoveLeft = true;
		break;
	case ('d') :
		m_MoveRight = true;
		break;
	case ('q') :
		m_MoveUp = true;
		break;
	case ('e') :
		m_MoveDown = true;
		break;
	}
}

//--------------------------------------------------------------------------------
void Camera::HandleKeyReleased(unsigned char key)
{
	switch (key)
	{
	case ('w') :
		m_MoveForward = false;
		break;
	case ('s') :
		m_MoveBackward = false;
		break;
	case ('a') :
		m_MoveLeft = false;
		break;
	case ('d') :
		m_MoveRight = false;
		break;
	case ('q') :
		m_MoveUp = false;
		break;
	case ('e') :
		m_MoveDown = false;
		break;
	}
}

//--------------------------------------------------------------------------------
void Camera::move()
{
	Vector2D radian = Vector2D(0, 0);

	radian.Y = (float)(m_Rotation.Y / 180 * M_PI);
	radian.X = (float)(m_Rotation.X / 180 * M_PI);

	if (m_MoveForward && !m_MoveBackward)
	{

		m_TargetPosition.X += float(sin(radian.Y)) * m_CameraSpeed;
		m_TargetPosition.Z -= float(cos(radian.Y)) * m_CameraSpeed;
		m_TargetPosition.Y -= float(sin(radian.X)) * m_CameraSpeed;
	}
	else if (m_MoveBackward && !m_MoveForward)
	{
		m_TargetPosition.X -= float(sin(radian.Y)) * m_CameraSpeed;
		m_TargetPosition.Z += float(cos(radian.Y)) * m_CameraSpeed;
		m_TargetPosition.Y += float(sin(radian.X)) * m_CameraSpeed;
	}

	if (m_MoveLeft && !m_MoveRight)
	{
		m_TargetPosition.X -= float(cos(radian.Y)) * m_CameraSpeed;
		m_TargetPosition.Z -= float(sin(radian.Y)) * m_CameraSpeed;
	}
	else if (m_MoveRight && !m_MoveLeft)
	{
		m_TargetPosition.X += float(cos(radian.Y)) * m_CameraSpeed;
		m_TargetPosition.Z += float(sin(radian.Y)) * m_CameraSpeed;
	}

	if (m_MoveUp && !m_MoveDown)
	{
		m_TargetPosition.Y -= float(sin(radian.X)) * m_CameraSpeed;
	}
	else if (m_MoveDown && !m_MoveUp)
	{
		m_TargetPosition.Y += float(sin(radian.X)) * m_CameraSpeed;
	}
}

//--------------------------------------------------------------------------------
void Camera::Update()
{
	
	if (m_TargetObject != nullptr)
	{
		SetTarget(m_TargetObject->GetDrawPosition());
	}
	else {
		move();
	}

	m_Position = Vector3D::Lerp(m_Position, m_TargetPosition, 0.1f);

	glLoadIdentity();
	glRotatef(m_Rotation.X, 1.0, 0.0, 0.0);
	glRotatef(m_Rotation.Y, 0.0, 1.0, 0.0);
	glTranslated(-m_Position.X, -m_Position.Y, -m_Position.Z);

	m_LastMousePosition = Vector2D((float)(int)((m_Width / 2.0f)), (float)(int)((m_Height / 2.0f)));
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
//================================================================================