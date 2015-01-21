#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>
#include "../Raytracer/Sphere.h"
#include "../Raytracer/Vector.h"
#include <stdlib.h>
#include <iostream>
#include <functional>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Math;

namespace RaytracerTests
{
	TEST_CLASS(SphereTests)
	{
	public:
		TEST_METHOD(SetCenter)
		{
			auto x = 1.0f;
			auto y = 2.0f;
			auto z = -3.0f;
			auto center = Math::Vector(x, y, z);
			auto radius = 5.0f;
			auto sphere = Math::Sphere(center, radius);

			Assert::AreEqual(x, sphere.GetCenter().GetX(), L"x values were not equal");
			Assert::AreEqual(y, sphere.GetCenter().GetY(), L"y values were not equal");
			Assert::AreEqual(z, sphere.GetCenter().GetZ(), L"z values were not equal");
			Assert::AreEqual(radius, sphere.GetRadius(), L"radii were not equal");
		}

		TEST_METHOD(RayIntersection) 
		{
			auto origin = Math::Vector(0, 0, 0);
			auto direction = Math::Vector(1.0f, 0, 0);
			auto sphere = Math::Sphere(Math::Vector(20.0f, 0, 0), 1.0f);

			auto result = sphere.GetIntersection(origin, direction);
			Assert::IsTrue(std::get<0>(result), L"should have intersected");
			Assert::AreEqual(19.0f, std::get<1>(result), L"distance should have been 19");
		}

		TEST_METHOD(RayMiss) 
		{
			auto origin = Math::Vector(0, 0, 0);
			auto direction = Math::Vector(1.0f, 0, 0);
			auto sphere = Math::Sphere(Math::Vector(-20.0f, 0, 0), 1.0f);

			auto result = sphere.GetIntersection(origin, direction);
			Assert::IsFalse(std::get<0>(result), L"should not have intersected");
		}
	};
}