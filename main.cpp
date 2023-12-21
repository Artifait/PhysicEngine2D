#include <SFML/Graphics.hpp>
#include <Shapes/Colliders.h>
#include <vector>
#include <iostream>

using namespace sf;
using namespace std;
namespace cld = phis2D::collider;

int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    vector<phis2D::collider::VirtualCollider*> coll;
    for (int i = 0; i < 15; i++)
    {
        string outMsg;
        cld::VirtualCollider* newColl = nullptr;
        if (cld::CreateCircleCollider(v2f(rand(), rand()), rand() % 2000, outMsg, newColl))
            coll.push_back(newColl);
        
        std::cout << outMsg;
    }
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}