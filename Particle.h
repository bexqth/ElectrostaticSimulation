#pragma once
#include <SFML/Graphics.hpp>

class Particle
{
private:
    float mass;
    int charge; // -1 / 1
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    sf::CircleShape shape;
    sf::CircleShape glowMiddle;
    sf::CircleShape glowOutside;

public:
    Particle(sf::Vector2f position, int charge);
    ~Particle();
    sf::Vector2f getPosition();
    int getCharge() const;
    void setParticleProperties();
    void update();
    void move();
    void checkForParticle(std::vector<Particle>& particles);
    float getDistanceBetweenAParticle(sf::Vector2f particlePosition);
    sf::Vector2f getForceByColoumbLaw(Particle& otherParticle);
    sf::Vector2f normalizeVector(sf::Vector2f vector);
    void drawGlow(sf::RenderWindow& window);
    void drawGlowOutside(sf::RenderWindow& window);
    void drawBody(sf::RenderWindow& window);


};

