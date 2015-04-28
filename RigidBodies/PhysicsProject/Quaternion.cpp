//======================================================================
//File: Quaternion.cpp
//Author: Matt Struble
//======================================================================
#include "Quaternion.h"
#include "Vector3D.h"
#include <math.h>
//======================================================================
Quaternion::Quaternion()
{
	R = 0;
	I = 0;
	J = 0;
	K = 0;
}

//-----------------------------------------------------------------------------
Quaternion::Quaternion(float r, float i, float j, float k)
{
	R = r; 
	I = i;
	J = j;
	K = k;
}

//-----------------------------------------------------------------------------
Quaternion::Quaternion(const Vector3D& rhs)
{
	R = 0;
	I = rhs.X;
	J = rhs.Y;
	K = rhs.Z;
}

//-----------------------------------------------------------------------------
Quaternion::Quaternion(const Quaternion& rhs)
{
	R = rhs.R;
	I = rhs.I;
	J = rhs.J;
	K = rhs.K;
}

//-----------------------------------------------------------------------------
Quaternion::~Quaternion()
{
}

//-----------------------------------------------------------------------------
void Quaternion::Normalize()
{
	float len = R*R + I*I + J*J + K*K;

	if (len == 0)
	{
		R = 1;
		return;
	}

	len = 1.0f / sqrtf(len);

	R *= len;
	I *= len;
	J *= len;
	K *= len;
}

//-----------------------------------------------------------------------------
Quaternion Quaternion::operator*(const Quaternion& rhs)
{
	Quaternion q = Quaternion((*this));

	R = q.R * rhs.R - q.I * rhs.I - q.J * rhs.J - q.K * rhs.K;
	I = q.R * rhs.I + q.I * rhs.R + q.J * rhs.K - q.K * rhs.J;
	J = q.R * rhs.J + q.J * rhs.R + q.K * rhs.I - q.I * rhs.K;
	K = q.R * rhs.K + q.K * rhs.R + q.I * rhs.J - q.J * rhs.I;

	return q;
}

//-----------------------------------------------------------------------------
Quaternion& Quaternion::operator*=(const Quaternion& rhs)
{
	return (*this = *this * rhs);
}

//--------------------------------------------------------------------------------
Quaternion& Quaternion::operator=(const Quaternion& rhs)
{
	R = rhs.R;
	I = rhs.I;
	J = rhs.J;
	K = rhs.K;

	return *this;
}

//--------------------------------------------------------------------------------
bool Quaternion::operator==(const Quaternion& rhs) const
{
	return R == rhs.R && I == rhs.I &&  J == rhs.J && K == rhs.K;
}

//--------------------------------------------------------------------------------
bool Quaternion::operator!=(const Quaternion& rhs) const
{
	return !(*this == rhs);
}

//-----------------------------------------------------------------------------
void Quaternion::VectorRotation(const Vector3D& rhs)
{
	Quaternion q = Quaternion(rhs);

	(*this) *= q;
}

//-----------------------------------------------------------------------------
void Quaternion::VectorScaling(const Vector3D& rhs, float scale)
{
	Vector3D scaledVector = Vector3D(rhs);
	scaledVector *= scale;
	Quaternion q = Quaternion(scaledVector);

	q *= (*this);
	R += q.R * (0.5f);
	I += q.I * (0.5f);
	J += q.J * (0.5f);
	K += q.K * (0.5f);
}