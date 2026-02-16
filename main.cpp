#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    unsigned int winWidth = 1000;
    unsigned int winHeight = 600;
    auto window = sf::RenderWindow(sf::VideoMode({winWidth, winHeight}), "Electrostatic Simulation");
    window.setFramerateLimit(60);

    sf::CircleShape particle(20.f);
    particle.setFillColor(sf::Color::Blue);
    particle.setOrigin({20.f, 20.f});
    particle.setPosition({500.f, 400.f});

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        
        }

        window.clear(sf::Color(40, 44, 52));
        window.draw(particle);
        window.display();
    }

    return 0;
}