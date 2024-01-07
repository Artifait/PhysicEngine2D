#include <Application.h>

int main()
{
<<<<<<< HEAD
    Application app;
    app.run();

=======
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    //window.setFramerateLimit(20);
    phis2D::World2D wrld(window);
    sf::Clock clock;
    float DT;
    float fps = 0;
    while (window.isOpen())
    {
        DT = clock.restart().asSeconds();
        fps = 1.f / DT;
        window.setTitle(to_string(fps));
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
    
>>>>>>> e800194a525aa6fce5d2a2e7157a3c25ecdaa9c2
    return 0;
}



