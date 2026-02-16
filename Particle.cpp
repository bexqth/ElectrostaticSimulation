#include "Particle.h"
#include <iostream>

using namespace std;

Particle::Particle(sf::Vector2f position, int charge) : position(position), charge(charge)
{
    this->shape.setPosition(this->position);
    this->glowMiddle.setPosition(this->position);
    this->glowOutside.setPosition(this->position);
    this->acceleration = sf::Vector2f(0.,0.);
    this->charge = charge;
    this->setParticleProperties();
}

Particle::~Particle()
{
}

sf::Vector2f Particle::getPosition()
{
    return this->position;
}

int Particle::getCharge() const
{
    return this->charge;
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

void Particle::move()
{
    this->velocity += this->acceleration;
    this->velocity *= 0.99f;
    this->position += this->velocity;
    this->shape.setPosition(this->position);
    this->glowMiddle.setPosition(this->position);
    this->glowOutside.setPosition(this->position);
    this->acceleration = sf::Vector2f(0.f, 0.f);
}

void Particle::checkForParticle(std::vector<Particle>& particles)
{   
    for(auto& particle : particles) {
        if(this != &particle) {
            sf::Vector2f forceVector = this->getForceByColoumbLaw(particle);
            this->acceleration += forceVector / this->mass;
            cout << this->acceleration.x << " " << this->acceleration.y << endl;
        }
    }
}

sf::Vector2f Particle::getForceByColoumbLaw(Particle &otherParticle)
{
    float k = 50.f;
    float distance = getDistanceBetweenAParticle(otherParticle.getPosition());
    sf::Vector2f directionVector = otherParticle.getPosition() - this->position;
    directionVector = this->normalizeVector(directionVector);
    float force = k * (this->charge * otherParticle.getCharge()) / (distance * distance);
    return directionVector * force;
}

sf::Vector2f Particle::normalizeVector(sf::Vector2f vector)
{
    float vectorLength = sqrt((vector.x * vector.x) + (vector.y * vector.y));
    if(vectorLength != 0) {
        vector.x = vector.x / vectorLength;
        vector.y = vector.y / vectorLength;
    }
    return vector;
}

float Particle::getDistanceBetweenAParticle(sf::Vector2f particlePosition)
{
    float xDiff = this->position.x - particlePosition.x;
    float yDiff = this->position.y - particlePosition.y;

    float distance = sqrt((xDiff * xDiff) + (yDiff * yDiff));
    return distance;
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
