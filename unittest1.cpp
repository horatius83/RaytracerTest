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

				// Add them together 
				float xs[4];
				float ys[4];
				float zs[4];

				for (auto i = 0; i < 4; ++i) {
					xs[i] = a.m_fX[i] + b.m_fX[i];
					ys[i] = a.m_fY[i] + b.m_fY[i];
					zs[i] = a.m_fZ[i] + b.m_fZ[i];

					// Make sure they are consistent
					Assert::AreEqual(xs[i], c.m_fX[i], L"x value was not the same.");
					Assert::AreEqual(ys[i], c.m_fY[i], L"y value was not the same.");
					Assert::AreEqual(zs[i], c.m_fZ[i], L"z value was not the same.");
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

				// Subtract them
				float xs[4];
				float ys[4];
				float zs[4];

				for (auto i = 0; i < 4; ++i) {
					xs[i] = a.m_fX[i] - b.m_fX[i];
					ys[i] = a.m_fY[i] - b.m_fY[i];
					zs[i] = a.m_fZ[i] - b.m_fZ[i];

					// Make sure they are consistent
					Assert::AreEqual(xs[i], c.m_fX[i], L"x value was not the same.");
					Assert::AreEqual(ys[i], c.m_fY[i], L"y value was not the same.");
					Assert::AreEqual(zs[i], c.m_fZ[i], L"z value was not the same.");
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
	};
}