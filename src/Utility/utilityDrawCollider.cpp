#include <Utility/utilityDrawCollider.h>

namespace utility
{
	namespace draw
	{
		void DrawCollider(sf::RenderWindow& win, phis2D::collider::VirtualCollider* collider, 
			bool filled, bool boundary, const sf::Color& collOutline, const sf::Color& collFill, float pxLine)
		{
			if (collider == nullptr)
			{
				//std::cout << "bla\n";
				return;
			}
			if (collider->GetTypeCollider() == phis2D::collider::Box)
			{
				sf::RectangleShape boxDraw(static_cast<phis2D::collider::BoxCollider*>(collider)->GetSize());
				boxDraw.setOrigin(boxDraw.getSize() / 2.f);
				boxDraw.setPosition(collider->GetPosition());
				filled ? boxDraw.setFillColor(collFill) : boxDraw.setFillColor(sf::Color::Transparent);
				boxDraw.setOutlineColor(collOutline);
				boxDraw.setOutlineThickness(pxLine);
				boxDraw.setRotation(phis2D::ToDegrees(collider->GetRotation()));
				win.draw(boxDraw);
			}
			else if (collider->GetTypeCollider() == phis2D::collider::Polygon)
			{
				auto vertix = collider->GetTransformedVertices();

				sf::ConvexShape ponDraw(vertix.second);
				for (int i = 0; i < vertix.second;i++)
					ponDraw.setPoint(i, vertix.first[i]);
				ponDraw.setOrigin(vertix.first[vertix.second]);
				ponDraw.setPosition(collider->GetCenterPosition());
				filled ? ponDraw.setFillColor(collFill) : ponDraw.setFillColor(sf::Color::Transparent);
				ponDraw.setOutlineColor(collOutline);
				ponDraw.setOutlineThickness(pxLine);
				win.draw(ponDraw);
			}
			else if (collider->GetTypeCollider() == phis2D::collider::Circle)
			{
				
				float radius = static_cast<phis2D::collider::CircleCollider*>(collider)->GetRadius();
				sf::CircleShape circDraw(radius);
				circDraw.setOrigin(v2f(radius, radius));
				circDraw.setPosition(collider->GetPosition());
				filled ? circDraw.setFillColor(collFill) : circDraw.setFillColor(sf::Color::Transparent);
				circDraw.setOutlineColor(collOutline);
				circDraw.setOutlineThickness(pxLine);
				win.draw(circDraw);
				DrawVector(win, v2f(cos(collider->GetRotation()) * radius, sin(collider->GetRotation()) * radius), collider->GetPosition());
			}

			boundary ? DrawBoxLine(win, collider->GetRectCollider(), sf::Color::Red) : void();
		}
		void utility::draw::DrawBady(sf::RenderWindow& win, phis2D::BaseBady2D* bady, bool filled, 
			bool boundary, bool possibilityBoundary, const sf::Color& collOutline, const sf::Color& collFill, float pxLine)
		{
			DrawCollider(win, bady->ICollider, filled, boundary, collOutline, collFill, pxLine);
			possibilityBoundary ? DrawBoxLine(win, bady->GetRectPossibilityCollision(), sf::Color::White) : void();
		}
	}

}