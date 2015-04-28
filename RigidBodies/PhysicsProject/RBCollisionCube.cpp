//======================================================================
//File: RBCollisionCube.h
//Author: Matt Struble
//======================================================================
#include "RBCollisionCube.h"
//=============================================================================
RBCollisionCube::RBCollisionCube(RigidBody* rigidBody, Vector3D halfSize, Matrix offset)
:RBCollisionPrimitive(rigidBody, offset)
{
	m_HalfSize = halfSize;

	m_Vertices[0] = Vector3D(-m_HalfSize.X, -m_HalfSize.Y, -m_HalfSize.Z);
	m_Vertices[1] = Vector3D(-m_HalfSize.X, -m_HalfSize.Y, m_HalfSize.Z);
	m_Vertices[2] = Vector3D(-m_HalfSize.X, m_HalfSize.Y, -m_HalfSize.Z);
	m_Vertices[3] = Vector3D(-m_HalfSize.X, m_HalfSize.Y, m_HalfSize.Z);
	m_Vertices[4] = Vector3D(m_HalfSize.X, -m_HalfSize.Y, -m_HalfSize.Z);
	m_Vertices[5] = Vector3D(m_HalfSize.X, -m_HalfSize.Y, m_HalfSize.Z);
	m_Vertices[6] = Vector3D(m_HalfSize.X, m_HalfSize.Y, -m_HalfSize.Z);
	m_Vertices[7] = Vector3D(m_HalfSize.X, m_HalfSize.Y, m_HalfSize.Z);

	for (unsigned i = 0; i < 8; i++)
	{
		m_Vertices[i] = m_Offset * m_Vertices[i];
	}
}

//-----------------------------------------------------------------------------
RBCollisionCube::~RBCollisionCube()
{
}
//=============================================================================