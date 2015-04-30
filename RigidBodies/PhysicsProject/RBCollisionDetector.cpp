//======================================================================
//File: RBCollisionDetector.cpp
//Author: Matt Struble
//Resource: https://github.com/idmillington/cyclone-physics
//======================================================================
#include "RBCollisionDetector.h"
#include "RBContact.h"
#include "IntersectionTests.h"
//=============================================================================
float RBCollisionDetector::m_Mults[8][3] = { { 1, 1, 1 }, { -1, 1, 1 }, { 1, -1, 1 }, { -1, -1, 1 },
{ 1, 1, -1 }, { -1, 1, -1 }, { 1, -1, -1 }, { -1, -1, -1 } };
//=============================================================================
RBCollisionDetector::RBCollisionDetector()
{
}

//-----------------------------------------------------------------------------
RBCollisionDetector::~RBCollisionDetector()
{
}

//-----------------------------------------------------------------------------
void fillPointFaceCubeCube(const RBCollisionCube& cubeOne, const RBCollisionCube& cubeTwo, const Vector3D& toCenter, CollisionData* collisionData, unsigned int best, float penetration)
{
	RBContact* rigidContact = collisionData->GetRigidContacts()[0];

	Vector3D normal = cubeOne.GetAxis(best);
	if (Vector3D::Dot(normal, toCenter) > 0)
		normal *= -1.0f;

	Vector3D vertex = cubeTwo.GetHalfSize();
	if (Vector3D::Dot(cubeTwo.GetAxis(0), normal) < 0) vertex.X *= -1.0f;
	if (Vector3D::Dot(cubeTwo.GetAxis(1), normal) < 0) vertex.Y *= -1.0f;
	if (Vector3D::Dot(cubeTwo.GetAxis(2), normal) < 0) vertex.Z *= -1.0f;

	Vector3D contactPoint = cubeTwo.GetTransform() * vertex;
	rigidContact->Initialize(cubeOne.GetRigidBody(), cubeTwo.GetRigidBody(), contactPoint, normal, penetration, collisionData->GetRestitution(), collisionData->GetFriction());
}

//-----------------------------------------------------------------------------
Vector3D getContactPoint(const Vector3D& pointOne, const Vector3D& directionOne, float sizeOne, const Vector3D& pointTwo, const Vector3D directionTwo, float sizeTwo, bool useOne)
{
	Vector3D toSt, cOne, cTwo;
	float dpStaOne, dpStaTwo, dpOneTwo, smOne, smTwo;
	float denom, mua, mub;

	smOne = directionOne.MagnitudeSquared();
	smTwo = directionTwo.MagnitudeSquared();
	dpOneTwo = Vector3D::Dot(directionTwo, directionOne);

	toSt = pointOne - pointTwo;
	dpStaOne = Vector3D::Dot(directionOne, toSt);
	dpStaTwo = Vector3D::Dot(directionTwo, toSt);

	denom = smOne * smTwo - dpOneTwo, dpOneTwo;

	if (abs(denom) < 0.0001f)
		return useOne ? pointOne : pointTwo;

	mua = (dpOneTwo * dpStaTwo - smTwo * dpStaOne) / denom;
	mub = (smOne * dpStaTwo - dpOneTwo * dpStaOne) / denom;

	if (mua > sizeOne || mua < -sizeOne || mub > sizeTwo || mub < -sizeTwo)
	{
		return useOne ? pointOne : pointTwo;
	}
	else
	{
		cOne = pointOne + directionOne * mua;
		cTwo = pointTwo + directionTwo * mub;

		return cOne * 0.5f + cTwo * 0.5f;
	}
}

//-----------------------------------------------------------------------------
unsigned int RBCollisionDetector::SphereAndSphere(const RBCollisionSphere& sphereOne, const RBCollisionSphere& sphereTwo, CollisionHandler* collisionHandler)
{
	Vector3D positionOne = sphereOne.GetAxis(3);
	Vector3D positionTwo = sphereTwo.GetAxis(3);

	Vector3D midLine = positionOne - positionTwo;
	float size = midLine.Magnitude();

	if (size <= 0.0f || size >= sphereOne.GetRadius() + sphereTwo.GetRadius())
	{
		return 0;
	}

	Vector3D normal = midLine * 1.0f / size;

	RBContact rigidContact = RBContact();
	Vector3D contactPoint = positionOne + midLine * 0.5f;
	float penetration = sphereOne.GetRadius() + sphereTwo.GetRadius() - size;
	rigidContact.Initialize(sphereOne.GetRigidBody(), sphereTwo.GetRigidBody(), contactPoint, normal, penetration, collisionHandler->GetRestitution(), collisionHandler->GetFriction());
	collisionHandler->AddContact(rigidContact);
	return 1;
}

//-----------------------------------------------------------------------------
unsigned int RBCollisionDetector::SphereAndHalfSpace(const RBCollisionSphere& sphere, const CollisionPlane& plane, CollisionHandler* collisionHandler)
{
	Vector3D position = sphere.GetAxis(3);

	float sphereDistance = Vector3D::Dot(plane.GetDirection(), position) - sphere.GetRadius() - plane.GetOffset();

	if (sphereDistance >= 0)
	{
		return 0;
	}

	RBContact rigidContact = RBContact();
	Vector3D contactPoint = position - plane.GetDirection() * (sphereDistance + sphere.GetRadius());

	rigidContact.Initialize(sphere.GetRigidBody(), nullptr, contactPoint, plane.GetDirection(), -sphereDistance, collisionHandler->GetRestitution(), collisionHandler->GetFriction());
	collisionHandler->AddContact(rigidContact);
	return 1;
}

//-----------------------------------------------------------------------------
unsigned int RBCollisionDetector::SphereAndTruePlane(const RBCollisionSphere& sphere, const CollisionPlane& plane, CollisionHandler* collisionHandler)
{
	Vector3D position = sphere.GetAxis(3);

	float centerDistance = Vector3D::Dot(plane.GetDirection(), position) - plane.GetOffset();

	if (centerDistance * centerDistance >= sphere.GetRadius() * sphere.GetRadius())
	{
		return 0;
	}

	Vector3D normal = plane.GetDirection();
	float penetration = -centerDistance;

	if (centerDistance < 0)
	{
		normal *= -1;
		penetration = -penetration;
	}
	penetration += sphere.GetRadius();

	RBContact rigidContact = RBContact();
	Vector3D contactPoint = position - plane.GetDirection() * centerDistance;
	rigidContact.Initialize(sphere.GetRigidBody(), nullptr, contactPoint, normal, penetration, collisionHandler->GetRestitution(), collisionHandler->GetFriction());
	collisionHandler->AddContact(rigidContact);
	return 1;
}

//-----------------------------------------------------------------------------
unsigned int RBCollisionDetector::CubeAndHalfSpace(const RBCollisionCube& cube, const CollisionPlane& plane, CollisionHandler* collisionHandler)
{
	if (!IntersectionTests::CheckCubeAndHalfSpace(cube, plane))
	{
		return 0;
	}

	int contactsUsed = 0;
	for (unsigned int i = 0; i < 8; i++)
	{
		Vector3D vertexPos(m_Mults[i][0], m_Mults[i][1], m_Mults[i][2]);
		vertexPos = vertexPos * cube.GetHalfSize();
		vertexPos = cube.GetTransform().Transform(vertexPos);

		float vertexDistance = Vector3D::Dot(vertexPos, plane.GetDirection());

		if (vertexDistance <= plane.GetOffset())
		{
			Vector3D contactPoint = plane.GetDirection();
			contactPoint *= vertexDistance - plane.GetOffset();
			contactPoint += vertexPos;
			Vector3D contactNormal = plane.GetDirection();
			float penetration = plane.GetOffset() - vertexDistance;
			RBContact rigidContact = RBContact();
			rigidContact.Initialize(cube.GetRigidBody(), NULL, contactPoint, contactNormal, penetration, collisionHandler->GetRestitution(), collisionHandler->GetFriction());
			collisionHandler->AddContact(rigidContact);
			contactsUsed++;
		}
	}
	return contactsUsed;
}

//-----------------------------------------------------------------------------
unsigned int CubeAndSphere(const RBCollisionCube& cube, const RBCollisionSphere& sphere, CollisionData* collisionData)
{
	Vector3D center = sphere.GetAxis(3);
	Vector3D relativeCenter = cube.GetTransform().TransformInverse(center);

	bool xEval = abs(relativeCenter.X) - sphere.GetRadius() > cube.GetHalfSize().X;
	bool yEval = abs(relativeCenter.Y) - sphere.GetRadius() > cube.GetHalfSize().Y;
	bool zEval = abs(relativeCenter.Z) - sphere.GetRadius() > cube.GetHalfSize().Z;

	if (xEval || yEval || zEval)
	{
		return 0;
	}

	Vector3D closestPoint = Vector3D::Zero;

	float xDistance = relativeCenter.X;
	if (xDistance > cube.GetHalfSize().X)
		xDistance = cube.GetHalfSize().X;
	if (xDistance < -cube.GetHalfSize().X)
		xDistance = -cube.GetHalfSize().X;
	closestPoint.X = xDistance;

	float yDistance = relativeCenter.Y;
	if (yDistance > cube.GetHalfSize().Y)
		yDistance = cube.GetHalfSize().Y;
	if (yDistance < -cube.GetHalfSize().Y)
		yDistance = -cube.GetHalfSize().Y;
	closestPoint.Y = yDistance;

	float zDistance = relativeCenter.Z;
	if (zDistance > cube.GetHalfSize().Z)
		zDistance = cube.GetHalfSize().Z;
	if (zDistance < -cube.GetHalfSize().Z)
		zDistance = -cube.GetHalfSize().Z;
	closestPoint.Z = zDistance;

	float distance = (closestPoint - relativeCenter).MagnitudeSquared();
	if (distance > sphere.GetRadius() * sphere.GetRadius())
		return 0;

	Vector3D closestWorldPoint = cube.GetTransform().Transform(closestPoint);

	RBContact* rigidContact = collisionData->GetRigidContacts()[0];
	Vector3D contactNormal = (closestWorldPoint - center);
	contactNormal.Normalize();
	Vector3D contactPoint = closestWorldPoint;
	float penetration = sphere.GetRadius() - sqrt(distance);
	rigidContact->Initialize(cube.GetRigidBody(), sphere.GetRigidBody(), contactPoint, contactNormal, penetration, collisionData->GetRestitution(), collisionData->GetFriction());

	collisionData->AddContacts(1);
	return 1;
}

//-----------------------------------------------------------------------------
unsigned int CubeAndCube(const RBCollisionCube& cubeOne, const RBCollisionCube& cubeTwo, CollisionData* collisionData)
{
	Vector3D toCenter = cubeTwo.GetAxis(3) - cubeOne.GetAxis(3);

	float penetration = FLT_MAX;
	unsigned int best = 0xffffff;

	if (!IntersectionTests::TryAxis(cubeOne, cubeTwo, cubeOne.GetAxis(0), toCenter, 0, penetration, best)) return 0;
	if (!IntersectionTests::TryAxis(cubeOne, cubeTwo, cubeOne.GetAxis(1), toCenter, 1, penetration, best)) return 0;
	if (!IntersectionTests::TryAxis(cubeOne, cubeTwo, cubeOne.GetAxis(2), toCenter, 2, penetration, best)) return 0;

	if (!IntersectionTests::TryAxis(cubeOne, cubeTwo, cubeTwo.GetAxis(0), toCenter, 3, penetration, best)) return 0;
	if (!IntersectionTests::TryAxis(cubeOne, cubeTwo, cubeTwo.GetAxis(1), toCenter, 4, penetration, best)) return 0;
	if (!IntersectionTests::TryAxis(cubeOne, cubeTwo, cubeTwo.GetAxis(2), toCenter, 5, penetration, best)) return 0;

	unsigned int bestSingleAxis = best;

	if (!IntersectionTests::TryAxis(cubeOne, cubeTwo, Vector3D::Cross(cubeOne.GetAxis(0), cubeTwo.GetAxis(0)), toCenter, 6, penetration, best)) return 0;
	if (!IntersectionTests::TryAxis(cubeOne, cubeTwo, Vector3D::Cross(cubeOne.GetAxis(0), cubeTwo.GetAxis(1)), toCenter, 7, penetration, best)) return 0;
	if (!IntersectionTests::TryAxis(cubeOne, cubeTwo, Vector3D::Cross(cubeOne.GetAxis(0), cubeTwo.GetAxis(2)), toCenter, 8, penetration, best)) return 0;
	if (!IntersectionTests::TryAxis(cubeOne, cubeTwo, Vector3D::Cross(cubeOne.GetAxis(1), cubeTwo.GetAxis(0)), toCenter, 9, penetration, best)) return 0;
	if (!IntersectionTests::TryAxis(cubeOne, cubeTwo, Vector3D::Cross(cubeOne.GetAxis(1), cubeTwo.GetAxis(1)), toCenter, 10, penetration, best)) return 0;
	if (!IntersectionTests::TryAxis(cubeOne, cubeTwo, Vector3D::Cross(cubeOne.GetAxis(1), cubeTwo.GetAxis(2)), toCenter, 11, penetration, best)) return 0;
	if (!IntersectionTests::TryAxis(cubeOne, cubeTwo, Vector3D::Cross(cubeOne.GetAxis(2), cubeTwo.GetAxis(0)), toCenter, 12, penetration, best)) return 0;
	if (!IntersectionTests::TryAxis(cubeOne, cubeTwo, Vector3D::Cross(cubeOne.GetAxis(2), cubeTwo.GetAxis(1)), toCenter, 13, penetration, best)) return 0;
	if (!IntersectionTests::TryAxis(cubeOne, cubeTwo, Vector3D::Cross(cubeOne.GetAxis(2), cubeTwo.GetAxis(2)), toCenter, 14, penetration, best)) return 0;

	if (best == 0xffffff)
		return 0;

	if (best < 3)
	{
		fillPointFaceCubeCube(cubeOne, cubeTwo, toCenter, collisionData, best, penetration);
		collisionData->AddContacts(1);
		return 1;
	}
	else if (best < 6)
	{
		fillPointFaceCubeCube(cubeTwo, cubeOne, toCenter * -1.0f, collisionData, best - 3, penetration);
		collisionData->AddContacts(1);
		return 1;
	}
	else
	{
		best -= 6;
		unsigned int axisOneIndex = best / 3;
		unsigned int axisTwoIndex = best % 3;
		Vector3D axisOne = cubeOne.GetAxis(axisOneIndex);
		Vector3D axisTwo = cubeTwo.GetAxis(axisTwoIndex);
		Vector3D axis = Vector3D::Cross(axisOne, axisTwo);
		axis.Normalize();

		if (Vector3D::Dot(axis, toCenter) > 0)
			axis *= 1.0f;

		Vector3D pointOnEdgeOne = cubeOne.GetHalfSize();
		Vector3D pointOnEdgeTwo = cubeTwo.GetHalfSize();
		for (unsigned i = 0; i < 3; i++)
		{
			if (i == axisOneIndex)
				pointOnEdgeOne.SetIndex(i, 0);
			else if (Vector3D::Dot(cubeOne.GetAxis(i), axis) > 0)
				pointOnEdgeOne.SetIndex(i, pointOnEdgeOne.GetIndex(i) * -1.0f);
			if (i == axisTwoIndex)
				pointOnEdgeTwo.SetIndex(i, 0);
			else if (Vector3D::Dot(cubeTwo.GetAxis(i), axis) < 0)
				pointOnEdgeTwo.SetIndex(i, pointOnEdgeOne.GetIndex(i) * -1.0f);
		}

		pointOnEdgeOne = cubeOne.GetTransform() * pointOnEdgeOne;
		pointOnEdgeTwo = cubeTwo.GetTransform() * pointOnEdgeTwo;

		Vector3D vertex = getContactPoint(pointOnEdgeOne, axisOne, cubeOne.GetHalfSize().GetIndex(axisOneIndex),
			pointOnEdgeTwo, axisTwo, cubeTwo.GetHalfSize().GetIndex(axisTwoIndex), bestSingleAxis > 2);

		RBContact* rigidContact = collisionData->GetRigidContacts()[0];
		rigidContact->Initialize(cubeOne.GetRigidBody(), cubeTwo.GetRigidBody(), vertex, axis, penetration, collisionData->GetRestitution(), collisionData->GetFriction());
		collisionData->AddContacts(1);
		return 1;
	}

	return 0;
}

//-----------------------------------------------------------------------------
void RBCollisionDetector::CheckCollision(RigidBody* rigidBodyOne, RigidBody* rigidBodyTwo, CollisionHandler* collisionHandler)
{
	if (rigidBodyOne->GetCollisionType() == e_CollisionType::SPHERE)
	{
		switch (rigidBodyTwo->GetCollisionType())
		{
		case e_CollisionType::SPHERE:
			SphereAndSphere(rigidBodyOne->GetCollisionSphere(), rigidBodyTwo->GetCollisionSphere(), collisionHandler);
			break;
		case e_CollisionType::CUBE:
			//CubeAndSphere(rigidBodyTwo->GetCollisionCube(), rigidBodyOne->GetCollisionSphere(), collisionHandler);
			break;
		}
	}
	else if (rigidBodyOne->GetCollisionType() == e_CollisionType::CUBE)
	{
		switch (rigidBodyTwo->GetCollisionType())
		{
		case e_CollisionType::SPHERE:
			//CubeAndSphere(rigidBodyOne->GetCollisionCube(), rigidBodyTwo->GetCollisionSphere(), collisionHandler);
			break;
		case e_CollisionType::CUBE:
			//CubeAndCube(rigidBodyOne->GetCollisionCube(), rigidBodyTwo->GetCollisionCube(), collisionHandler);
			break;
		}
	}
}