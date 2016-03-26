//======================================================================
//File: Camera.h
//Author: Matt Struble
//======================================================================
#ifndef CAMERA_H
#define CAMERA_H
//======================================================================
#pragma once
//======================================================================
#include "Vector3D.h"
#include "Vector2D.h"
#include "PhysicObject.h"
//======================================================================
class Camera
{
public:
	Camera(int width, int height);
	~Camera();

	void HandleMouse(Vector2D mousePos);
	void HandleKeyPressed(unsigned char key);
	void HandleKeyReleased(unsigned char key);
	void Update();

	void SetTarget(Vector3D target);
	void SetTarget(PhysicObject* target);
	inline void SetYaw(float yaw) { m_Yaw = yaw; };
	inline void SetPitch(float pitch) { m_Pitch = pitch; };

	inline float GetYaw() const { return m_Yaw; };
	inline float GetPitch() const { return m_Pitch; };

	Vector3D GetDirection();

private: 
	void move();

private:
	Vector2D m_LastMousePosition;
	Vector2D m_RadianRotation;
	Vector2D m_InitRotation;
	Vector2D m_Rotation;
	Vector2D m_TargetRotation;

	Vector3D m_Position;
	Vector3D m_TargetPosition;
	Vector3D m_InitPosition;

	float m_MouseSpeed;
	float m_CameraSpeed;
	float m_Yaw;
	float m_Pitch;

	PhysicObject* m_TargetObject;

	int m_Width;
	int m_Height;

	bool m_MouseFree;

	bool m_MoveForward;
	bool m_MoveBackward;
	bool m_MoveLeft;
	bool m_MoveRight;
	bool m_MoveUp;
	bool m_MoveDown;
};
#endif