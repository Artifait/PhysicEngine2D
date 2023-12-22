#pragma once
#include <Utility/utilityDraw/utilityDrawPrimetive.h>
#include <Shapes/Colliders.h>

namespace utility
{
	namespace draw
	{
		void DrawCollider(sf::RenderWindow& win, phis2D::collider::VirtualCollider* collider, bool filled = true, const sf::Color& col = sf::Color(rand() % 255, rand() % 255, rand() % 255))
		{
			if (collider == nullptr)
			{
				//std::cout << "bla\n";
				return;
			}

			switch (collider->GetTypeCollider())
			{
			case phis2D::collider::Box:
				filled ? DrawBox(win, collider->GetPosition(), static_cast<phis2D::collider::BoxCollider*>(collider)->GetSize(), col)
					: DrawBoxLine(win, collider->GetPosition(), static_cast<phis2D::collider::BoxCollider*>(collider)->GetSize(), col);
				break;
			case phis2D::collider::Circle:
				filled ? DrawPoint(win, collider->GetPosition(), static_cast<phis2D::collider::CircleCollider*>(collider)->GetRadius(), col)
					: DrawCircLine(win, collider->GetPosition(), static_cast<phis2D::collider::CircleCollider*>(collider)->GetRadius(), col);
				break;
			default:
				break;
			}
		}
	}

}