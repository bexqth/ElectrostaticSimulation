#pragma once
#include <SFML/Graphics.hpp>

class Particle
{
private:
    float mass;
    int charge; // -1 / 1
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::CircleShape shape;
    sf::CircleShape glowMiddle;
    sf::CircleShape glowOutside;

public:
    Particle(sf::Vector2f position, int charge);
    ~Particle();
    sf::Vector2f getPosition();
    void setParticleProperties();
    void update();
    void drawGlow(sf::RenderWindow& window);
    void drawGlowOutside(sf::RenderWindow& window);
    void drawBody(sf::RenderWindow& window);
};

