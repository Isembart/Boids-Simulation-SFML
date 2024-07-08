#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class gameObject;

using gameObjectPtr = std::shared_ptr<gameObject>;

class gameObject
{
protected:
    sf::Vector2f position;
    float hitboxRadius = 2.0f;

public:
    gameObject() = default;
    virtual ~gameObject() = default;

    virtual void draw(sf::RenderWindow &window);
    virtual void update();

    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f &position);

    void setHitboxRadius(float range);
    float getHitboxRadius() const;

    bool intersects(gameObjectPtr other) const;
};
