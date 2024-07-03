#include "particle.hpp"
#include "vectorFunctions.hpp"
#include <iostream>
#include <cmath>

const int borderSizeX = 1600;
const int borderSizeY = 900;
const float PI = 3.14159265359f;

particle::particle(const sf::Vector2f &position, float _size)
{
    setPosition(position);
    setHitboxRadius(_size);
    size = _size;

    if (!texture.loadFromFile("arrow.png"))
    {
        return;
    }

    textureLoaded = true;
    sprite.setTexture(texture);
    sprite.setOrigin(sprite.getTextureRect().width / 2.0f, sprite.getTextureRect().height / 2.0f);
    sprite.setScale(sf::Vector2f(0.05f, 0.05f));
    sprite.setColor(sf::Color(255, 255, 255, 200));
}

sf::FloatRect particle::getSearchRect() const
{
    return searchRect;
}

void particle::setSearchRect(const sf::FloatRect &radius)
{
    searchRect = radius;
}

sf::FloatRect particle::getSeparationRect() const
{
    return separationRect;
}

void particle::setSeparationRect(const sf::FloatRect &radius)
{
    separationRect = radius;
}

void particle::setVelocity(const sf::Vector2f &_velocity)
{
    velocity = _velocity;
}

sf::Vector2f particle::getVelocity() const
{
    return velocity;
}

void particle::draw(sf::RenderWindow &window)
{
    if (!textureLoaded)
    {
        sf::CircleShape circle;
        circle.setFillColor(sf::Color(255, 255, 255, 100));
        circle.setPosition(position);
        circle.setRadius(size);
        circle.setOrigin(sf::Vector2f(circle.getRadius(), circle.getRadius()));
        window.draw(circle);
    }
    else
    {
        sprite.setPosition(position);
        sprite.setRotation(std::atan2(velocity.y, velocity.x) * 180.0f / PI);
        window.draw(sprite);
    }
}

void particle::update()
{
    // limit max speed
    float magn = magnitude(velocity);
    if (magn > maxSpeed)
    {
        velocity.x = velocity.x / magn * maxSpeed;
        velocity.y = velocity.y / magn * maxSpeed;
    }
    // velocity = normalize(velocity)  * speed;
    position += velocity * speed;

    searchRect = sf::FloatRect(getPosition().x - searchRange, getPosition().y - searchRange, searchRange * 2, searchRange * 2);
    separationRect = sf::FloatRect(getPosition().x - separationRange, getPosition().y - separationRange, separationRange * 2, separationRange * 2);

    // wrap around the screen
    if (position.x < 0)
    {
        position.x = borderSizeX;
    }
    else if (position.x > borderSizeX)
    {
        position.x = 0;
    }

    if (position.y < 0)
    {
        position.y = borderSizeY;
    }
    else if (position.y > borderSizeY)
    {
        position.y = 0;
    }
}

void particle::separation(const std::vector<particlePtr> &objects)
{
    sf::Vector2f sumToAllNearBoids(0, 0);
    int validObjects = 0;
    for (auto obj : objects)
    {
        if (distance(position, obj->position) > separationRange || position == obj->position)
        {
            continue;
        }
        sumToAllNearBoids += getPosition() - obj->getPosition();
        validObjects++;
    }
    if (validObjects > 0)
    {
        velocity += normalize(sumToAllNearBoids) * separationWeigth;
    }
}
void particle::alignment(const std::vector<particlePtr> &objects)
{
    int validObjects = 0;
    sf::Vector2f averageVelocity(0, 0);
    for (auto obj : objects)
    {
        if (distance(position, obj->position) > searchRange || position == obj->position)
        {
            continue;
        }
        averageVelocity += obj->getVelocity();
        validObjects++;
    }
    if (validObjects > 0)
    {
        averageVelocity = sf::Vector2f(averageVelocity.x / validObjects, averageVelocity.y / validObjects);
        velocity += averageVelocity * alignmentWeight;
    }
}

void particle::cohesion(const std::vector<particlePtr> &objects)
{
    int validObjects = 0;
    sf::Vector2f averagePosition(0, 0);
    for (auto obj : objects)
    {
        if (distance(position, obj->position) < searchRange || position == obj->position)
        {
            continue;
        }
        averagePosition += obj->getPosition();
        validObjects++;
    }
    if (validObjects > 0)
    {
        averagePosition = sf::Vector2f(averagePosition.x / validObjects, averagePosition.y / validObjects);
        averagePosition = averagePosition - position;
        velocity += averagePosition * cohesionWeight;
    }
}
