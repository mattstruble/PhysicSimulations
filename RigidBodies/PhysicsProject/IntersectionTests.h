//======================================================================
//File: IntersectionTests.h
//Author: Matt Struble
//Resources: https://github.com/idmillington/cyclone-physics
//======================================================================
#ifndef INTERSECTION_TESTS_H
#define INTERSECTION_TESTS_H
//=============================================================================
#include "RBCollisionSphere.h"
#include "CollisionPlane.h"
#include "RBCollisionCube.h"
//=============================================================================
class IntersectionTests
{
private:
	static float transformToAxis(const RBCollisionCube& cube, const Vector3D& axis);
	static bool checkOverlapOnAxis(const RBCollisionCube& cubeOne, const RBCollisionCube& cubeTwo, const Vector3D& axis, const Vector3D& toCenter);
	static float penetrationOnAxis(const RBCollisionCube& cubeOne, const RBCollisionCube& cubeTwo, const Vector3D& axis, const Vector3D& toCenter);

public:
	IntersectionTests();
	~IntersectionTests();

	static bool CheckSphereAndHalfSpace(const RBCollisionSphere& sphere, const CollisionPlane& plane);
	static bool CheckSphereAndSphere(const RBCollisionSphere& sphereOne, const RBCollisionSphere& sphereTwo);
	static bool CheckCubeAndCube(const RBCollisionCube& cubeOne, const RBCollisionCube& cubeTwo);
	static bool CheckCubeAndHalfSpace(const RBCollisionCube& cube, const CollisionPlane& plane);

	static bool TryAxis(const RBCollisionCube& cubeOne, const RBCollisionCube& cubeTwo, Vector3D axis, const Vector3D& toCenter, unsigned int index, float& smallestPenetration, unsigned int& smallestCase);
};
#endif