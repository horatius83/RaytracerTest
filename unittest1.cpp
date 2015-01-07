#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Raytracer/PacketVector.h"
#include "../Raytracer/Vector.h"
#include <stdlib.h>
#include <iostream>
#include <functional>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Math;

namespace RaytracerTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(VectorAdd)
		{
			srand(83);

			for (auto i = 0; i < 1000; ++i) {
				// Generate a bunch of numbers
				auto a = CreateRandomPacketVector();
				auto b = CreateRandomPacketVector();
				auto c = a;
				c.Add(b);
				
				for (auto i = 0; i < 4; ++i) {
					// Add them together 
					auto x = a.m_fX[i] + b.m_fX[i];
					auto y = a.m_fY[i] + b.m_fY[i];
					auto z = a.m_fZ[i] + b.m_fZ[i];

					// Make sure they are consistent
					Assert::IsTrue(AreFloatsEqual(x, c.m_fX[i]), L"x value was not the same");
					Assert::IsTrue(AreFloatsEqual(y, c.m_fY[i]), L"y value was not the same");
					Assert::IsTrue(AreFloatsEqual(z, c.m_fZ[i]), L"z value was not the same");
				}
			}
		}

		TEST_METHOD(VectorSub)
		{
			srand(8383);

			for (auto i = 0; i < 1000; ++i) {
				// Generate a bunch of numbers
				auto a = CreateRandomPacketVector();
				auto b = CreateRandomPacketVector();
				auto c = a;
				c.Sub(b);
				
				for (auto i = 0; i < 4; ++i) {
					// Subtract them
					auto x = a.m_fX[i] - b.m_fX[i];
					auto y = a.m_fY[i] - b.m_fY[i];
					auto z = a.m_fZ[i] - b.m_fZ[i];

					// Make sure they are consistent
					Assert::IsTrue(AreFloatsEqual(x, c.m_fX[i]), L"x value was not the same");
					Assert::IsTrue(AreFloatsEqual(y, c.m_fY[i]), L"y value was not the same");
					Assert::IsTrue(AreFloatsEqual(z, c.m_fZ[i]), L"z value was not the same");
				}
			}
		}

		TEST_METHOD(VectorScalarMul)
		{
			srand(38);

			for (auto i = 0; i < 1000; ++i) {
				// Generate a bunch of numbers
				auto a = CreateRandomPacketVector();
				auto v = CreateRandomVector();
				auto c = PacketVector();
				c.Mul(v.GetSse(), a);

				float scalar[4] = { v.GetX(), v.GetY(), v.GetZ(), v.GetW() };

				for (auto i = 0; i < 4; ++i) {
					// Multiply them
					auto x = a.m_fX[i] * scalar[i];
					auto y = a.m_fY[i] * scalar[i];
					auto z = a.m_fZ[i] * scalar[i];

					// Make sure they are consistent
					Assert::IsTrue(AreFloatsEqual(x, c.m_fX[i]), L"x value was not the same");
					Assert::IsTrue(AreFloatsEqual(y, c.m_fY[i]), L"y value was not the same");
					Assert::IsTrue(AreFloatsEqual(z, c.m_fZ[i]), L"z value was not the same");
				}
			}
		}

		TEST_METHOD(VectorVectorMul)
		{
			srand(86);

			for (auto i = 0; i < 1000; ++i) {
				// Generate a bunch of numbers
				auto a = CreateRandomPacketVector();
				auto b = CreateRandomPacketVector();
				auto c = PacketVector();
				c.Mul(a, b);

				for (auto i = 0; i < 4; ++i) {
					// Multiply them
					auto x = a.m_fX[i] * b.m_fX[i];
					auto y = a.m_fY[i] * b.m_fY[i];
					auto z = a.m_fZ[i] * b.m_fZ[i];

					// Make sure they are consistent
					Assert::IsTrue(AreFloatsEqual(x, c.m_fX[i]), L"x value was not the same");
					Assert::IsTrue(AreFloatsEqual(y, c.m_fY[i]), L"y value was not the same");
					Assert::IsTrue(AreFloatsEqual(z, c.m_fZ[i]), L"z value was not the same");
				}
			}
		}
		
		TEST_METHOD(VectorCrossProduct) 
		{
			srand(8383);

			for (auto i = 0; i < 1000; ++i) {
				// Generate a bunch of numbers
				auto a = CreateRandomPacketVector();
				auto b = CreateRandomPacketVector();
				auto c = a.DotProduct(b);

				for (auto i = 0; i < 4; ++i) {
					auto x0 = a.m_fX[i];
					auto y0 = a.m_fY[i];
					auto z0 = a.m_fZ[i];

					auto x1 = b.m_fX[i];
					auto y1 = b.m_fY[i];
					auto z1 = b.m_fZ[i];

					auto dotProduct = x0 * x1 + y0 * y1 + z0 * z1;

					Assert::IsTrue(AreFloatsEqual(dotProduct, c.Get(i)), L"Dot product was not equal");
				}
			}
		}

		TEST_METHOD(VectorNormalize)
		{
			srand(68);

			for (auto i = 0; i < 1000; ++i) {
				// Generate a bunch of numbers
				auto a = CreateRandomPacketVector();
				a.Normalize();
				auto c = a;
				c.Normalize();

				for (auto i = 0; i < 4; ++i) {
					// Normalize them
					auto x = a.m_fX[i];
					auto y = a.m_fY[i];
					auto z = a.m_fZ[i];

					auto invMagnitude = (float)(1.0 / sqrt(x*x + y*y + z*z));

					// Make sure they are consistent
					Assert::IsTrue(AreFloatsEqual(x * invMagnitude, c.m_fX[i]), L"x values were not the same.");
					Assert::IsTrue(AreFloatsEqual(y * invMagnitude, c.m_fY[i]), L"x values were not the same.");
					Assert::IsTrue(AreFloatsEqual(z * invMagnitude, c.m_fZ[i]), L"x values were not the same.");
				}
			}
		}
	private:
		PacketVector CreateRandomPacketVector() {
			Vector xs, ys, zs, ws;
			xs = CreateRandomVector();
			ys = CreateRandomVector();
			zs = CreateRandomVector();
			
			PacketVector rv;
			rv.m_sseX = xs.GetSse();
			rv.m_sseY = ys.GetSse();
			rv.m_sseZ = zs.GetSse();

			return rv;
		}

		Vector CreateRandomVector() {
			Vector v;
			v.Set(rand(), rand(), rand(), rand());
			return v;
		}

		bool AreFloatsEqual(float x, float y) { return fabs(x - y) < GetEpsilon(); }

		float GetEpsilon() { return 0.00001; }
	};
}