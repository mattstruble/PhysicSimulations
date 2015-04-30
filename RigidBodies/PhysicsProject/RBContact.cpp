//File: RBContact.cpp
//Author: Matt Struble
//Resource: https://github.com/idmillington/cyclone-physics
//======================================================================
#include "RBContact.h"
#include <math.h>
//=============================================================================
RBContact::RBContact()
{
}

//-----------------------------------------------------------------------------
RBContact::~RBContact()
{
}

//-----------------------------------------------------------------------------
void RBContact::calculateContactBasis()
{
	Vector3D contactTangentX;
	Vector3D contactTangentY;
	float scale;

	if (abs(m_ContactNormal.X) > abs(m_ContactNormal.Y))
	{
		scale = 1.0f / sqrtf(m_ContactNormal.Z * m_ContactNormal.Z + m_ContactNormal.X * m_ContactNormal.X);

		contactTangentX.X = m_ContactNormal.Z * scale;
		contactTangentX.Y = 0;
		contactTangentX.Z = -m_ContactNormal.X * scale;

		contactTangentY.X = m_ContactNormal.Y * contactTangentX.X;
		contactTangentY.Y = m_ContactNormal.Z * contactTangentX.X - m_ContactNormal.X * contactTangentX.Z;
		contactTangentY.Z = -m_ContactNormal.Y * contactTangentX.X;
	}
	else
	{
		scale = 1.0f / sqrtf(m_ContactNormal.Z * m_ContactNormal.Z + m_ContactNormal.Y * m_ContactNormal.Y);

		contactTangentX.X = 0;
		contactTangentX.Y = -m_ContactNormal.Z * scale;
		contactTangentX.Z = m_ContactNormal.Y * scale;

		contactTangentY.X = m_ContactNormal.Y * contactTangentX.Z - m_ContactNormal.Z * contactTangentX.Y;
		contactTangentY.Y = -m_ContactNormal.X * contactTangentX.Z;
		contactTangentY.Z = m_ContactNormal.X * contactTangentX.Y;
	}

	m_ContactToWorld = Matrix(3, 3);
	m_ContactToWorld.Set(0, m_ContactNormal.X);
	m_ContactToWorld.Set(1, contactTangentX.X);
	m_ContactToWorld.Set(2, contactTangentY.X);
	m_ContactToWorld.Set(3, m_ContactNormal.Y);
	m_ContactToWorld.Set(4, contactTangentX.Y);
	m_ContactToWorld.Set(5, contactTangentY.Y);
	m_ContactToWorld.Set(6, m_ContactNormal.Z);
	m_ContactToWorld.Set(7, contactTangentX.Z);
	m_ContactToWorld.Set(8, contactTangentY.Z);
}

//-----------------------------------------------------------------------------
Vector3D RBContact::calculateLocalVelocity(unsigned int rigidBodyIndex, float deltaTime)
{
	RigidBody* rigidBody;
	Vector3D relativePosition;
	if (rigidBodyIndex == 0)
	{
		rigidBody = mp_RigidBodyOne;
		relativePosition = m_RelativeContactPositionOne;
	}
	else
	{
		rigidBody = mp_RigidBodyTwo;
		relativePosition = m_RelativeContactPositionTwo;
	}

	Vector3D velocity = Vector3D::Cross(rigidBody->GetRotation(), relativePosition);
	velocity += rigidBody->GetVelocity();

	Vector3D contactVelocity = m_ContactToWorld.TransformTranspose(velocity);
	Vector3D accVelocity = rigidBody->GetLastFrameAcceleration() * deltaTime;
	accVelocity = m_ContactToWorld.TransformTranspose(accVelocity);
	accVelocity.X = 0;

	m_ContactVelocity += accVelocity;

	return contactVelocity;
}

//-----------------------------------------------------------------------------
void RBContact::CalculateDesiredDeltavelocity(float deltaTime)
{
	const float velocityLimit = 0.25f;
	float velocityFromAcc = 0;

	if (mp_RigidBodyOne->GetAwake())
	{
		velocityFromAcc += Vector3D::Dot(mp_RigidBodyOne->GetLastFrameAcceleration(), m_ContactNormal) * deltaTime;
	}

	if (mp_RigidBodyTwo && mp_RigidBodyTwo->GetAwake())
	{
		velocityFromAcc -= Vector3D::Dot(mp_RigidBodyTwo->GetLastFrameAcceleration(), m_ContactNormal) * deltaTime;
	}

	float thisRestitution = m_Restitution;
	if (abs(m_ContactVelocity.X) < velocityLimit)
		thisRestitution = 0.0f;

	m_DesiredDeltaVelocity = -m_ContactVelocity.X - thisRestitution * (m_ContactVelocity.X - velocityFromAcc);
}

//-----------------------------------------------------------------------------
Vector3D RBContact::calculateImpulse(Matrix* inverseInertiaTensor)
{
	Vector3D impulseContact;

	Vector3D deltaVelWorld = Vector3D::Cross(m_RelativeContactPositionOne, m_ContactNormal);
	deltaVelWorld = inverseInertiaTensor[0].Transform(deltaVelWorld);
	deltaVelWorld = Vector3D::Cross(deltaVelWorld, m_RelativeContactPositionOne);

	float deltaVelocity = Vector3D::Dot(deltaVelWorld, m_ContactNormal);
	deltaVelocity += mp_RigidBodyOne->GetInverseMass();

	if (mp_RigidBodyTwo)
	{
		Vector3D deltaVelWorld = Vector3D::Cross(m_RelativeContactPositionTwo, m_ContactNormal);
		deltaVelWorld = inverseInertiaTensor[1].Transform(deltaVelWorld);
		deltaVelWorld = Vector3D::Cross(deltaVelWorld, m_RelativeContactPositionTwo);

		deltaVelocity += Vector3D::Dot(deltaVelWorld, m_ContactNormal);
		deltaVelocity += mp_RigidBodyTwo->GetInverseMass();
	}

	impulseContact.X = m_DesiredDeltaVelocity / deltaVelocity;
	impulseContact.Y = 0;
	impulseContact.Z = 0;

	return impulseContact;
}

//-----------------------------------------------------------------------------
Vector3D RBContact::calculateFrictionImpulse(Matrix* inverseInertiaTensor)
{
	Vector3D impulseContact;
	float inverseMass = mp_RigidBodyOne->GetInverseMass();

	Matrix impulseToTorque = Matrix(3, 3);
	impulseToTorque.SkewSymmetric(m_RelativeContactPositionOne);

	Matrix deltaVelWorld = impulseToTorque;
	deltaVelWorld = deltaVelWorld * inverseInertiaTensor[0];
	deltaVelWorld = deltaVelWorld * impulseToTorque;
	deltaVelWorld = deltaVelWorld * -1;

	if (mp_RigidBodyTwo)
	{
		impulseToTorque.SkewSymmetric(m_RelativeContactPositionTwo);

		Matrix deltaVelWorld2 = impulseToTorque;
		deltaVelWorld2 = deltaVelWorld2 * inverseInertiaTensor[1];
		deltaVelWorld2 = deltaVelWorld2 * impulseToTorque;
		deltaVelWorld2 = deltaVelWorld2 * -1;

		deltaVelWorld = deltaVelWorld + deltaVelWorld2;

		inverseMass += mp_RigidBodyTwo->GetInverseMass();
	}

	Matrix deltaVelocity = m_ContactToWorld.Transpose();
	deltaVelocity = deltaVelocity * deltaVelWorld;
	deltaVelocity = deltaVelocity * m_ContactToWorld;

	deltaVelocity.Set(0, deltaVelocity.Get(0) + inverseMass);
	deltaVelocity.Set(4, deltaVelocity.Get(4) + inverseMass);
	deltaVelocity.Set(8, deltaVelocity.Get(8) + inverseMass);

	Matrix impulseMatrix = deltaVelocity.Inverse();

	Vector3D velKill(m_DesiredDeltaVelocity, -m_ContactVelocity.Y, -m_ContactVelocity.Z);

	impulseContact = impulseMatrix.Transform(velKill);

	float planarImpulse = sqrt(impulseContact.Y * impulseContact.Y + impulseContact.Z * impulseContact.Z);

	if (planarImpulse > impulseContact.X * m_Friction)
	{
		impulseContact.Y /= planarImpulse;
		impulseContact.Z /= planarImpulse;

		impulseContact.X = deltaVelocity.Get(0) + deltaVelocity.Get(1) * m_Friction * impulseContact.Y +
			deltaVelocity.Get(2) * m_Friction * impulseContact.Z;
		impulseContact.X = m_DesiredDeltaVelocity / impulseContact.X;
		impulseContact.Y *= m_Friction * impulseContact.X;
		impulseContact.Z *= m_Friction * impulseContact.X;
	}

	return impulseContact;
}

//-----------------------------------------------------------------------------
void RBContact::Initialize(RigidBody* rigidBodyOne, RigidBody* rigidBodyTwo, Vector3D contactPoint, Vector3D contactNormal, float penetration, float restitution, float friction)
{
	mp_RigidBodyOne = rigidBodyOne;
	mp_RigidBodyTwo = rigidBodyTwo;

	m_ContactPoint = contactPoint;
	m_ContactNormal = contactNormal;

	m_Penetration = penetration;
	m_Restitution = restitution;
	m_Friction = friction;
}

//-----------------------------------------------------------------------------
void RBContact::CalculateInternals(float deltaTime)
{
	calculateContactBasis();

	m_RelativeContactPositionOne = m_ContactPoint - mp_RigidBodyOne->GetPosition();

	if (mp_RigidBodyTwo)
		m_RelativeContactPositionTwo = m_ContactPoint - mp_RigidBodyTwo->GetPosition();

	m_ContactVelocity = calculateLocalVelocity(0, deltaTime);
	if (mp_RigidBodyTwo)
		m_ContactVelocity -= calculateLocalVelocity(1, deltaTime);

	CalculateDesiredDeltavelocity(deltaTime);
}

//-----------------------------------------------------------------------------
void RBContact::MatchAwakeState()
{
	if (!mp_RigidBodyTwo)
		return;

	bool bodyOneAwake = mp_RigidBodyOne->GetAwake();
	bool bodyTwoAwake = mp_RigidBodyTwo->GetAwake();

	if (!bodyOneAwake && bodyTwoAwake)
	{
		mp_RigidBodyOne->SetAwake();
	}
	else if (bodyOneAwake && !bodyTwoAwake)
	{
		mp_RigidBodyTwo->SetAwake();
	}
}

//-----------------------------------------------------------------------------
void RBContact::ApplyPositionChange(Vector3D linearChange[2], Vector3D angularChange[2], float penetration, float dt)
{
	const float angularLimit = 0.2f;
	float angularMove[2];
	float linearMove[2];

	float totalInertia = 0;
	float linearInertia[2];
	float angularInertia[2];

	for (unsigned int i = 0; i < 2; i++)
	{
		if (i == 0 && mp_RigidBodyOne || i == 1 && mp_RigidBodyTwo)
		{
			RigidBody* rigidBody;
			Vector3D relativeContactPosition;
			if (i == 0)
			{
				rigidBody = mp_RigidBodyOne;
				relativeContactPosition = m_RelativeContactPositionOne;
			}
			else
			{
				rigidBody = mp_RigidBodyTwo;
				relativeContactPosition = m_RelativeContactPositionTwo;
			}

			Matrix inverseInertiaTensor = Matrix(3, 3);
			rigidBody->GetInverseInertiaTensorWorld(inverseInertiaTensor);

			Vector3D angularInertiaWorld = Vector3D::Cross(relativeContactPosition, m_ContactNormal);
			angularInertiaWorld = inverseInertiaTensor.Transform(angularInertiaWorld);
			angularInertiaWorld = Vector3D::Cross(angularInertiaWorld, relativeContactPosition);
			angularInertia[i] = Vector3D::Dot(angularInertiaWorld, m_ContactNormal);

			linearInertia[i] = rigidBody->GetInverseMass();

			totalInertia += linearInertia[i] + angularInertia[i];
		}
	}

	for (unsigned int i = 0; i < 2; i++)
	{
		if (i == 0 && mp_RigidBodyOne || i == 1 && mp_RigidBodyTwo)
		{
			RigidBody* rigidBody;
			Vector3D relativeContactPosition;
			if (i == 0)
			{
				rigidBody = mp_RigidBodyOne;
				relativeContactPosition = m_RelativeContactPositionOne;
			}
			else
			{
				rigidBody = mp_RigidBodyTwo;
				relativeContactPosition = m_RelativeContactPositionTwo;
			}

			int sign = (i == 0) ? 1 : -1;
			angularMove[i] = sign * m_Penetration * (angularInertia[i] / totalInertia);
			linearMove[i] = sign * penetration * (linearInertia[i] / totalInertia);

			Vector3D projection = relativeContactPosition;
			projection += m_ContactNormal * ((relativeContactPosition * -1) * m_ContactNormal);

			float maxMagnitude = angularLimit * projection.Magnitude();

			if (angularMove[i] < -maxMagnitude)
			{
				float totalMove = angularMove[i] + linearMove[i];
				angularMove[i] = -maxMagnitude;
				linearMove[i] = totalMove - angularMove[i];
			}
			else if (angularMove[i] > maxMagnitude)
			{
				float totalMove = angularMove[i] + linearMove[i];
				angularMove[i] = maxMagnitude;
				linearMove[i] = totalMove - angularMove[i];
			}

			if (angularMove[i] == 0)
			{
				angularChange[i] = Vector3D::Zero;
			}
			else
			{
				Vector3D targetAngularDirection = relativeContactPosition * m_ContactNormal;

				Matrix inverseInertiaTensor = Matrix(3, 3);
				rigidBody->GetInverseInertiaTensorWorld(inverseInertiaTensor);

				angularChange[i] = inverseInertiaTensor.Transform(targetAngularDirection) * (angularMove[i] / angularInertia[i]);
			}

			linearChange[i] = m_ContactNormal * linearMove[i];

			Vector3D position = rigidBody->GetPosition();
			position += m_ContactNormal * linearMove[i];
			rigidBody->SetPosition(position);

			Quaternion q;
			q = rigidBody->GetOrientation();
			q.VectorScaling(angularChange[i], 1.0f);
			rigidBody->SetOrientation(q);

			if (!rigidBody->GetAwake())
				rigidBody->CalculateDerivedData();
		}
	}
}

//-----------------------------------------------------------------------------
void RBContact::ApplyVelocityChange(Vector3D velocityChange[2], Vector3D rotationChange[2], float dt)
{
	Matrix inverseInertiaTensor[2];
	mp_RigidBodyOne->GetInverseInertiaTensorWorld(inverseInertiaTensor[0]);
	if (mp_RigidBodyTwo)
		mp_RigidBodyTwo->GetInverseInertiaTensorWorld(inverseInertiaTensor[1]);

	Vector3D impulseContact;

	if (m_Friction == 0.0f)
	{
		impulseContact = calculateImpulse(inverseInertiaTensor);
	}
	else
	{
		impulseContact = calculateFrictionImpulse(inverseInertiaTensor);
	}

	Vector3D impulse = m_ContactToWorld.Transform(impulseContact);

	Vector3D impulsiveTorque = Vector3D::Cross(m_RelativeContactPositionOne, impulse);
	rotationChange[0] = inverseInertiaTensor[0].Transform(impulsiveTorque);
	velocityChange[0] = Vector3D::Zero;
	velocityChange[0] += impulse * mp_RigidBodyOne->GetInverseMass();

	mp_RigidBodyOne->AddVelocity(velocityChange[0]);
	mp_RigidBodyOne->AddRotation(rotationChange[0]);

	if (mp_RigidBodyTwo)
	{
		Vector3D impulsiveTorque = Vector3D::Cross(impulse, m_RelativeContactPositionTwo);
		rotationChange[1] = inverseInertiaTensor[1].Transform(impulsiveTorque);
		velocityChange[1] = Vector3D::Zero;
		velocityChange[1] += impulse * mp_RigidBodyTwo->GetInverseMass();

		mp_RigidBodyTwo->AddVelocity(velocityChange[1]);
		mp_RigidBodyTwo->AddRotation(rotationChange[1]);
	}
}

//-----------------------------------------------------------------------------
RigidBody* RBContact::GetRigidBody(int index)
{
	if (index == 0)
	{
		return mp_RigidBodyOne;
	}
	else
	{
		return mp_RigidBodyTwo;
	}
}

//-----------------------------------------------------------------------------
Vector3D RBContact::GetRelativeContactPosition(int index)
{
	if (index == 0)
	{
		return m_RelativeContactPositionOne;
	}
	else
	{
		return m_RelativeContactPositionTwo;
	}
}