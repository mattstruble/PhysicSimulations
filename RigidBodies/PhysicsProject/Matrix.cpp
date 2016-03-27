//======================================================================
//File: Matrix.cpp
//Author: Matt Struble
//Purpose: Vector storage and operations
//======================================================================
#include "Matrix.h"
#include <cmath>
#include <limits>
#include <sstream>
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
	Matrix transpose = Matrix(m_NumColumns, m_NumRows);

	for (int i = 0; i < m_NumRows; i++)
	{
		for (int j = 0; j < m_NumColumns; j++)
		{
			transpose.Set(j, i, Get(i, j));
		}
	}

	return transpose;
}

//--------------------------------------------------------------------------------
Matrix Matrix::Inverse() const
{
	if (m_NumColumns == 4)
		return Inverse44();
	else if (m_NumColumns == 3)
		return Inverse33();
	else if (m_NumColumns == 2)
		return Inverse22();
	else
		return InverseNN();
}

//--------------------------------------------------------------------------------
Matrix Matrix::Inverse22() const
{
	Matrix m = *this;

	if (m.Determinant() != 0)
	{
		float invDet = 1 / m.Determinant();

		Matrix mInv = Matrix(2, 2);

		mInv.Set(0, 0, (m.Get(1, 1) * invDet));
		mInv.Set(0, 1, (-m.Get(0, 1) * invDet));
		mInv.Set(1, 0, (-m.Get(1, 0) * invDet));
		mInv.Set(1, 1, (m.Get(0, 0) * invDet));

		m = mInv;

		return m;
	}

	return Matrix(m.GetNumRows(), m.GetNumColumns());
}

//--------------------------------------------------------------------------------
Matrix Matrix::Inverse33() const
{
	Matrix m = *this;

	if (m.Determinant() != 0)
	{
		float invDet = 1 / m.Determinant();

		Matrix mInv = Matrix(3, 3);

		mInv.Set(0, 0, (m.Get(1, 1) * m.Get(2, 2) - m.Get(2, 1) * m.Get(1, 2)) * invDet);
		mInv.Set(0, 1, (m.Get(0, 2) * m.Get(2, 1) - m.Get(0, 1) * m.Get(2, 2)) * invDet);
		mInv.Set(0, 2, (m.Get(0, 1) * m.Get(1, 2) - m.Get(0, 2) * m.Get(1, 1)) * invDet);
		mInv.Set(1, 0, (m.Get(1, 2) * m.Get(2, 0) - m.Get(1, 0) * m.Get(2, 2)) * invDet);
		mInv.Set(1, 1, (m.Get(0, 0) * m.Get(2, 2) - m.Get(0, 2) * m.Get(2, 0)) * invDet);
		mInv.Set(1, 2, (m.Get(1, 0) * m.Get(0, 2) - m.Get(0, 0) * m.Get(1, 2)) * invDet);
		mInv.Set(2, 0, (m.Get(1, 0) * m.Get(2, 1) - m.Get(2, 0) * m.Get(1, 1)) * invDet);
		mInv.Set(2, 1, (m.Get(2, 0) * m.Get(0, 1) - m.Get(0, 0) * m.Get(2, 1)) * invDet);
		mInv.Set(2, 2, (m.Get(0, 0) * m.Get(1, 1) - m.Get(1, 0) * m.Get(0, 1)) * invDet);

		m = mInv;

		return m;
	}

	return Matrix(m.GetNumRows(), m.GetNumColumns());
}

//--------------------------------------------------------------------------------
Matrix Matrix::Inverse44() const
{
	float inv[16], det;

	float* m = mp_Matrix;

	inv[0] = m[5] * m[10] * m[15] -
		m[5] * m[11] * m[14] -
		m[9] * m[6] * m[15] +
		m[9] * m[7] * m[14] +
		m[13] * m[6] * m[11] -
		m[13] * m[7] * m[10];

	inv[4] = -m[4] * m[10] * m[15] +
		m[4] * m[11] * m[14] +
		m[8] * m[6] * m[15] -
		m[8] * m[7] * m[14] -
		m[12] * m[6] * m[11] +
		m[12] * m[7] * m[10];

	inv[8] = m[4] * m[9] * m[15] -
		m[4] * m[11] * m[13] -
		m[8] * m[5] * m[15] +
		m[8] * m[7] * m[13] +
		m[12] * m[5] * m[11] -
		m[12] * m[7] * m[9];

	inv[12] = -m[4] * m[9] * m[14] +
		m[4] * m[10] * m[13] +
		m[8] * m[5] * m[14] -
		m[8] * m[6] * m[13] -
		m[12] * m[5] * m[10] +
		m[12] * m[6] * m[9];

	inv[1] = -m[1] * m[10] * m[15] +
		m[1] * m[11] * m[14] +
		m[9] * m[2] * m[15] -
		m[9] * m[3] * m[14] -
		m[13] * m[2] * m[11] +
		m[13] * m[3] * m[10];

	inv[5] = m[0] * m[10] * m[15] -
		m[0] * m[11] * m[14] -
		m[8] * m[2] * m[15] +
		m[8] * m[3] * m[14] +
		m[12] * m[2] * m[11] -
		m[12] * m[3] * m[10];

	inv[9] = -m[0] * m[9] * m[15] +
		m[0] * m[11] * m[13] +
		m[8] * m[1] * m[15] -
		m[8] * m[3] * m[13] -
		m[12] * m[1] * m[11] +
		m[12] * m[3] * m[9];

	inv[13] = m[0] * m[9] * m[14] -
		m[0] * m[10] * m[13] -
		m[8] * m[1] * m[14] +
		m[8] * m[2] * m[13] +
		m[12] * m[1] * m[10] -
		m[12] * m[2] * m[9];

	inv[2] = m[1] * m[6] * m[15] -
		m[1] * m[7] * m[14] -
		m[5] * m[2] * m[15] +
		m[5] * m[3] * m[14] +
		m[13] * m[2] * m[7] -
		m[13] * m[3] * m[6];

	inv[6] = -m[0] * m[6] * m[15] +
		m[0] * m[7] * m[14] +
		m[4] * m[2] * m[15] -
		m[4] * m[3] * m[14] -
		m[12] * m[2] * m[7] +
		m[12] * m[3] * m[6];

	inv[10] = m[0] * m[5] * m[15] -
		m[0] * m[7] * m[13] -
		m[4] * m[1] * m[15] +
		m[4] * m[3] * m[13] +
		m[12] * m[1] * m[7] -
		m[12] * m[3] * m[5];

	inv[14] = -m[0] * m[5] * m[14] +
		m[0] * m[6] * m[13] +
		m[4] * m[1] * m[14] -
		m[4] * m[2] * m[13] -
		m[12] * m[1] * m[6] +
		m[12] * m[2] * m[5];

	inv[3] = -m[1] * m[6] * m[11] +
		m[1] * m[7] * m[10] +
		m[5] * m[2] * m[11] -
		m[5] * m[3] * m[10] -
		m[9] * m[2] * m[7] +
		m[9] * m[3] * m[6];

	inv[7] = m[0] * m[6] * m[11] -
		m[0] * m[7] * m[10] -
		m[4] * m[2] * m[11] +
		m[4] * m[3] * m[10] +
		m[8] * m[2] * m[7] -
		m[8] * m[3] * m[6];

	inv[11] = -m[0] * m[5] * m[11] +
		m[0] * m[7] * m[9] +
		m[4] * m[1] * m[11] -
		m[4] * m[3] * m[9] -
		m[8] * m[1] * m[7] +
		m[8] * m[3] * m[5];

	inv[15] = m[0] * m[5] * m[10] -
		m[0] * m[6] * m[9] -
		m[4] * m[1] * m[10] +
		m[4] * m[2] * m[9] +
		m[8] * m[1] * m[6] -
		m[8] * m[2] * m[5];

	det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

	if (det == 0) 
		return Matrix(m_NumRows, m_NumColumns);

	det = 1.0f / det;

	for (int i = 0; i < 16; i++)
	{
		inv[i] *= det;
	}

	return Matrix(4, 4, inv);
}

//--------------------------------------------------------------------------------
// http://easy-learn-c-language.blogspot.com/2013/02/numerical-methods-inverse-of-nxn-matrix.html
//--------------------------------------------------------------------------------
Matrix Matrix::InverseNN() const
{
	Matrix inverse = *this;

	if (inverse.Determinant() != 0)
	{
		int n = inverse.GetNumRows();
		int i, j, k;
		float d;
		for (int i = 0; i < n; i++)
		{
			for (j = 0; j < 2 * n; j++)
			{
				if (j == (i + n))
				{
					inverse.Set(i, j, 1);
				}
			}
		}
		for (i = n; i > 1; i--)
		{
			if (inverse.Get(i - 1, 1) < inverse.Get(i, 1))
			{
				for (j = 1; j <= n * 2; j++)
				{
					d = inverse.Get(i, j);
					inverse.Set(i, j, inverse.Get(i - 1, j));
					inverse.Set(i - 1, j, d);
				}
			}
		}
		for (i = 1; i <= n; i++)
		{
			for (j = 1; j <= n * 2; j++)
			{
				if (j != i)
				{
					d = inverse.Get(j, i) / inverse.Get(i, i);
					for (k = 1; k <= n * 2; k++)
					{
						inverse.Set(j, k, inverse.Get(j, k) - (inverse.Get(i, k) * d));
					}
				}
			}
		}
		for (i = 1; i <= n; i++)
		{
			d = inverse.Get(i, i);
			for (j = 1; j <= n * 2; j++)
			{
				inverse.Set(i, j, inverse.Get(i, j) / d);
			}
		}
		return inverse;
	}

	return Matrix(inverse.GetNumRows(), inverse.GetNumColumns());
}

//--------------------------------------------------------------------------------
float Matrix::Determinant() const
{
	if (m_NumRows != m_NumColumns)
		return 0;
	else if (m_NumColumns == 3)
		return Determinant33();
	else if (m_NumColumns == 2)
		return Determinant22();
	else
		return DeterminantNN();
}

//--------------------------------------------------------------------------------
float Matrix::Determinant22() const
{
	Matrix m = *this;

	float det = (m.Get(0, 0) * m.Get(1, 1)) - (m.Get(0, 1) * m.Get(1, 0));

	return det;
}

//--------------------------------------------------------------------------------
float Matrix::Determinant33() const
{
	Matrix m = *this;

	float det = m.Get(0, 0) * (m.Get(1, 1) * m.Get(2, 2) - m.Get(2, 1) * m.Get(1, 2)) -
		m.Get(0, 1) * (m.Get(1, 0) * m.Get(2, 2) - m.Get(1, 2) * m.Get(2, 0)) +
		m.Get(0, 2) * (m.Get(1, 0) * m.Get(2, 1) - m.Get(1, 1) * m.Get(2, 0));

	return det;
}

//--------------------------------------------------------------------------------
float Matrix::Determinant44() const
{

	return 0;
}

//--------------------------------------------------------------------------------
// http://easy-learn-c-language.blogspot.com/2013/02/numerical-methods-determinant-of-nxn.html
//--------------------------------------------------------------------------------
float Matrix::DeterminantNN() const
{
	if (m_NumRows != m_NumColumns)
		return 0;

	float ratio, det = 1;

	Matrix UT = *this;

	for (int i = 0; i < m_NumRows; i++)
	{
		for (int j = 0; j < m_NumRows; j++)
		{
			if (j > i)
			{
				ratio = UT.Get(j, i) / UT.Get(i, i);

				for (int k = 0; k < m_NumRows; k++)
				{
					UT.Set(j, k, (UT.Get(j, k) - (ratio*UT.Get(i, k))));
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
	if (m_NumColumns * m_NumRows == 9)
	{
		mp_Matrix[0] = mp_Matrix[4] = mp_Matrix[8] = 0;
		mp_Matrix[1] = -vector.Z;
		mp_Matrix[2] = vector.Y;
		mp_Matrix[3] = vector.Z;
		mp_Matrix[5] = -vector.X;
		mp_Matrix[6] = -vector.Y;
		mp_Matrix[7] = vector.X;
	}
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

	Matrix tmpMatrix = Matrix(*this);

	tmpMatrix *= vectorMatrix;

	return Vector3D(tmpMatrix.Get(0), tmpMatrix.Get(1), tmpMatrix.Get(2));
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

//--------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& stream, const Matrix& matrix)
{
	stream << "[";

	int r = matrix.GetNumRows();
	int c = matrix.GetNumColumns();

	for (int i = 0; i < r * c; i++)
	{
		stream << matrix.Get(i) << ", ";

		if (i % c == 0)
			stream << "; ";
	}
	stream << "]";

	return stream;
}

//--------------------------------------------------------------------------------
std::string Matrix::ToString() const
{
	std::ostringstream ss;
	ss << (*this);
	return ss.str();
}
//================================================================================