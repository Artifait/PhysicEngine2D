#pragma once
#include <Utility/utilityDraw/utilityDrawPrimetive.h>
#include <Shapes/Colliders.h>

namespace utility
{
	namespace draw
	{
		void DrawCollider(sf::RenderWindow& win, phis2D::collider::VirtualCollider* collider, 
			bool filled = true, bool boundary = false, const sf::Color& col = sf::Color(34, 109, 224));
	}

}