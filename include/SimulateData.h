#pragma once

// worldPhysic
// phis2D - Physic

namespace phis2D
{

	namespace worldPhysicConstant
	{
		const float maxRadius = 200.f;// 1 km
		const float minRadius = 0.01f; 

		const float maxSide = 200.f;	 
		const float minSide = 0.01f;	 

		const float maxArea = maxSide * maxSide * 4.f;
		const float minArea = minSide * minSide * 4.f;

		const float MinDensity = 0.5f;     // g/cm^2 плотность
		const float MaxDensity = 21.4f;
	}

	const float PI = 3.141592f;


	static inline float ToRadian(float degrees) {
		return degrees * PI / 180.0f;
	}

	static inline float ToDegrees(float radians) {
		return radians * 180.0f / PI;
	}

}
