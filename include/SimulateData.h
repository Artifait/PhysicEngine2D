#pragma once

// worldPhysic
// phis2D - Physic

namespace phis2D
{

	namespace worldPhysicConstant
	{
		const float maxRadius = 1000.f;// 1 km
		const float minRadius = 0.01f; 

		const float maxSide = 1000.f;	 // 2 km длина
		const float minSide = 0.01f;	 

		const float maxArea = maxSide * maxSide;
		const float minArea = minSide * minSide;

		const float MinDensity = 0.5f;     // g/cm^2 плотность
		const float MaxDensity = 21.4f;
	}

	const float PI = 3.141592f;


	static double ToRadian(double degrees) {
		double radians = degrees * PI / 180.0;
		return radians;
	}

	static double ToDegrees(double radians) {
		double degrees = radians * 180.0 / PI;
		return degrees;
	}
}
