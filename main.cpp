#include <EnginePhis2D/worldPhis2D.h>

int main()
{
    srand((int)time(NULL));
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    //window.setFramerateLimit(144);
    phis2D::World2D wrld;
    sf::Clock clock;
    float DT;
    float fps = 0;
    phis2D::BaseBady2D* player;
    wrld.GetBadyByIndex(0, player);
    while (window.isOpen())
    {
        DT = clock.getElapsedTime().asSeconds();
        fps = 1.f / DT;
        window.setTitle(to_string(fps));
        clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //input step
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
            player->Rotate(-phis2D::PI * DT * 2.f);
        
        if (Keyboard::isKeyPressed(Keyboard::Right))
            player->Rotate(phis2D::PI * DT * 2.f);
        player->ApplyForce(offset);
        wrld.Step(DT);
        window.clear(sf::Color::Black);
        wrld.Render(window);
        window.display();
    }
    
    return 0;
}

