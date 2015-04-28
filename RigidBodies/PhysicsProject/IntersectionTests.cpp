//======================================================================
//File: IntersectionTests.cpp
//Author: Matt Struble
//Resources: https://github.com/idmillington/cyclone-physics
//======================================================================
#include "IntersectionTests.h"
#include <math.h>
//=============================================================================
IntersectionTests::IntersectionTests()
{
}

//-----------------------------------------------------------------------------
IntersectionTests::~IntersectionTests()
{
}

//-----------------------------------------------------------------------------
float IntersectionTests::transformToAxis(const RBCollisionCube& cube, const Vector3D& axis)
{
	float xEval = cube.GetHalfSize().X * abs(Vector3D::Dot(axis, cube.GetAxis(0)));
	float yEval = cube.GetHalfSize().Y * abs(Vector3D::Dot(axis, cube.GetAxis(1)));
	float zEval = cube.GetHalfSize().Z * abs(Vector3D::Dot(axis, cube.GetAxis(2)));

	return xEval + yEval + zEval;
}

//-----------------------------------------------------------------------------
bool IntersectionTests::checkOverlapOnAxis(const RBCollisionCube& cubeOne, const RBCollisionCube& cubeTwo, const Vector3D& axis, const Vector3D& toCenter)
{
	float projectOne = transformToAxis(cubeOne, axis);
	float projectTwo = transformToAxis(cubeTwo, axis);

	float distance = abs(Vector3D::Dot(toCenter, axis));

	return distance < (projectOne + projectTwo);
}

//-----------------------------------------------------------------------------
float IntersectionTests::penetrationOnAxis(const RBCollisionCube& cubeOne, const RBCollisionCube& cubeTwo, const Vector3D& axis, const Vector3D& toCenter)
{
	float projectOne = transformToAxis(cubeOne, axis);
	float projectTwo = transformToAxis(cubeTwo, axis);

	float distance = abs(Vector3D::Dot(toCenter, axis));

	return projectOne + projectTwo - distance;
}

//-----------------------------------------------------------------------------
bool IntersectionTests::CheckSphereAndHalfSpace(const RBCollisionSphere& sphere, const CollisionPlane& plane)
{
	float sphereDistance = Vector3D::Dot(plane.GetDirection(), sphere.GetAxis(3)) - sphere.GetRadius();

	return sphereDistance <= plane.GetOffset();
}

//-----------------------------------------------------------------------------
bool IntersectionTests::CheckSphereAndSphere(const RBCollisionSphere& sphereOne, const RBCollisionSphere& sphereTwo)
{
	Vector3D midLine = sphereOne.GetAxis(3) - sphereTwo.GetAxis(3);
	float radiiSum = sphereOne.GetRadius() + sphereTwo.GetRadius();

	return midLine.MagnitudeSquared() < (radiiSum * radiiSum);
}

//-----------------------------------------------------------------------------
bool IntersectionTests::CheckCubeAndCube(const RBCollisionCube& cubeOne, const RBCollisionCube& cubeTwo)
{
	Vector3D toCenter = cubeTwo.GetAxis(3) - cubeOne.GetAxis(3);

	return
	{
		checkOverlapOnAxis(cubeOne, cubeTwo, cubeOne.GetAxis(0), toCenter) &&
		checkOverlapOnAxis(cubeOne, cubeTwo, cubeOne.GetAxis(1), toCenter) &&
		checkOverlapOnAxis(cubeOne, cubeTwo, cubeOne.GetAxis(2), toCenter) &&

		checkOverlapOnAxis(cubeOne, cubeTwo, cubeTwo.GetAxis(0), toCenter) &&
		checkOverlapOnAxis(cubeOne, cubeTwo, cubeTwo.GetAxis(1), toCenter) &&
		checkOverlapOnAxis(cubeOne, cubeTwo, cubeTwo.GetAxis(2), toCenter) &&

		checkOverlapOnAxis(cubeOne, cubeTwo, Vector3D::Cross(cubeOne.GetAxis(0), cubeTwo.GetAxis(0)), toCenter) &&
		checkOverlapOnAxis(cubeOne, cubeTwo, Vector3D::Cross(cubeOne.GetAxis(0), cubeTwo.GetAxis(1)), toCenter) &&
		checkOverlapOnAxis(cubeOne, cubeTwo, Vector3D::Cross(cubeOne.GetAxis(0), cubeTwo.GetAxis(2)), toCenter) &&
		checkOverlapOnAxis(cubeOne, cubeTwo, Vector3D::Cross(cubeOne.GetAxis(1), cubeTwo.GetAxis(0)), toCenter) &&
		checkOverlapOnAxis(cubeOne, cubeTwo, Vector3D::Cross(cubeOne.GetAxis(1), cubeTwo.GetAxis(1)), toCenter) &&
		checkOverlapOnAxis(cubeOne, cubeTwo, Vector3D::Cross(cubeOne.GetAxis(1), cubeTwo.GetAxis(2)), toCenter) &&
		checkOverlapOnAxis(cubeOne, cubeTwo, Vector3D::Cross(cubeOne.GetAxis(2), cubeTwo.GetAxis(0)), toCenter) &&
		checkOverlapOnAxis(cubeOne, cubeTwo, Vector3D::Cross(cubeOne.GetAxis(2), cubeTwo.GetAxis(1)), toCenter) &&
		checkOverlapOnAxis(cubeOne, cubeTwo, Vector3D::Cross(cubeOne.GetAxis(2), cubeTwo.GetAxis(2)), toCenter)
	};
}

//-----------------------------------------------------------------------------
bool IntersectionTests::CheckCubeAndHalfSpace(const RBCollisionCube& cube, const CollisionPlane& plane)
{
	float projectedRadius = transformToAxis(cube, plane.GetDirection());

	float cubeDistance = Vector3D::Dot(plane.GetDirection(), cube.GetAxis(3)) - projectedRadius;

	return cubeDistance <= plane.GetOffset();
}

//-----------------------------------------------------------------------------
bool IntersectionTests::TryAxis(const RBCollisionCube& cubeOne, const RBCollisionCube& cubeTwo, Vector3D axis, const Vector3D& toCenter, unsigned int index, float& smallestPenetration, unsigned int& smallestCase)
{
	if (axis.MagnitudeSquared() < 0.0001)
		return true;
	axis.Normalize();

	float penetration = penetrationOnAxis(cubeOne, cubeTwo, axis, toCenter);

	if (penetration < 0)
		return false;

	if (penetration < smallestPenetration)
	{
		smallestPenetration = penetration;
		smallestCase = index;
	}

	return true;
}