#include <Utility/utilityDraw/utilityDrawCollider.h>

namespace utility
{
	namespace draw
	{
		void DrawCollider(sf::RenderWindow& win, phis2D::collider::VirtualCollider* collider, bool filled, bool boundary, const sf::Color& col)
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

			boundary ? DrawBoxLine(win, collider->GetRectCollider(), sf::Color::Red) : void();
		}
		void utility::draw::DrawBady(sf::RenderWindow& win, phis2D::BaseBady2D* bady, bool filled, bool boundary, bool possibilityBoundary, const sf::Color& col)
		{
			DrawCollider(win, bady->ICollider, filled, boundary, col);
			possibilityBoundary ? DrawBoxLine(win, bady->GetRectPossibilityCollision(), sf::Color::White) : void();
		}
	}

}