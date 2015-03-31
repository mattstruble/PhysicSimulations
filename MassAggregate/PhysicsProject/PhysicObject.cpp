//======================================================================
//File: PhysicObject.cpp
//Author: Matt Struble
//======================================================================

#include "PhysicObject.h"

//======================================================================
PhysicObject::PhysicObject()
:m_Dampening(0.999f)
{
	m_Acceleration = Vector3D::Zero;
	m_Velocity = Vector3D::Zero;
	m_Acceleration = Vector3D::Zero;
	m_Rotation = Vector3D::Zero;
}

//--------------------------------------------------------------------------------
PhysicObject::~PhysicObject()
{

}

//--------------------------------------------------------------------------------
void PhysicObject::Initialize(double mass, Vector3D position, Vector3D velocity, Vector3D acceleration, Vector3D rotation)
{
	m_Mass = mass;
	m_InverseMass = mass == 0 ? 1 : 1 / mass;

	m_Position = position;
	m_Velocity = velocity;
	m_Acceleration = acceleration;
	m_Rotation = rotation;

	m_InitPosition = m_Position;
	m_InitVelocity = m_Velocity;
	m_InitAcceleration = m_Acceleration;
	m_InitRotation = m_Rotation;
}

//--------------------------------------------------------------------------------
void PhysicObject::Update(float gameTime)
{
	m_Position += m_Velocity * static_cast<double>(gameTime);
	m_Acceleration = m_Force * static_cast<double>(m_InverseMass);
	m_Velocity += m_Acceleration * static_cast<double>(gameTime);

	//m_Velocity *= m_Dampening;

	m_Force = Vector3D::Zero;
}

//--------------------------------------------------------------------------------
void PhysicObject::Draw()
{

}

//--------------------------------------------------------------------------------
void PhysicObject::Reset()
{
	m_Position = m_InitPosition;
	m_Velocity = m_InitVelocity;
	m_Acceleration = m_InitAcceleration;
	m_Rotation = m_InitRotation;

	m_Force = Vector3D::Zero;
}

void PhysicObject::Clear()
{

}
//======================================================================