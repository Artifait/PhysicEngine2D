#pragma once
#include <Utility/utilityDrawPrimetive.h>
#include <EnginePhis2D/Shapes/baseBady.h>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
namespace utility
{
	namespace draw
	{
		void DrawCollider(sf::RenderWindow& win, phis2D::collider::VirtualCollider* collider,
			bool filled, bool boundary, const sf::Color& collOutline, const sf::Color& collFill, float pxLine);
		void DrawBady(sf::RenderWindow& win, phis2D::BaseBady2D* bady, bool filled, bool boundary, 
			bool possibilityBoundary, const sf::Color& collOutline, const sf::Color& collFill, float pxLine);
	}

}