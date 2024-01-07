#pragma once

// worldPhysic
// phis2D - Physic
namespace winSettup
{
	const float winSizeX = 16.f; // в метрах
	const float winSizeY = 12.f;
}


namespace phis2D
{

	namespace worldPhysicConstant
	{
		const float maxRadius = 50.f;		// в метрах
		const float minRadius = 10.f;

		const float maxSide = 100.f; 
		const float minSide = 20.f; 

		const float scale = 250.f;			// сколько пикселей в метре


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
