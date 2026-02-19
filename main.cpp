#include <SFML/Graphics.hpp>
#include <iostream>
#include "Particle.h"
#include "Simulation.h"

int main()
{
    unsigned int winWidth = 1000;
    unsigned int winHeight = 600;
    auto window = sf::RenderWindow(sf::VideoMode({winWidth, winHeight}), "Electrostatic Simulation");
    window.setFramerateLimit(60);

    Simulation simulation(winWidth, winHeight);
    simulation.createParticles();
    

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        
        }

        simulation.update();
        window.clear(sf::Color(40, 44, 52));
        simulation.draw(window);
        window.display();
    }

    return 0;
}