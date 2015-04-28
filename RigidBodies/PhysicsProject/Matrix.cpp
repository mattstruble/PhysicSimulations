//======================================================================
//File: Matrix.cpp
//Author: Matt Struble
//Purpose: Vector storage and operations
//======================================================================
#include "Matrix.h"
#include <cmath>
#include <limits>
//======================================================================
Matrix::Matrix()
: Matrix(2, true)
{
}

//--------------------------------------------------------------------------------
Matrix::Matrix(const Matrix& rhs)
{
	m_NumRows = rhs.GetNumRows();
	m_NumColumns = rhs.GetNumColumns();
	m_Size = m_NumRows * m_NumColumns;
	mp_Matrix = new float[m_Size];
	for (int i = 0; i < m_Size; ++i)
	{
		mp_Matrix[i] = rhs.mp_Matrix[i];
	}
}

//--------------------------------------------------------------------------------
Matrix::Matrix(int length, bool identiy)
: Matrix(length, length)
{
	if (identiy)
	{
		for (int row = 0; row < m_NumRows; row++)
		{
			mp_Matrix[row * m_NumRows + row] = 1;
		}
	}
}

//--------------------------------------------------------------------------------
Matrix::Matrix(int rows, int columns)
{
	initalizeMatrix(rows, columns);

	for (int i = 0; i < m_Size; ++i)
	{
		mp_Matrix[i] = 0;
	}
}

//--------------------------------------------------------------------------------
Matrix::Matrix(int rows, int columns, float* matrixValues)
{
	initalizeMatrix(rows, columns);

	for (int i = 0; i < m_Size; ++i)
	{
		mp_Matrix[i] = matrixValues[i];
	}
}

//--------------------------------------------------------------------------------
Matrix::~Matrix()
{
	delete [] mp_Matrix;
	mp_Matrix = nullptr;
}

//--------------------------------------------------------------------------------
void Matrix::initalizeMatrix(int rows, int columns)
{
	m_NumRows = rows;
	m_NumColumns = columns;
	m_Size = m_NumRows * m_NumColumns;
	mp_Matrix = new float[m_Size];
}

//--------------------------------------------------------------------------------
void Matrix::Set(int row, int column, float value)
{
	mp_Matrix[row * m_NumColumns + column] = value;
}

//--------------------------------------------------------------------------------
void Matrix::Set(int index, float value)
{
	mp_Matrix[index] = value;
}


//--------------------------------------------------------------------------------
float Matrix::Get(const int& row, const int& column) const
{
	return mp_Matrix[row * m_NumColumns + column];
}

//--------------------------------------------------------------------------------
float Matrix::Get(int index) const
{
	return mp_Matrix[index];
}

//--------------------------------------------------------------------------------
Matrix Matrix::CombinedMatrix(const Matrix& rhs, bool add) const
{
	Matrix returnedMatrix = Matrix(m_NumRows, m_NumColumns);

	for (int row = 0; row < m_NumRows; row++)
	{
		for (int col = 0; col < m_NumColumns; col++)
		{
			add ? returnedMatrix.Set(row, col, Get(row, col) + rhs.Get(row, col)) :
				returnedMatrix.Set(row, col, Get(row, col) - rhs.Get(row, col));
		}
	}

	return returnedMatrix;
}

//--------------------------------------------------------------------------------
Matrix Matrix::Transpose() const
{
	Matrix tranposed = Matrix(m_NumColumns, m_NumRows);

	for (int i = 0; i < m_Size; ++i) 
	{
		for (int j = 0; j < i; ++j) 
		{
			float tmp = Get(j, i);
			tranposed.Set(j, i, Get(i, j));
			tranposed.Set(i, j, tmp);
		}
	}

	return tranposed;
}

//--------------------------------------------------------------------------------
// http://easy-learn-c-language.blogspot.com/2013/02/numerical-methods-inverse-of-nxn-matrix.html
//--------------------------------------------------------------------------------
Matrix Matrix::Inverse() const
{
	if (m_NumColumns != m_NumRows)
	{
		return *this;
	}

	// Make double columns for room for inverted matrix
	Matrix inverted = Matrix(m_NumRows, m_NumColumns * 2);
	float ratio, a, tmp;

	int i, j, k;

	for (i = 0; i < m_NumRows; i++)
	{
		for (j = 0; j < m_NumColumns; j++)
		{
			inverted.Set(i, j, Get(i, j));
		}
	}
	
	// Form augmented matrix
	for (i = 0; i < m_NumRows; i++)
	{
		for (j = m_NumColumns; j < 2 * m_NumColumns; j++)
		{
			if (i == (j - m_NumColumns))
			{
				inverted.Set(i, j, 1);
			}
			else
			{
				inverted.Set(i, j, 0);
			}
		}
	}

	for (i = 0; i < m_NumRows; i++)
	{
		for (j = 0; j < m_NumRows; j++)
		{
			if (i != j)
			{
				ratio = inverted.Get(j, i) / inverted.Get(i, i);

				for (k = 0; k < 2 * m_NumColumns; k++)
				{
					tmp = inverted.Get(j, k) - (ratio * inverted.Get(i, k));
					inverted.Set(j, k, tmp);
				}
			}
		}
	}

	for (i = 0; i < m_NumRows; i++) 
	{
		a = inverted.Get(i, i);

		for (j = 0; j < 2 * m_NumColumns; j++)
		{
			inverted.Set(i, j, inverted.Get(i, j) / a);
		}
	}

	return inverted;
}

//--------------------------------------------------------------------------------
// http://easy-learn-c-language.blogspot.com/2013/02/numerical-methods-determinant-of-nxn.html
//--------------------------------------------------------------------------------
float Matrix::Determinant() const
{
	if (m_NumRows != m_NumColumns)
		return 0;

	float ratio, det = 1;

	Matrix UT = Matrix(*this);

	for (int i = 0; i < m_NumRows; i++)
	{
		for (int j = 0; j < m_NumRows; j++)
		{
			if (j > i)
			{
				ratio = UT.Get(j, i) / UT.Get(i, i);

				for (int k = 0; k < m_NumRows; k++)
				{
					float tmp = UT.Get(j, k);
					tmp -= ratio * UT.Get(i, k);
					UT.Set(j, k, tmp);
				}
			}
		}
	}

	for (int i = 0; i < m_NumRows; i++)
	{
		det *= UT.Get(i, i);
	}

	return det;
}

//--------------------------------------------------------------------------------------------
Vector3D Matrix::Transform(const Vector3D& vector)
{
	return (*this) * vector;
}

//--------------------------------------------------------------------------------------------
Vector3D Matrix::TransformInverse(const Vector3D& vector)
{
	return Inverse() * vector;
}

//--------------------------------------------------------------------------------------------
Vector3D Matrix::TransformTranspose(const Vector3D& vector)
{
	return Transpose() * vector;
}

//--------------------------------------------------------------------------------------------
void Matrix::SkewSymmetric(const Vector3D& vector)
{
	mp_Matrix[0] = mp_Matrix[4] = mp_Matrix[8] = 0;
	mp_Matrix[1] = -vector.Z;
	mp_Matrix[2] = vector.Y;
	mp_Matrix[3] = vector.Z;
	mp_Matrix[5] = -vector.X;
	mp_Matrix[6] = -vector.Y;
	mp_Matrix[7] = vector.X;
}

//--------------------------------------------------------------------------------------------
Vector3D Matrix::GetAxisVector(unsigned int index) const
{
	Vector3D axisVector = Vector3D(mp_Matrix[index], mp_Matrix[index + 4], mp_Matrix[index + 8]);
	return axisVector;
}

//--------------------------------------------------------------------------------
Matrix Matrix::Identity(int r, int c)
{
	Matrix identity = Matrix(r, c);

	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			if (i == j)
			{
				identity.Set(i, j, 1);
			}
			else
			{
				identity.Set(i, j, 0);
			}
		}
	}

	return identity;
}

//--------------------------------------------------------------------------------
Matrix Matrix::LookAt(const Vector3D& eye, const Vector3D& at, Vector3D up)
{
	if (abs(up.Magnitude() - 0.0f) < std::numeric_limits<double>::epsilon())
	{
		up = Vector3D(0, 1, 0);
	}

	Vector3D zaxis = (at - eye);
	zaxis.Normalize();

	Vector3D xaxis = Vector3D::Cross(up, zaxis);
	xaxis.Normalize();

	Vector3D yaxis = Vector3D::Cross(zaxis, xaxis);

	float* values = new float[16];
	values[0] = xaxis.X;
	values[1] = yaxis.X;
	values[2] = zaxis.X;
	values[3] = 0;
	values[4] = xaxis.Y;
	values[5] = yaxis.Y;
	values[6] = zaxis.Y;
	values[7] = 0;
	values[8] = xaxis.Z;
	values[9] = yaxis.Z;
	values[10] = zaxis.Z;
	values[11] = 0;
	values[12] = Vector3D::Dot(xaxis, -eye);
	values[13] = Vector3D::Dot(yaxis, -eye);
	values[14] = Vector3D::Dot(zaxis, -eye);
	values[15] = 1;

	return Matrix(4, 4, values);
}

//--------------------------------------------------------------------------------
Matrix Matrix::operator+(const Matrix& rhs) const
{
	if (!SameSize(rhs))
	{
		return *this;
	}

	return CombinedMatrix(rhs, true);
}

//--------------------------------------------------------------------------------
Matrix Matrix::operator-(const Matrix& rhs) const
{
	if (!SameSize(rhs))
	{
		return *this;
	}

	return CombinedMatrix(rhs, false);
}

//--------------------------------------------------------------------------------
Matrix Matrix::operator*(const Matrix& rhs) const
{
	if (m_NumColumns != rhs.GetNumRows())
	{
		return *this;
	}

	Matrix returnMatrix = Matrix(m_NumRows, rhs.GetNumColumns());

	for (int i = 0; i < m_NumRows; ++i)
	{
		for (int j = 0; j < returnMatrix.GetNumColumns(); ++j)
		{
			float value = 0;
			for (int k = 0; k < m_NumColumns; ++k)
			{
				value += Get(i, k) * rhs.Get(k, j);
			}
			returnMatrix.Set(i, j, value);
		}
	}

	return returnMatrix;
}

//--------------------------------------------------------------------------------
Matrix Matrix::operator*(const float& rhs) const
{
	float* tempArray = new float[m_Size];

	for (int i = 0; i < m_Size; ++i)
	{
		tempArray[i] = mp_Matrix[i] * rhs;
	}

	return Matrix(m_NumRows, m_NumColumns, tempArray);
}

//--------------------------------------------------------------------------------
Vector3D Matrix::operator*(const Vector3D& rhs) const
{
	float* tempArray = new float[3];
	tempArray[0] = rhs.X;
	tempArray[1] = rhs.Y;
	tempArray[2] = rhs.Z;

	Matrix vectorMatrix = Matrix(3, 1, tempArray);
	vectorMatrix *= *this;

	return Vector3D(vectorMatrix.Get(0), vectorMatrix.Get(1), vectorMatrix.Get(2));
}

//--------------------------------------------------------------------------------
Matrix& Matrix::operator=(const Matrix& rhs)
{
	m_NumRows = rhs.GetNumRows();
	m_NumColumns = rhs.GetNumColumns();
	m_Size = m_NumRows * m_NumColumns;
	mp_Matrix = new float[m_Size];
	for (int i = 0; i < m_Size; ++i)
	{
		mp_Matrix[i] = rhs.mp_Matrix[i];
	}

	return *this;
}

//--------------------------------------------------------------------------------
Matrix& Matrix::operator*=(const Matrix& rhs)
{
	return (*this = *this * rhs);
}

//--------------------------------------------------------------------------------
Matrix& Matrix::operator*=(const float& rhs)
{
	return (*this = *this * rhs);
}

//--------------------------------------------------------------------------------
Matrix& Matrix::operator+=(const Matrix& rhs)
{
	return (*this = *this + rhs);
}

//--------------------------------------------------------------------------------
Matrix& Matrix::operator-=(const Matrix& rhs)
{
	return (*this = *this - rhs);
}

//--------------------------------------------------------------------------------
bool Matrix::operator==(const Matrix& rhs) const
{
	if (!SameSize(rhs))
	{
		return false;
	}

	for (int row = 0; row < m_NumRows; row++)
	{
		for (int col = 0; col < m_NumColumns; col++)
		{
			if (Get(row, col) != rhs.Get(row, col))
			{
				return false;
			}
		}
	}

	return true;
}

//--------------------------------------------------------------------------------
bool Matrix::operator!=(const Matrix& rhs) const
{
	return !(*this == rhs);
}
//================================================================================