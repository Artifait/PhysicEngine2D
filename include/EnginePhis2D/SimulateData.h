#pragma once

// worldPhysic
// phis2D - Physic
<<<<<<< HEAD
namespace winSettup
{
	const float winSizeX = 16.f; // в метрах
	const float winSizeY = 12.f;
}
=======
>>>>>>> e800194a525aa6fce5d2a2e7157a3c25ecdaa9c2

namespace phis2D
{

	namespace worldPhysicConstant
	{
<<<<<<< HEAD
		const float maxRadius = 50.f;		// в метрах
		const float minRadius = 10.f;

		const float maxSide = 100.f; 
		const float minSide = 20.f; 

		const float scale = 250.f;			// сколько пикселей в метре
=======
		const float maxRadius = 200.f;		// в метрах
		const float minRadius = 0.01f;

		const float maxSide = 200.f; 
		const float minSide = 0.01f; 

		const float maxArea = maxSide * maxSide * 3.141593f;
		const float minArea = minSide * minSide * 3.141593f;
>>>>>>> e800194a525aa6fce5d2a2e7157a3c25ecdaa9c2

		const float MinDensity = 0.5f;		// g/cm^2 плотность
		const float MaxDensity = 21.4f;
	}

	const float PI = 3.141592f;

	inline float ToRadian(float degrees) {
		return degrees * phis2D::PI / 180.0f;
	}

	inline float ToDegrees(float radians)
	{
		return radians * 180.0f / phis2D::PI;
	}
}
