#pragma once
#include "gameObject.hpp"

class particle : public gameObject
{
private:
    float size;
    sf::FloatRect separationRect;
    sf::FloatRect searchRect;
    sf::Vector2f velocity; 
    float speed=1;
    float maxSpeed=1;

    bool textureLoaded = false;
public:
    float separationWeigth = 0.1;
    float alignmentWeight = 0.05;
    float cohesionWeight = 0.0003;

    float separationRange = 20;
    float searchRange = 60;
    
    particle(sf::Vector2f position, float size);
    ~particle();

    sf::FloatRect getSearchRect() const;
    void setSearchRect(const sf::FloatRect& radius);
    sf::FloatRect getSeparationRect() const;
    void setSeparationRect(const sf::FloatRect& radius);
    
    void setVelocity(const sf::Vector2f& velocity);
    sf::Vector2f getVelocity() const;
    
    virtual void draw(sf::RenderWindow &window) override;
     void update() override;

    void separation(std::vector<particlePtr> &obj);
    void alignment(std::vector<particlePtr> &obj);
    void cohesion(std::vector<particlePtr> &obj);


    ///graphics
    sf::Sprite sprite;
    sf::Texture texture;
};


