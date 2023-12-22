#include <SFML/Graphics.hpp>
#include <Shapes/Colliders.h>
#include <vector>
#include <iostream>
#include <Utility/utilityDraw/utilityDrawCollider.h>
#include <Utility/utilityPhisic/collisionPhis2D.h>

using namespace sf;
using namespace std;
namespace cld = phis2D::collider;

int main()
{
    srand(3);
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    vector<phis2D::collider::VirtualCollider*> coll;
    for (int i = 0; i < 15; i++)
    {
        string outMsg;
        cld::VirtualCollider* newColl = nullptr;
        if (cld::CreateCircleCollider(v2f((float)(rand() % 1000), (float)(rand() % 1000)), (float)(rand() % 50), outMsg, newColl))
            coll.emplace_back(newColl);

        std::cout << outMsg;
    }
    window.setFramerateLimit(144);
    while (window.isOpen())
    {
        sf::Event event;
        v2f offset;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::A))
            offset.x += -2;
        if (Keyboard::isKeyPressed(Keyboard::D))
            offset.x += 2;
        if (Keyboard::isKeyPressed(Keyboard::W))
            offset.y += -2;
        if (Keyboard::isKeyPressed(Keyboard::S))
            offset.y += 2;
        coll[0]->Move(offset);
        for (int i = 0; i < coll.size() - 1; i++)
        {
            cld::VirtualCollider* colliderA = coll[i];
            for (int j = i + 1; j < coll.size(); j++)
            {
                cld::VirtualCollider* colliderB = coll[j];
                v2f normal;
                float depth;
                if (phis2D::Collision::IntersectCircles(
                    (cld::CircleCollider*)colliderA,
                    (cld::CircleCollider*)colliderB,
                    normal, depth))
                {
                    colliderA->Move(-normal * depth * 0.5f);
                    colliderB->Move(normal * depth * 0.5f);
                }
            }
        }
        {
            
        }
        window.clear();
        for (auto& c : coll)
        {
            utility::draw::DrawCollider(window, c, false, Color::Green);
        }
        window.display();
    }

    return 0;
}
