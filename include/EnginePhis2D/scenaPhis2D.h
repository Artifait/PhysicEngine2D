#pragma once
#include <EnginePhis2D/Shapes/baseBady.h>
#include <vector>


#include <Utility/collisionPhis2D.h>

#include <Utility/utilityDrawCollider.h>
#include <Utility/randCollider.h>
namespace phis2D
{
	class Scena
	{
	public:
		Scena(sf::RenderWindow& win) : win(win) {}
		~Scena()
        {
            for (auto& obj : bodies) delete obj;
        }
		void Step()
        {
            float DT = deltaClock.restart().asSeconds();
            for (int i = 0; i < bodies.size(); i++)
                if (!bodies[i]->isStatic) bodies[i]->Step(DT, Gravity);

            //Collision step
            for (int i = 0; i < (int)bodies.size() - 1; i++)
            {
                phis2D::collider::VirtualCollider* colliderA = bodies[i]->ICollider;
                bool staticA = bodies[i]->isStatic;
                for (int j = i + 1; j < bodies.size(); j++)
                {
                    phis2D::collider::VirtualCollider* colliderB = bodies[j]->ICollider;
                    bool staticB = bodies[j]->isStatic;
                    if (staticA && staticB) continue;
                    v2f normal;
                    float depth;
                    if (phis2D::Collision::IntersectColliders(
                        colliderA, colliderB, normal, depth))
                    {
                        if (staticA)
                            colliderB->Move(normal * depth);
                        else if (staticB)
                            colliderA->Move(-normal * depth);
                        else
                        {
                            colliderA->Move(-normal * depth * 0.5f);
                            colliderB->Move(normal * depth * 0.5f);
                        }

                        Collision::ResolverCollision(bodies[i], bodies[j], normal, depth);
                    }
                }
            }
        }
		void Render(bool debug)
        {
            for (int i = 0; i < bodies.size(); i++) utility::draw::DrawBady(win, bodies[i], true, debug, debug, fillAndOutline[i].second, fillAndOutline[i].first, -1);
        }
		void AddBady(BaseBady2D* obj)
        {
            bodies.push_back(obj);
            sf::Color fill(obj->isStatic ? sf::Color::Transparent : utility::getRandomColor());
            sf::Color OutLine(sf::Color::White);
            fillAndOutline.push_back({ fill , OutLine });
        }

	private:
		sf::RenderWindow& win;
		v2f Gravity = v2f(0, 100);
		std::vector<BaseBady2D*> bodies;
		std::vector<std::pair<sf::Color, sf::Color>> fillAndOutline;
		sf::Clock deltaClock;
	};

}