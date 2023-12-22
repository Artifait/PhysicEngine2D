#pragma once
#include <Shapes/Colliders/typeCollider.h>
#include <SFML/Graphics/Rect.hpp>
#include <v2f.h>
#include <string>
#include <new>

namespace phis2D
{
	namespace collider
	{
		class VirtualCollider
		{
		public:
			VirtualCollider() = default;
			~VirtualCollider() = default;

			//from v2f min to max
			virtual sf::FloatRect GetRectCollider() = 0;
			virtual phis2D::collider::typeCollider GetTypeCollider() = 0;
			virtual const v2f& GetPosition() = 0;

			virtual void Move(const v2f& offset) = 0;

		};
	}
}