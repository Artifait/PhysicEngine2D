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
    srand((int)time(NULL));
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    //window.setFramerateLimit(144);
    vector<phis2D::collider::VirtualCollider*> coll;
    for (int i = 0; i < 15; i++)
    {
        string outMsg;
        cld::VirtualCollider* newColl = nullptr;
        int type = rand() % 2;
        if(type == (int)phis2D::collider::Box)
            if (cld::CreateBoxCollider(v2f((float)(rand() % 900 + 50), (float)(rand() % 900 + 50)), v2f(rand() % 75 + 25, rand() % 75 + 25), outMsg, newColl))
                coll.emplace_back(newColl);
        if(type == (int)phis2D::collider::Circle)
            if (cld::CreateCircleCollider(v2f((float)(rand() % 900 + 50), (float)(rand() % 900 + 50)), rand() % 25 + 25, outMsg, newColl))
                coll.emplace_back(newColl);
        std::cout << outMsg;
    }

  
    Clock clock;
    float DT;
    float fps = 0;

    while (window.isOpen())
    {
        DT = clock.getElapsedTime().asSeconds();
        fps = 1.f / DT;
        window.setTitle(to_string(fps));
        clock.restart();
        sf::Event event;
        v2f offset;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //for (auto& c : coll)  c->Rotate(phis2D::PI / 2.f * DT);
        
        if (Keyboard::isKeyPressed(Keyboard::A))
            offset.x += -300;
        if (Keyboard::isKeyPressed(Keyboard::D))
            offset.x += 300;
        if (Keyboard::isKeyPressed(Keyboard::W))
            offset.y += -300;
        if (Keyboard::isKeyPressed(Keyboard::S))
            offset.y += 300;

        if (Keyboard::isKeyPressed(Keyboard::Left))
            coll[0]->Rotate(phis2D::PI * DT);
        if (Keyboard::isKeyPressed(Keyboard::Right))
            coll[0]->Rotate(-phis2D::PI * DT);
        if(coll.size() >= 1)
            coll[0]->Move(offset * DT);

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

        window.clear(Color::Black);
        for (auto& c : coll)
            utility::draw::DrawCollider(window, c, false);

        
        window.display();
    }
    
    return 0;
}

