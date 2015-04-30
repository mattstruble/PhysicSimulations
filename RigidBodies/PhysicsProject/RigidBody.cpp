//======================================================================
//File: RigidBody.cpp
//Author: Matt Struble
//======================================================================
#include "RigidBody.h"
#include <math.h>
//=============================================================================
RigidBody::RigidBody()
{
	m_TransformationMatrix = Matrix(4, 4);
	m_InverseInertiaTensor = Matrix(3, 3);
	m_InverseInertiaTensorWorld = Matrix(3, 3);
	m_CollisionType = e_CollisionType::SPHERE;
}

//-----------------------------------------------------------------------------
RigidBody::~RigidBody()
{

}

//-----------------------------------------------------------------------------
void RigidBody::Initialize(float mass, Vector3D initialPosition, Vector3D initialVelocity, Vector3D initialAcceleration, Vector3D initialRotation, float dampening, float angularDampening)
{
	m_Mass = mass;
	m_InverseMass = 1 / mass;

	m_LinearDampening = dampening;
	m_AngularDampening = angularDampening;

	m_InitialPosition = initialPosition;
	m_Position = m_InitialPosition;
	m_InitialVelocity = initialVelocity;
	m_Velocity = m_InitialVelocity;
	m_InitialAcceleration = initialAcceleration;
	m_LastFrameAcceleration = m_InitialAcceleration;
	m_Acceleration = m_InitialAcceleration;
	m_InitialRotation = initialRotation;
	m_Rotation = m_InitialRotation;

	m_IsAwake = false;

	m_TransformationMatrix = Matrix(4, 4);
}

//-----------------------------------------------------------------------------
void RigidBody::Update(float duration)
{
	m_LastFrameAcceleration = m_Acceleration;
	m_LastFrameAcceleration += (m_ForceAccum * m_InverseMass);

	Vector3D angularAcceleration = m_InverseInertiaTensorWorld.Transform(m_TorqueAccum);

	m_Velocity += (m_LastFrameAcceleration * duration);

	m_Rotation += (angularAcceleration * duration);

	m_Velocity *= (pow(m_LinearDampening, duration));
	m_Rotation *= (pow(m_AngularDampening, duration));

	m_Position += (m_Velocity * duration);

	m_Orientation.VectorScaling(m_Rotation, duration);

	CalculateDerivedData();

	Clear();
}

//-----------------------------------------------------------------------------
void RigidBody::Reset()
{
	m_Position = m_InitialPosition;
	m_Velocity = m_InitialVelocity;
	m_LastFrameAcceleration = m_InitialAcceleration;
	m_Acceleration = m_InitialAcceleration;
	m_Rotation = m_InitialRotation;
}

//-----------------------------------------------------------------------------
void RigidBody::Clear()
{
	m_ForceAccum = Vector3D::Zero;
	m_TorqueAccum = Vector3D::Zero;
}

//-----------------------------------------------------------------------------
void RigidBody::AddForce(const Vector3D &force)
{
	m_ForceAccum += force;
	m_IsAwake = true;
}

//-----------------------------------------------------------------------------
void RigidBody::AddForcePoint(const Vector3D &force, const Vector3D &point)
{
	Vector3D worldPoint = point;
	worldPoint -= m_Position;

	m_ForceAccum += force;
	m_TorqueAccum += Vector3D::Cross(worldPoint, force);

	m_IsAwake = true;
}

//-----------------------------------------------------------------------------
void RigidBody::AddForceBodyPoint(const Vector3D &force, const Vector3D &point)
{
	Vector3D worldPoint = GetPointInWorldSpace(point);
	AddForcePoint(force, worldPoint);
	m_IsAwake = true;
}

//-----------------------------------------------------------------------------
void RigidBody::AddVelocity(const Vector3D& deltaVelocity)
{
	m_Velocity += deltaVelocity;
}

//-----------------------------------------------------------------------------
void RigidBody::AddRotation(const Vector3D& deltaRotation)
{
	m_Rotation += deltaRotation;
}

//-----------------------------------------------------------------------------
void RigidBody::CalculateDerivedData()
{
	m_Orientation.Normalize();

	calculateTransformMatrix(m_TransformationMatrix, m_Position, m_Orientation);

	transformInertiaTensor(m_InverseInertiaTensorWorld,  m_InverseInertiaTensor, m_TransformationMatrix);
}

//-----------------------------------------------------------------------------
void RigidBody::calculateTransformMatrix(Matrix& transformMatrix, const Vector3D& position, const Quaternion& orientation)
{
	float val1 = 1 - 2 * orientation.J * orientation.J - 2 * orientation.K * orientation.K;
	transformMatrix.Set(0, 0, val1);
	float val2 = 2 * orientation.I * orientation.J - 2 * orientation.R * orientation.K;
	transformMatrix.Set(0, 1, val2);
	float val3 = 2 * orientation.I * orientation.K + 2 * orientation.R * orientation.J;
	transformMatrix.Set(0, 2, val3);
	float val4 = position.X;
	transformMatrix.Set(0, 3, val4);

	float val5 = 2 * orientation.I * orientation.J + 2 * orientation.R * orientation.K;
	transformMatrix.Set(1, 0, val5);
	float val6 = 1 - 2 * orientation.I * orientation.I - 2 * orientation.K * orientation.K;
	transformMatrix.Set(1, 1, val6);
	float val7 = 2 * orientation.J * orientation.K - 2 * orientation.R * orientation.I;
	transformMatrix.Set(1, 2, val7);
	float val8 = position.Y;
	transformMatrix.Set(1, 3, val8);

	float val9 = 2 * orientation.I * orientation.K - 2 * orientation.R * orientation.J;
	transformMatrix.Set(2, 0, val9);
	float val10 = 2 * orientation.J * orientation.K + 2 * orientation.R * orientation.I;
	transformMatrix.Set(2, 1, val10);
	float val11 = 1 - 2 * orientation.I * orientation.I - 2 * orientation.J * orientation.J;
	transformMatrix.Set(2, 2, val11);
	float val12 = position.Z;
	transformMatrix.Set(2, 3, val12);
}

//-----------------------------------------------------------------------------
void RigidBody::transformInertiaTensor(Matrix& iitWorld, const Matrix& iitBody, const Matrix& rotationMatrix)
{
	float t4 = rotationMatrix.Get(0) * iitBody.Get(0) + rotationMatrix.Get(1) * iitBody.Get(3) + rotationMatrix.Get(2) * iitBody.Get(6);
	float t9 = rotationMatrix.Get(0) * iitBody.Get(1) + rotationMatrix.Get(1) * iitBody.Get(4) + rotationMatrix.Get(2) * iitBody.Get(7);
	float t14 = rotationMatrix.Get(0) * iitBody.Get(2) + rotationMatrix.Get(1) * iitBody.Get(5) + rotationMatrix.Get(2) * iitBody.Get(8);
	float t28 = rotationMatrix.Get(4) * iitBody.Get(0) + rotationMatrix.Get(5) * iitBody.Get(3) + rotationMatrix.Get(6) * iitBody.Get(6);
	float t33 = rotationMatrix.Get(4) * iitBody.Get(1) + rotationMatrix.Get(5) * iitBody.Get(4) + rotationMatrix.Get(6) * iitBody.Get(7);
	float t38 = rotationMatrix.Get(4) * iitBody.Get(2) + rotationMatrix.Get(5) * iitBody.Get(5) + rotationMatrix.Get(6) * iitBody.Get(8);
	float t52 = rotationMatrix.Get(8) * iitBody.Get(0) + rotationMatrix.Get(9) * iitBody.Get(3) + rotationMatrix.Get(10) * iitBody.Get(6);
	float t57 = rotationMatrix.Get(8) * iitBody.Get(1) + rotationMatrix.Get(9) * iitBody.Get(4) + rotationMatrix.Get(10) * iitBody.Get(7);
	float t62 = rotationMatrix.Get(8) * iitBody.Get(2) + rotationMatrix.Get(9) * iitBody.Get(5) + rotationMatrix.Get(10) * iitBody.Get(8);

	float val0 = t4 * rotationMatrix.Get(0) + t9 * rotationMatrix.Get(1) + t14 * rotationMatrix.Get(2);
	iitWorld.Set(0, val0);
	float val1 = t4 * rotationMatrix.Get(4) + t9 * rotationMatrix.Get(5) + t14 * rotationMatrix.Get(6);
	iitWorld.Set(1, val1);
	float val2 = t4 * rotationMatrix.Get(8) + t9 * rotationMatrix.Get(9) + t14 * rotationMatrix.Get(10);
	iitWorld.Set(2, val2);
	float val3 = t28 * rotationMatrix.Get(0) + t33 * rotationMatrix.Get(1) + t38 * rotationMatrix.Get(2);
	iitWorld.Set(3, val3);
	float val4 = t28 * rotationMatrix.Get(4) + t33 * rotationMatrix.Get(5) + t38 * rotationMatrix.Get(6);
	iitWorld.Set(4, val4);
	float val5 = t28 * rotationMatrix.Get(8) + t33 * rotationMatrix.Get(9) + t38 * rotationMatrix.Get(10);
	iitWorld.Set(5, val5);
	float val6 = t52 * rotationMatrix.Get(0) + t57 * rotationMatrix.Get(1) + t62 * rotationMatrix.Get(2);
	iitWorld.Set(6, val6);
	float val7 = t52 * rotationMatrix.Get(4) + t57 * rotationMatrix.Get(5) + t62 * rotationMatrix.Get(6);
	iitWorld.Set(7, val7);
	float val8 = t52 * rotationMatrix.Get(8) + t57 * rotationMatrix.Get(9) + t62 * rotationMatrix.Get(10);
	iitWorld.Set(8, val8);
}