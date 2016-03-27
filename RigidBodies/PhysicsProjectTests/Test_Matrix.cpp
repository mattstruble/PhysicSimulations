#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\PhysicsProject\Matrix.h"
#include "..\PhysicsProject\Vector3D.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace PhysicsProjectTests
{		
	TEST_CLASS(MatrixTests)
	{
	public:

		TEST_METHOD(Test_Identity)
		{
			float* startValues = new float[9] {
				1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 1.0f
			};
			Matrix startMatrix = Matrix(3, 3, startValues);

			Matrix identity = Matrix::Identity(3, 3);

			Assert::IsTrue(startMatrix.Inverse() == identity);
		}

		TEST_METHOD(Test_Addition)
		{
			float* aValues = new float[9] {
				1.0f, 2.0f, 3.0f,
				4.0f, 5.0f, 6.0f,
				7.0f, 8.0f, 9.0f
			};
			Matrix a = Matrix(3, 3, aValues);

			float* bValues = new float[9] {
				1.0f, 4.0f, 7.0f,
				2.0f, 5.0f, 8.0f,
				3.0f, 6.0f, 9.0f
			};
			Matrix b = Matrix(3, 3, bValues);

			float* cValues = new float[9] {
				2.0f, 6.0f, 10.0f,
				6.0f, 10.0f, 14.0f,
				10.0f, 14.0f, 18.0f
			};
			Matrix c = Matrix(3, 3, cValues);

			Assert::IsTrue(a + b == c);
		}

		TEST_METHOD(Test_Subtraction)
		{
			float* aValues = new float[9] {
				1.0f, 2.0f, 3.0f,
				4.0f, 5.0f, 6.0f,
				7.0f, 8.0f, 9.0f
			};
			Matrix a = Matrix(3, 3, aValues);

			float* bValues = new float[9] {
				1.0f, 4.0f, 7.0f,
				2.0f, 5.0f, 8.0f,
				3.0f, 6.0f, 9.0f
			};
			Matrix b = Matrix(3, 3, bValues);

			float* cValues = new float[9] {
				0.0f, -2.0f, -4.0f,
				2.0f, 0.0f, -2.0f,
				4.0f, 2.0f, 0.0f
			};
			Matrix c = Matrix(3, 3, cValues);

			Assert::IsTrue(a - b == c);
		}

		TEST_METHOD(Test_Float_Multiplication)
		{
			Matrix a = Matrix::Identity(3, 3);

			float b = 2.0f;

			float* cValues = new float[9] {
				2.0f, 0.0f, 0.0f,
				0.0f, 2.0f, 0.0f,
				0.0f, 0.0f, 2.0f
			};

			Matrix c = Matrix(3, 3, cValues);

			Assert::IsTrue(a * b == c);
		}

		TEST_METHOD(Test_Vector3D_Multiplication)
		{
			float* aValues = new float[9] {
				1.0f, 2.0f, 3.0f,
				4.0f, 5.0f, 6.0f,
				7.0f, 8.0f, 9.0f
			};
			Matrix a = Matrix(3, 3, aValues);

			Vector3D b = Vector3D(1, 2, 3);

			Vector3D c = Vector3D(14, 32, 50);

			Assert::IsTrue(a * b == c);
		}

		TEST_METHOD(Test_NxN_Multiplication)
		{
			float* aValues = new float[9] {
				1.0f, 2.0f, 3.0f,
				4.0f, 5.0f, 6.0f,
				7.0f, 8.0f, 9.0f
			};
			Matrix a = Matrix(3, 3, aValues);

			float* bValues = new float[9] {
				1.0f, 4.0f, 7.0f,
				2.0f, 5.0f, 8.0f,
				3.0f, 6.0f, 9.0f
			};
			Matrix b = Matrix(3, 3, bValues);

			float* cValues = new float[9] {
				14.0f, 32.0f, 50.0f,
				32.0f, 77.0f, 122.0f,
				50.0f, 122.0f, 194.0f
			};
			Matrix c = Matrix(3, 3, cValues);

			Assert::IsTrue(a * b == c);
		}

		TEST_METHOD(Test_te_Multiplication)
		{
			float* aValues = new float[9] {
				1.0f, 2.0f, 3.0f,
					4.0f, 5.0f, 6.0f,
					7.0f, 8.0f, 9.0f
			};
			Matrix a = Matrix(3, 3, aValues);

			float* bValues = new float[9] {
				1.0f, 4.0f, 7.0f,
					2.0f, 5.0f, 8.0f,
					3.0f, 6.0f, 9.0f
			};
			Matrix b = Matrix(3, 3, bValues);

			float* cValues = new float[9] {
				14.0f, 32.0f, 50.0f,
					32.0f, 77.0f, 122.0f,
					50.0f, 122.0f, 194.0f
			};
			Matrix c = Matrix(3, 3, cValues);

			a *= b;

			Assert::IsTrue(a == c);
		}

		TEST_METHOD(Test_MxN_Multiplication)
		{
			float* aValues = new float[9] {
				1.0f, 2.0f, 3.0f,
					4.0f, 5.0f, 6.0f,
					7.0f, 8.0f, 9.0f
			};
			Matrix a = Matrix(3, 3, aValues);

			float* bValues = new float[12] {
				1.0f, 4.0f, 7.0f, 1.0f,
				2.0f, 5.0f, 8.0f, 6.0f,
				3.0f, 6.0f, 9.0f, 0.0f
			};
			Matrix b = Matrix(3, 4, bValues);

			float* cValues = new float[12] {
				14.0f, 32.0f, 50.0f, 13.0f,
				32.0f, 77.0f, 122.0f, 34.0f,
				50.0f, 122.0f, 194.0f, 55.0f
			};
			Matrix c = Matrix(3, 4, cValues);

			Assert::IsTrue(a * b == c);
		}

		TEST_METHOD(Test_NxN_Transpose)
		{
			float* startValues = new float[9] {
				1.0f, 2.0f, 3.0f,
				4.0f, 5.0f, 6.0f,
				7.0f, 8.0f, 9.0f
			};
			Matrix startMatrix = Matrix(3, 3, startValues);

			float* transposeValues = new float[9] {
				1.0f, 4.0f, 7.0f,
				2.0f, 5.0f, 8.0f,
				3.0f, 6.0f, 9.0f
			};
			Matrix transpose = Matrix(3, 3, transposeValues);

			Assert::IsTrue(startMatrix.Transpose() == transpose);
		}

		TEST_METHOD(Test_MxN_Transpose)
		{
			float* startValues = new float[12] {
				1.0f, 2.0f, 3.0f, 4.0f,
				5.0f, 6.0f, 7.0f, 8.0f,
				9.0f, 10.0f, 11.0f, 12.0f
			};
			Matrix startMatrix = Matrix(3, 4, startValues);

			float* transposeValues = new float[12] {
				1.0f, 5.0f, 9.0f,
				2.0f, 6.0f, 10.0f,
				3.0f, 7.0f, 11.0f,
				4.0f, 8.0f, 12.0f
			};
			Matrix transpose = Matrix(4, 3, transposeValues);

			Assert::IsTrue(startMatrix.Transpose() == transpose);
		}

		TEST_METHOD(Test_3x3_Inverse)
		{
			float* startValues = new float[9] { 
				1.0f, 2.0f, 3.0f,
				0.0f, 1.0f, 4.0f,
				5.0f, 6.0f, 0.0f
			};
			Matrix startMatrix = Matrix(3, 3, startValues);

			float* invValues = new float[9] { 
				-24.0f, 18.0f, 5.0f,
				20.0f, -15.0f, -4.0f,
				-5.0f, 4.0f, 1.0f
			};
			Matrix invMatrix = Matrix(3, 3, invValues);

			Assert::IsTrue(startMatrix.Inverse() == invMatrix);
		}

		TEST_METHOD(Test_4x4_Inverse)
		{
			float* startValues = new float[16] {
				4.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 2.0f, 0.0f,
				0.0f, 1.0f, 2.0f, 0.0f,
				1.0f, 0.0f, 0.0f, 1.0f
			};
			Matrix startMatrix = Matrix(4, 4, startValues);

			float* invValues = new float[16] {
				0.25f,  0.0f, 0.0f, 0.0f,
				0.0f,  -1.0f, 1.0f, 0.0f,
				0.0f,   0.5f, 0.0f, 0.0f,
				-0.25f, 0.0f, 0.0f, 1.0f
			};
			Matrix invMatrix = Matrix(4, 4, invValues);

			Assert::IsTrue(startMatrix.Inverse() == invMatrix);
		}

	};
}

