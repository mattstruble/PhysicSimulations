//======================================================================
//File: PhysicObject.h
//Author: Matt Struble
//======================================================================
#ifndef PHYSIC_OBJECT_H
#define PHYSIC_OBJECT_H
//======================================================================
#pragma once
//======================================================================
#include "Matrix.h"
#include <GL\glut.h>
#include "Debug.h"
#include <string>
//======================================================================
class PhysicObject
{
public:
	PhysicObject();
	~PhysicObject();

	virtual void Initialize(float mass = 1, Vector3D position = Vector3D::Zero, Vector3D velocity = Vector3D::Zero, Vector3D acceleration = Vector3D::Zero, Vector3D rotation = Vector3D::Zero);
	virtual void Update(float gameTime);
	virtual void Draw();
	virtual void Reset();
	virtual void Clear();
	
	inline void SetPosition(Vector3D position) { m_Position = position; };
	inline void SetVelocity(Vector3D velocity) { m_Velocity = velocity; };
	inline void SetAcceleration(Vector3D acceleration) { m_Acceleration = acceleration; };
	inline void SetRotation(Vector3D rotation) { m_Rotation = rotation; };
	inline void SetMass(float mass) { m_Mass = mass; m_InverseMass = mass == 0 ? 1 : 1 / mass; };
	inline void AddForce(Vector3D force) { m_Force += force; };
	inline void SetRadius(float radius) { m_Radius = radius; };
	inline void SetRestitution(float restitution) { m_Restitution = restitution; };
	inline void SetName(std::string name) { m_Name = name; };

	inline Vector3D GetPosition() { return m_Position;  };
	inline Vector3D GetDrawPosition() { return m_DrawPosition; };
	inline Vector3D GetVelocity() { return m_Velocity;  };
	inline Vector3D GetAcceleration() { return m_Acceleration; };
	inline Vector3D GetRotation() { return m_Rotation; };
	inline float GetMass() { return m_Mass; };
	inline float GetInverseMass() { return m_InverseMass; };
	inline float GetRadius() { return m_Radius; };
	inline float GetRestitution() { return m_Restitution; };
	inline std::string GetName() { return m_Name; };

protected: 
	Vector3D m_DrawPosition;
	Vector3D m_Position;
	Vector3D m_Velocity;
	Vector3D m_Acceleration;
	Vector3D m_Rotation;
	Vector3D m_Force;

	Vector3D m_InitPosition;
	Vector3D m_InitVelocity;
	Vector3D m_InitAcceleration;
	Vector3D m_InitRotation;

	float m_Mass;
	float m_InverseMass;

	float m_Dampening;
	float m_Radius;
	float m_Restitution;

	std::string m_Name;
};
#endif