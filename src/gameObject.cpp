#include "gameObject.hpp"
#include "vectorFunctions.hpp"
#include <cmath>

sf::Vector2f gameObject::getPosition() const
{
    return position;
}

void gameObject::draw(sf::RenderWindow & /*window*/)
{
}

void gameObject::update()
{
}

void gameObject::setPosition(const sf::Vector2f &pos)
{
    position = pos;
}

void gameObject::setHitboxRadius(float range)
{
    hitboxRadius = range;
}

float gameObject::getHitboxRadius() const
{
    return hitboxRadius;
}

bool gameObject::intersects(gameObjectPtr other) const
{
    return hitboxRadius * 2.0f >= distance(other->getPosition(), position);
}
