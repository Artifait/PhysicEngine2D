#pragma once
#include <Utility/utilityDraw/utilityDrawPrimetive.h>
#include <Shapes/baseBady.h>

namespace utility
{
	namespace draw
	{
		void DrawCollider(sf::RenderWindow& win, phis2D::collider::VirtualCollider* collider,
			bool filled, bool boundary, const sf::Color& col);
		void DrawBady(sf::RenderWindow& win, phis2D::BaseBady2D* bady, bool filled, bool boundary, 
			bool possibilityBoundary, const sf::Color& col);
	}

}