#include <EnginePhis2D/worldPhis2D.h>

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    //window.setFramerateLimit(20);
    phis2D::World2D wrld(window);
    sf::Clock clock;
    float DT;
    float fps = 0;
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
        wrld.HandleEvent(DT);
        wrld.Step(DT);
        window.clear(sf::Color::Black);
        wrld.Render(false);
        window.display();
    }
    
    return 0;
}

