#include "Particle.h"
#include <iostream>
#include <random>

using namespace std;

Particle::Particle(int charge) : charge(charge)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrX(100, 900);
    uniform_int_distribution<> distrY(100, 500);
    float randomXPos = distrX(gen);
    float randomYPos = distrY(gen);
    cout << randomXPos << endl;
    cout << randomYPos << endl;
    this->position = sf::Vector2f(randomXPos, randomYPos);
    this->shape.setPosition(this->position);
    this->glowMiddle.setPosition(this->position);
    this->glowOutside.setPosition(this->position);
    this->acceleration = sf::Vector2f(0.,0.);
    this->velocity = {0,0};
    this->charge = charge;
    this->dt = 1.f;
    this->trailMaxSize = 40;
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
        //this->mass = 1.f;
        this->radius = 10.f;
        this->shape.setFillColor(sf::Color(255, 77, 86));
        this->glowMiddle.setFillColor(sf::Color(255, 77, 86, 50));
        this->glowOutside.setFillColor(sf::Color(255, 77, 86, 25));
        break;
    case -1: //electron
        this->mass = 1.f;
        this->radius = 3.f;
        this->shape.setFillColor(sf::Color(33, 188, 255));
        this->glowMiddle.setFillColor(sf::Color(33, 188, 255, 50));
        this->glowOutside.setFillColor(sf::Color(33, 188, 255, 25));
        break;
    default:
        break;
    }
    this->shape.setRadius(this->radius);
    this->glowMiddle.setRadius(this->radius * 2);
    this->glowOutside.setRadius(this->radius * 3);
    this->glowMiddle.setOrigin({this->glowMiddle.getRadius(), this->glowMiddle.getRadius()});
    this->glowOutside.setOrigin({this->glowOutside.getRadius(), this->glowOutside.getRadius()});
    this->shape.setOrigin({this->shape.getRadius(), this->shape.getRadius()});
}

void Particle::update()
{
}

void Particle::move(int maxWidth, int maxHeight)
{
    this->velocity += this->acceleration * this->dt;
    this->position += this->velocity * this->dt;

    this->trailPositions.push_back(this->position);
    if(this->trailPositions.size() > this->trailMaxSize) {
        this->trailPositions.pop_front();
    }

    //this->checkBoundries(maxWidth, maxHeight);
    this->shape.setPosition(this->position);
    this->glowMiddle.setPosition(this->position);
    this->glowOutside.setPosition(this->position);
    this->acceleration = sf::Vector2f(0.f, 0.f);
}

void Particle::checkBoundries(int maxWidth, int maxHeight)
{
    float step = 100.f;
    if (this->position.x + this->radius + step > maxWidth) {
        this->velocity.x *= -1;
        this->position.x = maxWidth - this->radius - step;

    } else if (this->position.x - this->radius - step < 0) {
        this->velocity.x *= -1;
        this->position.x = this->radius + step;
    }

    if (this->position.y + this->radius + step > maxHeight) {
        this->velocity.y *= -1;
       this->position.y = maxHeight - this->radius - step;

    } else if (this->position.y - this->radius - step < 0) {
         this->velocity.y *= -1;
        this->position.y = this->radius + step;
    }
}

void Particle::checkForParticle(std::vector<Particle>& particles)
{   
    for(auto& particle : particles) {
        if(this != &particle) {
            sf::Vector2f forceVector = this->getForceByColoumbLaw(particle);
            this->acceleration += forceVector / this->mass;
        }
    }
}

sf::Vector2f Particle::getForceByColoumbLaw(Particle &otherParticle)
{
    float k = 5000.f;
    float epsilon = 500.f;
    float distance = getDistanceBetweenAParticle(otherParticle.getPosition());
    sf::Vector2f directionVector = otherParticle.getPosition() - this->position;
    directionVector = this->normalizeVector(directionVector);
    float force = (-1) * k * (this->charge * otherParticle.getCharge()) / (distance * distance + epsilon);
    cout << force  << endl;
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

void Particle::drawTail(sf::RenderWindow &window)
{
    sf::VertexArray vertexArray(sf::PrimitiveType::LineStrip, this->trailPositions.size());

    auto color = this->glowMiddle.getFillColor();
    int opacity = 200 / this->trailPositions.size();
    for(int i = 0; i < trailPositions.size(); i++) {
        vertexArray[i].position = this->trailPositions[i];
        vertexArray[i].color = sf::Color(color.r, color.g, color.b, opacity * i);
        
    }
    
    window.draw(vertexArray); 
}
