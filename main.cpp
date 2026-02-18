#include <SFML/Graphics.hpp>
#include <iostream>
#include "Particle.h"

int main()
{
    unsigned int winWidth = 1000;
    unsigned int winHeight = 600;
    auto window = sf::RenderWindow(sf::VideoMode({winWidth, winHeight}), "Electrostatic Simulation");
    window.setFramerateLimit(60);

    std::vector<Particle> particles;
    for (int i = 0; i < 8; i++)
    {
        particles.push_back(Particle(1));
    }

    for (int i = 0; i < 100; i++)
    {
        particles.push_back(Particle(-1));
    }
    

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
            p.move(winWidth, winHeight);
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