#pragma once
#include <SFML/Graphics.hpp>
#include <deque>

class Particle
{
private:
    float mass;
    int charge; // -1 / 1
    float positionX;
    float positionY;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float radius;
    float dt;
    sf::CircleShape shape;
    sf::CircleShape glowMiddle;
    sf::CircleShape glowOutside;

    sf::Vector2f old_a;
    sf::Vector2f new_a;

    std::deque<sf::Vector2f> trailPositions;
    int trailMaxSize;

public:
    Particle(sf::Vector2f position, int charge);
    ~Particle();
    sf::Vector2f getPosition();
    int getCharge() const;
    void setParticleProperties();
    void update();
    void move(int maxWidth, int maxHeight);
    void checkBoundries(int maxWidth, int maxHeight);
    void checkForParticle(std::vector<Particle>& particles);
    float getDistanceBetweenAParticle(sf::Vector2f particlePosition);
    sf::Vector2f getForceByColoumbLaw(Particle& otherParticle);
    sf::Vector2f normalizeVector(sf::Vector2f vector);
    void drawGlow(sf::RenderWindow& window);
    void drawGlowOutside(sf::RenderWindow& window);
    void drawBody(sf::RenderWindow& window);
    void drawTail(sf::RenderWindow& window);
    void setAcceleration(sf::Vector2f newA);
    void setOldAcceleration(sf::Vector2f oldA);
    sf::Vector2f getAcceleration();
    void movePosition();
    void moveVelocity();


};

