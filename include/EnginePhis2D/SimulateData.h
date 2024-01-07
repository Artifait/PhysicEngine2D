#pragma once

// worldPhysic
// phis2D - Physic
namespace winSettup
{
	const float winSizeX = 16.f; // � ������
	const float winSizeY = 12.f;
}


namespace phis2D
{

	namespace worldPhysicConstant
	{
		const float maxRadius = 50.f;		// � ������
		const float minRadius = 10.f;

		const float maxSide = 100.f; 
		const float minSide = 20.f; 

		const float scale = 250.f;			// ������� �������� � �����


		const float MinDensity = 0.5f;		// g/cm^2 ���������
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
