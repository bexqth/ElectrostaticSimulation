#pragma once
#include "Particle.h"

class Simulation
{
    private:
        std::vector<Particle> particles;
        float maxWidth;
        float maxHeight;
    public:
        Simulation(float maxWidth, float maxHeight);
        ~Simulation();
        void update();
        void draw(sf::RenderWindow &window);
        void createParticles();
        sf::Vector2f generateRandomPosition();
};

