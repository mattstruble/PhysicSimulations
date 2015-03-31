//======================================================================
//File: Vector3D.h
//Author: Matt Struble
//Purpose: Vector storage and operations
//======================================================================
#include "Vector3D.h"
#include <cmath>
//======================================================================
Vector3D const Vector3D::Zero = Vector3D(0, 0, 0);
//======================================================================
Vector3D::Vector3D()
{
	X = 0;
	Y = 0;
	Z = 0;
}
//======================================================================
Vector3D::Vector3D(double x, double y, double z)
{
	X = x;
	Y = y;
	Z = z;
}

//--------------------------------------------------------------------------------
Vector3D::~Vector3D()
{
}

//--------------------------------------------------------------------------------
Vector3D Vector3D::operator*(const float& rhs) const
{
	return Vector3D(X * rhs, Y * rhs, Z * rhs);
}

//--------------------------------------------------------------------------------
Vector3D Vector3D::operator/(const float& rhs) const
{
	return Vector3D(X / rhs, Y / rhs, Z / rhs);
}

//--------------------------------------------------------------------------------
Vector3D Vector3D::operator+(const Vector3D& rhs) const
{
	return Vector3D(X + rhs.X, Y + rhs.Y, Z + rhs.Z);
}

//--------------------------------------------------------------------------------
Vector3D Vector3D::operator-(const Vector3D& rhs) const
{
	return Vector3D(X - rhs.X, Y - rhs.Y, Z - rhs.Z);
}

Vector3D Vector3D::operator-() const
{
	return *this * -1;
}

//--------------------------------------------------------------------------------
Vector3D& Vector3D::operator=(const Vector3D& rhs)
{
	X = rhs.X;
	Y = rhs.Y;
	Z = rhs.Z;

	return *this;
}

//--------------------------------------------------------------------------------
Vector3D& Vector3D::operator*=(const float& rhs)
{
	return (*this = *this * rhs);
}

//--------------------------------------------------------------------------------
Vector3D& Vector3D::operator/=(const float& rhs)
{
	return (*this = *this / rhs);
}

//--------------------------------------------------------------------------------
Vector3D& Vector3D::operator+=(const Vector3D& rhs)
{
	return (*this = *this + rhs);
}

//--------------------------------------------------------------------------------
Vector3D& Vector3D::operator-=(const Vector3D& rhs)
{
	return (*this = *this - rhs);
}

//--------------------------------------------------------------------------------
bool Vector3D::operator==(const Vector3D& rhs) const
{
	return X == rhs.X && Y == rhs.Y &&  Z == rhs.Z;
}

//--------------------------------------------------------------------------------
bool Vector3D::operator!=(const Vector3D& rhs) const
{
	return !(*this == rhs);
}

//--------------------------------------------------------------------------------
double Vector3D::Dot(const Vector3D& lhs, const Vector3D& rhs)
{
	return lhs.X * rhs.X + lhs.Y * rhs.Y + lhs.Z * rhs.Z;
}

//--------------------------------------------------------------------------------
Vector3D Vector3D::Cross(const Vector3D& lhs, const Vector3D& rhs)
{
	return Vector3D(lhs.Y * rhs.Z - lhs.Z*rhs.Y, lhs.Z * rhs.X - lhs.X * rhs.Z, lhs.X * rhs.Y - lhs.Y * rhs.X);
}

//--------------------------------------------------------------------------------
Vector3D Vector3D::Lerp(const Vector3D& start, const Vector3D& end, const float& percent)
{
	return start + ((end - start) * percent);
}

//--------------------------------------------------------------------------------
Vector3D Vector3D::SLerp(const Vector3D& start, const Vector3D& end, const float& percent)
{
	double dot = Dot(start, end);

	// clamp
	dot = dot > 1.0f ? 1.0f : dot;
	dot = dot < -1.0f ? -1.0f : dot;

	double theta = acos(dot) * percent;

	Vector3D relativeVec = end - start*dot;
	relativeVec.Normalize();

	return ((start*cos(theta)) + (relativeVec*sin(theta)));
}

//--------------------------------------------------------------------------------
Vector3D Vector3D::NLerp(const Vector3D& start, const Vector3D& end, const float& percent)
{
	return Lerp(start, end, percent).Normalized();
}

//--------------------------------------------------------------------------------
double Vector3D::Distance(const Vector3D& lhs, const Vector3D& rhs)
{
	return sqrt(Vector3D::DistanceSQ(lhs, rhs));
}

//--------------------------------------------------------------------------------
double Vector3D::DistanceSQ(const Vector3D& lhs, const Vector3D& rhs)
{
	return pow(lhs.X - rhs.X, 2) + pow(lhs.Y - rhs.Y, 2) + pow(lhs.Z - rhs.Z, 2);
}

//--------------------------------------------------------------------------------
double Vector3D::Magnitude()
{
	return sqrt(MagnitudeSquared());
}

//--------------------------------------------------------------------------------
double Vector3D::MagnitudeSquared()
{
	return (X * X) + (Y * Y) + (Z * Z);
}

//--------------------------------------------------------------------------------
Vector3D Vector3D::Normalized()
{
	return *this / Magnitude();
}

//--------------------------------------------------------------------------------
void Vector3D::Normalize()
{
	*this = Normalized();
}

std::string Vector3D::ToString()
{
	std::string output = "Vector3D(" + std::to_string(X) + ", " + std::to_string(Y) + ", " + std::to_string(Z) + ")";
	return output;
}
//================================================================================