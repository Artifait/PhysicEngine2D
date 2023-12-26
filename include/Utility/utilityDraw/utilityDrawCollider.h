#pragma once
#include <Utility/utilityDraw/utilityDrawPrimetive.h>
#include <Shapes/Colliders.h>

namespace utility
{
	namespace draw
	{
		void DrawCollider(sf::RenderWindow& win, phis2D::collider::VirtualCollider* collider, bool filled = true, bool boundary = false, const sf::Color& col = sf::Color(34, 109, 224))
		{
			if (collider == nullptr)
			{
				//std::cout << "bla\n";
				return;
			}
			if (collider->GetTypeCollider() == phis2D::collider::Box || collider->GetTypeCollider() == phis2D::collider::Polygon)
			{
				auto vertix = collider->GetTransformedVertices();
				auto index = collider->GetTriangles();
				filled ? DrawVertices(win, vertix.first, vertix.second, index.first, index.second, col) :
					DrawVerticesLine(win, vertix.first, vertix.second, index.first, index.second, col);
			}
			else if (collider->GetTypeCollider() == phis2D::collider::Circle)
			{
				float radius = static_cast<phis2D::collider::CircleCollider*>(collider)->GetRadius();
				filled ? DrawPoint(win, collider->GetPosition(), radius, col)
					: DrawCircLine(win, collider->GetPosition(), radius, col);
				DrawVector(win, v2f(cos(collider->GetRotation()) * radius, sin(collider->GetRotation()) * radius), collider->GetPosition());
			}

			boundary ? DrawBoxLine(win, collider->GetRectCollider(), sf::Color::White) : void();
		}
	}

}