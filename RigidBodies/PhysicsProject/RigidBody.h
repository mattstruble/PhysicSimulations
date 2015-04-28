//======================================================================
//File: RigidBody.h
//Author: Matt Struble
//======================================================================
#ifndef RIGID_BODY_H
#define RIGID_BODY_H
//=============================================================================
#pragma once
//=============================================================================
#include "Vector3D.h"
#include "Quaternion.h"
#include "Matrix.h"
#include "RBCollisionSphere.h"
//=============================================================================
class RigidBody
{

public:
	RigidBody();
	~RigidBody();

	virtual void Initialize(float mass, Vector3D initialPosition = Vector3D::Zero, Vector3D initialVelocity = Vector3D::Zero, Vector3D initialAcceleration = Vector3D::Zero, Vector3D initialRotation = Vector3D::Zero, float linearDampening = 1, float angularDampening = 1);
	void Integrate(float duration);
	void Reset();
	void Clear();

	void AddForce(const Vector3D& force);
	void AddForcePoint(const Vector3D& force, const Vector3D& point);
	void AddForceBodyPoint(const Vector3D& force, const Vector3D& point);

	void AddVelocity(const Vector3D& deltaVelocity);
	void AddRotation(const Vector3D& deltaRotation);
	
	inline void SetAwake() { m_IsAwake = true; };
	inline void SetIntertiaTensor(const Matrix& inertiaTensor) { m_InverseInertiaTensor = inertiaTensor.Inverse(); };
	inline void SetPosition(Vector3D position) { m_Position = position; };
	inline void SetOrientation(Quaternion orientation) { m_Orientation = orientation; };

	inline Quaternion GetOrientation() { return m_Orientation; };
	inline Matrix GetTransform() const { return m_TransformationMatrix; };
	inline Vector3D GetPointInWorldSpace(const Vector3D point) { return m_TransformationMatrix.Transform(point); };
	inline Vector3D GetPosition() { return m_Position; };
	inline Vector3D GetRotation() { return m_Rotation; };
	inline Vector3D GetVelocity() { return m_Velocity; };
	inline Vector3D GetLastFrameAcceleration() { return m_LastFrameAcceleration; };
	inline void GetInverseInertiaTensorWorld(Matrix& inverseInertiaTensor) const { inverseInertiaTensor = m_InverseInertiaTensorWorld; };
	inline float GetInverseMass() { return m_InverseMass; };
	inline float GetMass() { return m_Mass; };
	inline bool GetAwake() { return m_IsAwake; };

	virtual RBCollisionSphere GetCollisionSphere() { return RBCollisionSphere(this, 1); };

	inline bool HasInfiniteMass() { return m_InverseMass == 1; }

	void CalculateDerivedData();

protected:
	static void calculateTransformMatrix(Matrix& transformMatrix, const Vector3D& position, const Quaternion& orientation);
	static void transformInertiaTensor(Matrix& iitWorld, const Matrix& iitBody, const Matrix& rotationMatrix);

	float m_Mass;
	float m_InverseMass;
	float m_LinearDampening;
	float m_AngularDampening;

	Vector3D m_Position;
	Vector3D m_InitialPosition;
	Vector3D m_Velocity;
	Vector3D m_InitialVelocity;
	Vector3D m_LastFrameAcceleration;
	Vector3D m_Acceleration;
	Vector3D m_InitialAcceleration;
	Vector3D m_Rotation;
	Vector3D m_InitialRotation;
	Vector3D m_ForceAccum;
	Vector3D m_TorqueAccum;

	Quaternion m_Orientation;

	Matrix m_TransformationMatrix;
	Matrix m_InverseInertiaTensor;
	Matrix m_InverseInertiaTensorWorld;

	bool m_IsAwake;

};
#endif 