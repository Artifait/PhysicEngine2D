#pragma once
#include <StructData/v2f.h>

namespace phis2D
{
	struct Transform2D
	{
		v2f Position;
		float Cos;
		float Sin;
		Transform2D(v2f position, float angl) : Position{ position }
		{
			Cos = cos(angl);
			Sin = sin(angl);
		}
		Transform2D(float x, float y, float angl) : Position{ x, y }
		{
			Cos = cos(angl);
			Sin = sin(angl);
		}
		static v2f Transform(const v2f& v, const Transform2D& transform)
		{
			return v2f(
				transform.Cos * v.x - transform.Sin * v.y + transform.Position.x,
				transform.Sin * v.x + transform.Cos * v.y + transform.Position.y
			);
		}
	};
}