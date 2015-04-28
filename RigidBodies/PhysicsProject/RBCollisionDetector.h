//======================================================================
//File: RBCollisionDetector.h
//Author: Matt Struble
//Resource: https://github.com/idmillington/cyclone-physics
//======================================================================
#ifndef RB_COLLISION_DETECTOR_H
#define RB_COLLISION_DETECTOR_H
//=============================================================================
#include "RBCollisionData.h"
#include "RBCollisionSphere.h"
#include "CollisionPlane.h"
#include "RBCollisionCube.h"
#include "RBCollisionHandler.h"
//=============================================================================
class RBCollisionDetector
{
private:
	static float m_Mults[8][3];

private:
	void fillPointFaceCubeCube(const RBCollisionCube& cubeOne, const RBCollisionCube& cubeTwo, const Vector3D& toCenter, CollisionData* collisionData, unsigned int best, float penetration);
	Vector3D getContactPoint(const Vector3D& pointOne, const Vector3D& directionOne, float sizeOne, const Vector3D& pointTwo, const Vector3D directionTwo, float sizeTwo, bool useOne);

public:
	RBCollisionDetector();
	~RBCollisionDetector();

	unsigned int SphereAndSphere(const RBCollisionSphere& sphereOne, const RBCollisionSphere& sphereTwo, CollisionData* collisionData);
	unsigned int SphereAndHalfSpace(const RBCollisionSphere& sphere, const CollisionPlane& plane, CollisionHandler* collisionData);
	unsigned int SphereAndTruePlane(const RBCollisionSphere& sphere, const CollisionPlane& plane, CollisionData* collisionData);
	unsigned int CubeAndHalfSpace(const RBCollisionCube& cube, const CollisionPlane& plane, CollisionData* collisionData);
	unsigned int CubeAndSphere(const RBCollisionCube& cube, const RBCollisionSphere& sphere, CollisionData* collisionData);
	unsigned int CubeAndCube(const RBCollisionCube& cubeOne, const RBCollisionCube& cubeTwo, CollisionData* collisionData);
};
#endif