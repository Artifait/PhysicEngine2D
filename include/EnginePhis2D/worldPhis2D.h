#pragma once
#include <SFML/Graphics.hpp>
#include <Shapes/Colliders.h>
#include <vector>
#include <iostream>
#include <Utility/utilityDraw/utilityDrawCollider.h>
#include <Utility/utilityPhisic/collisionPhis2D.h>

using namespace sf;
using namespace std;
namespace cld = phis2D::collider;

namespace phis2D
{
	class World2D
	{
	public:
		World2D()
		{
            for (int i = 0; i < 15; i++)
            {
                string outMsg;
                cld::VirtualCollider* newColl = nullptr;
                int type = rand() % 2;
                //type = 1;
                if (type == (int)phis2D::collider::Box)
                    if (cld::CreateBoxCollider(v2f((float)(rand() % 900 + 50), (float)(rand() % 900 + 50)), v2f(rand() % 25 + 25, rand() % 25 + 25), outMsg, newColl))
                        coll.emplace_back(newColl);
                if (type == (int)phis2D::collider::Circle)
                    if (cld::CreateCircleCollider(v2f((float)(rand() % 900 + 50), (float)(rand() % 900 + 50)), rand() % 25 + 25, outMsg, newColl))
                        coll.emplace_back(newColl);
                
                std::cout << outMsg;
            }
            string outMsg;
            cld::VirtualCollider* newColl = nullptr;
            v2f arr[] = {v2f(20, 20), v2f(100, 0), v2f(200, 200), v2f(100, 200)};
            cld::vecV2f virtsP(arr, 4);
            if (cld::CreatePolygonCollider(virtsP, outMsg, newColl))
                coll.emplace_back(newColl);
            coll[coll.size() - 1]->Move(v2f(100, 100));
            cout << outMsg;
            auto ind = coll[coll.size() - 1]->GetTriangles();
            for (int i = 0; i < ind.second; i++)
                cout << "[" + std::to_string(i) + "] = " + std::to_string(ind.first[i] ) << std::endl;
		}
		bool AddColliderBady(collider::VirtualCollider* collider, bool isStatic,
			float density, float mass, float restition, std::string& outMessage);

		bool AddCircleBady(const v2f& posCenter, float r, bool isStatic,
			float density, float mass, float restition, std::string& outMessage);

		bool AddBoxBady(const v2f& position, const v2f& size, bool isStatic,
			float density, float mass, float restition, std::string& outMessage);

        void Render(RenderWindow& win)
        {
            for (auto& c : coll)
                utility::draw::DrawCollider(win, c, false, false);
        }
		void Step(float DT)
		{
            v2f offset;
            if (Keyboard::isKeyPressed(Keyboard::A))
                offset.x += -300;
            if (Keyboard::isKeyPressed(Keyboard::D))
                offset.x += 300;
            if (Keyboard::isKeyPressed(Keyboard::W))
                offset.y += -300;
            if (Keyboard::isKeyPressed(Keyboard::S))
                offset.y += 300;

            if (Keyboard::isKeyPressed(Keyboard::Left))
                coll[coll.size() - 1]->Rotate(-phis2D::PI * DT * 2.f);
            if (Keyboard::isKeyPressed(Keyboard::Right))
                coll[coll.size() - 1]->Rotate(phis2D::PI * DT * 2.f);
            if (coll.size() >= 1)
                coll[coll.size() - 1]->Move(offset * DT);

            for (int i = 0; i < coll.size() - 1; i++)
            {
                cld::VirtualCollider* colliderA = coll[i];
                for (int j = i + 1; j < coll.size(); j++)
                {
                    cld::VirtualCollider* colliderB = coll[j];
                    v2f normal;
                    float depth;
                    if (phis2D::Collision::IntersectColliders(
                        colliderA, colliderB, normal, depth))
                    {
                        colliderA->Move(-normal * depth * 0.5f);
                        colliderB->Move(normal * depth * 0.5f);
                    }
                }
            }
		}
		~World2D()
		{
		}

	private:
        vector<phis2D::collider::VirtualCollider*> coll;
	};

}


