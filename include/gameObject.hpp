#pragma once
#include "SFML/Graphics.hpp"
#include "typedefs.hpp"

class gameObject
{
protected:
    sf::Vector2f position;
    float hitboxRadius = 2;
public:
    gameObject();
    ~gameObject();

    virtual sf::Vector2f getPosition(); 
    virtual void draw(sf::RenderWindow &window);
    virtual void update();
    virtual void setPosition(sf::Vector2f position); 

    void setHitboxRadius(float range); 
    float getHitboxRadius(); 
    bool intersects(gameObjectPtr other);
};
