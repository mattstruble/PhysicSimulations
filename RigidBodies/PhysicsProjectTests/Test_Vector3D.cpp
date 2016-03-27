#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\PhysicsProject\Vector3D.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace PhysicsProjectTests
{
	TEST_CLASS(Vector3DTests)
	{
	public:

		TEST_METHOD(Vector_Magnitude)
		{
			Vector3D v1 = Vector3D(1, 2, 3);
			
			float magSq = v1.MagnitudeSquared();

			Assert::IsTrue(magSq == 14);

			Assert::IsTrue(sqrt(magSq) == v1.Magnitude());
		}

		TEST_METHOD(Vector_TestNormalized)
		{
			Vector3D v1 = Vector3D(2, 0, 0);
			v1.Normalize();

			Assert::IsTrue(v1 == Vector3D(1, 0, 0));
		}

		TEST_METHOD(Vector_TestMultiply)
		{
			Vector3D v1 = Vector3D(1, 1, 1);
			v1 = v1 * 2;

			Assert::IsTrue(v1 == Vector3D(2, 2, 2));
		}

		TEST_METHOD(Vector_TestDivide)
		{
			Vector3D v1 = Vector3D(2, 2, 2);
			v1 = v1 / 2;

			Assert::IsTrue(v1 == Vector3D(1, 1, 1));
		}

		TEST_METHOD(Vector_TestAddAndSubtract)
		{
			Vector3D v1 = Vector3D(1, 1, 1);
			v1 = v1 + Vector3D(1, 1, 1);

			Assert::IsTrue(v1 == Vector3D(2, 2, 2));

			v1 = v1 - Vector3D(2, 2, 2);

			Assert::IsTrue(v1 == Vector3D(0, 0, 0));
		}

		TEST_METHOD(Vector_TestDot)
		{
			Vector3D v1 = Vector3D(1, 1, 1);
			float dot = Vector3D::Dot(v1, Vector3D(2, 2, 2));

			Assert::AreEqual(dot, 6.0f);
		}

		TEST_METHOD(Vector_TestCross)
		{
			Vector3D v1 = Vector3D(3, -3, 1);
			Vector3D v2 = Vector3D(-12, 12, -4);

			Vector3D crossVector = Vector3D::Cross(v1, v2);

			Assert::IsTrue(crossVector == Vector3D(0, 0, 0));
		}

		TEST_METHOD(Vector_TestDistance)
		{
			Vector3D v1 = Vector3D(1, 2, 3);
			Vector3D v2 = Vector3D(2, 4, 6);

			float distanceSq = Vector3D::DistanceSQ(v1, v2);

			Assert::IsTrue(distanceSq == 14);

			Assert::IsTrue(sqrt(distanceSq) == Vector3D::Distance(v1, v2));
		}
	};
}