#include <SFML/Graphics.hpp>
#include <iostream>
#include "Particle.h"

int main()
{
    unsigned int winWidth = 1000;
    unsigned int winHeight = 600;
    auto window = sf::RenderWindow(sf::VideoMode({winWidth, winHeight}), "Electrostatic Simulation");
    window.setFramerateLimit(60);

    Particle prot({500.f, 400.f}, 1);
    Particle el({550.f, 400.f}, -1);

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
        prot.setParticleProperties();
        prot.drawGlowOutside(window);
        prot.drawGlow(window);
        prot.drawBody(window);

        el.setParticleProperties();
        el.drawGlowOutside(window);
        el.drawGlow(window);
        el.drawBody(window);

        window.display();
    }

    return 0;
}