#pragma once
#include "gameObject.hpp"
#include <memory>

class particle;

using particlePtr = std::shared_ptr<particle>;

class particle : public gameObject
{
    float size;
    sf::FloatRect separationRect;
    sf::FloatRect searchRect;
    sf::Vector2f velocity;
    /// graphics
    sf::Sprite sprite;
    sf::Texture texture;
    bool textureLoaded = false;

    const float separationWeigth = 0.1f;
    const float alignmentWeight = 0.05f;
    const float cohesionWeight = 0.0003f;
    const float separationRange = 20.0f;
    const float searchRange = 60.0f;
    const float speed = 1.0f;
    const float maxSpeed = 1.0f;

public:
    particle(const sf::Vector2f &position, float size);
    ~particle() = default;

    void draw(sf::RenderWindow &window) override;
    void update() override;

    sf::FloatRect getSearchRect() const;
    void setSearchRect(const sf::FloatRect &radius);

    sf::FloatRect getSeparationRect() const;
    void setSeparationRect(const sf::FloatRect &radius);

    sf::Vector2f getVelocity() const;
    void setVelocity(const sf::Vector2f &velocity);

    void separation(const std::vector<particlePtr> &obj);
    void alignment(const std::vector<particlePtr> &obj);
    void cohesion(const std::vector<particlePtr> &obj);
};
