//======================================================================
//File: Vector2D.h
//Author: Matt Struble
//======================================================================
#include "Vector2D.h"
#include <cmath>
//======================================================================
Vector2D::Vector2D()
{
	X = 0;
	Y = 0;
}
//======================================================================
Vector2D::Vector2D(float x, float y)
{
	X = x;
	Y = y;
}

//--------------------------------------------------------------------------------
Vector2D::~Vector2D()
{

}

//--------------------------------------------------------------------------------
Vector2D Vector2D::operator*(const float& rhs) const
{
	return Vector2D(X * rhs, Y * rhs);
}

//--------------------------------------------------------------------------------
Vector2D Vector2D::operator/(const float& rhs) const
{
	return Vector2D(X / rhs, Y / rhs);
}

//--------------------------------------------------------------------------------
Vector2D Vector2D::operator+(const Vector2D& rhs) const
{
	return Vector2D(X + rhs.X, Y + rhs.Y);
}

//--------------------------------------------------------------------------------
Vector2D Vector2D::operator-(const Vector2D& rhs) const
{
	return Vector2D(X - rhs.X, Y - rhs.Y);
}

//--------------------------------------------------------------------------------
Vector2D& Vector2D::operator=(const Vector2D& rhs)
{
	X = rhs.X;
	Y = rhs.Y;

	return *this;
}

//--------------------------------------------------------------------------------
Vector2D& Vector2D::operator*=(const float& rhs)
{
	return (*this = *this * rhs);
}

//--------------------------------------------------------------------------------
Vector2D& Vector2D::operator/=(const float& rhs)
{
	return (*this = *this / rhs);
}

//--------------------------------------------------------------------------------
Vector2D& Vector2D::operator+=(const Vector2D& rhs)
{
	return (*this = *this + rhs);
}

//--------------------------------------------------------------------------------
Vector2D& Vector2D::operator-=(const Vector2D& rhs)
{
	return (*this = *this - rhs);
}

//--------------------------------------------------------------------------------
bool Vector2D::operator==(const Vector2D& rhs) const
{
	return X == rhs.X && Y == rhs.Y;
}

//--------------------------------------------------------------------------------
bool Vector2D::operator!=(const Vector2D& rhs) const
{
	return !(*this == rhs);
}

//--------------------------------------------------------------------------------
Vector2D Vector2D::Lerp(const Vector2D& start, const Vector2D& end, const float& percent)
{
	return start + ((end - start) * percent);
}

//--------------------------------------------------------------------------------
std::string Vector2D::ToString()
{
	std::string output = "Vector2D(" + std::to_string(X) + ", " + std::to_string(Y) + ")";
	return output;
}
//================================================================================