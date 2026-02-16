#include "Particle.h"

Particle::Particle(sf::Vector2f position, int charge) : position(position), charge(charge)
{
    this->shape.setPosition(this->position);
    this->glowMiddle.setPosition(this->position);
    this->glowOutside.setPosition(this->position);
    this->charge = charge;
}

Particle::~Particle()
{
}

sf::Vector2f Particle::getPosition()
{
    return this->position;
}

void Particle::setParticleProperties()
{
    switch (this->charge)
    {
    case 1: //proton
        this->mass = 1836.f;
        this->shape.setRadius(10.f);
        this->glowMiddle.setRadius(this->shape.getRadius() * 2);
        this->glowOutside.setRadius(this->shape.getRadius() * 3);
        this->shape.setFillColor(sf::Color(255, 77, 86));
        this->glowMiddle.setFillColor(sf::Color(255, 77, 86, 50));
        this->glowOutside.setFillColor(sf::Color(255, 77, 86, 25));
        break;
    case -1: //electron
        this->mass = 1.f;
        this->shape.setRadius(3.f);
        this->glowMiddle.setRadius(this->shape.getRadius() * 2);
        this->glowOutside.setRadius(this->shape.getRadius() * 3);
        this->shape.setFillColor(sf::Color(33, 188, 255));
        this->glowMiddle.setFillColor(sf::Color(33, 188, 255, 50));
        this->glowOutside.setFillColor(sf::Color(33, 188, 255, 25));
        break;
    default:
        break;
    }
    this->glowMiddle.setOrigin({this->glowMiddle.getRadius(), this->glowMiddle.getRadius()});
    this->glowOutside.setOrigin({this->glowOutside.getRadius(), this->glowOutside.getRadius()});
    this->shape.setOrigin({this->shape.getRadius(), this->shape.getRadius()});
}

void Particle::update()
{
}

void Particle::drawGlow(sf::RenderWindow &window) {
    window.draw(this->glowMiddle);
}

void Particle::drawGlowOutside(sf::RenderWindow &window) {
    window.draw(this->glowOutside);
}

void Particle::drawBody(sf::RenderWindow &window) {
    window.draw(this->shape);
}
