#include <SFML/Graphics.hpp>
#include <iostream>
#include "Particle.h"

int main()
{
    unsigned int winWidth = 1000;
    unsigned int winHeight = 600;
    auto window = sf::RenderWindow(sf::VideoMode({winWidth, winHeight}), "Electrostatic Simulation");
    window.setFramerateLimit(60);

    Particle prot({50.f, 40.f}, 1);
    Particle el({55.f, 45.f}, -1);
    std::vector<Particle> particles = {prot, el};

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

        for (auto& p : particles) {
            p.checkForParticle(particles);
        }
        for (auto& p : particles) {
            p.move();
        }

        for (auto& p : particles) {
            p.drawGlowOutside(window);
            p.drawGlow(window);
            p.drawBody(window);
        }

        window.display();
    }

    return 0;
}