#pragma once
#include <Shapes/Colliders.h>
#include <v2f.h>

namespace phis2D
{
	class Collision
	{
	public:
		Collision() = default;
		~Collision() = default;

		static bool IntersectCircles(collider::CircleCollider* circleA, collider::CircleCollider* circleB, v2f& normal, float& depth)
		{
			normal = v2f();
			depth = 0.f;

			v2f distVec = circleB->GetPosition() - circleA->GetPosition();// вектор направлений из A в B тоесть куда нужно сдвинуть B при коллизии
			float distance = v2f::Length(distVec);
			float radii = circleA->GetRadius() + circleB->GetRadius();

			if (distance >= radii)
				return false;

			depth = radii - distance;
			normal = v2f::Normalize(distVec);
			return true;
		}

	private:

	};
}