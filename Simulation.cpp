#include "Simulation.h"
#include "Particle.h"
#include <iostream>
#include <random>

using namespace std;

Simulation::Simulation(float maxWidth, float maxHeight) : maxWidth(maxWidth), maxHeight(maxHeight)
{

}

Simulation::~Simulation()
{
}

void Simulation::update()
{
    for (auto& p : particles) {
        p.checkForParticle(particles);
    }
    
    for (auto& p : particles) {
        p.move(this->maxWidth, this->maxHeight);
    }
    
}

void Simulation::draw(sf::RenderWindow &window)
{
    for (auto& p : particles) {
        p.drawGlowOutside(window);
        p.drawGlow(window);
        p.drawBody(window);
        p.drawTail(window);
    }
}

void Simulation::createParticles()
{
    //this->particles.push_back(Particle(sf::Vector2f(this->maxWidth / 2, this->maxHeight / 2), 1));
    int count = 4;
    float widthStep = (this->maxWidth - 200) / (count - 1);
    for(int i = 0; i < count; i++) {
        this->particles.push_back(Particle(sf::Vector2f(i * widthStep + 100, this->maxHeight / 3), 1));
    }

    for(int i = 0; i < count; i++) {
        this->particles.push_back(Particle(sf::Vector2f(i * widthStep + 100, 2 * this->maxHeight / 3), 1));
    }


    for(int i = 0; i < 40; i++) {
        this->particles.push_back(Particle(this->generateRandomPosition(), -1));
    }
}


sf::Vector2f Simulation::generateRandomPosition()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrX(100, 900);
    uniform_int_distribution<> distrY(100, 500);
    float randomXPos = distrX(gen);
    float randomYPos = distrY(gen);
    cout << randomXPos << endl;
    cout << randomYPos << endl;
    return sf::Vector2f(randomXPos, randomYPos);
}
