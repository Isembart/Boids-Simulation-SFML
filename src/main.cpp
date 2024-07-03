#include "quadTree.hpp"
#include "particle.hpp"
#include "vectorFunctions.hpp"
#include <iostream>
#include <random>

const float particleSize = 4;
const int quadTreeCapacity = 3;

void addInitialRandomPoints(const sf::RenderWindow &window, quadTreePtr mainQT, std::vector<particlePtr> &objects)
{
    if (!mainQT)
    {
        // TODO: Error case - add a log
        return;
    }
    std::random_device device;
    std::mt19937 rng(device());
    std::uniform_real_distribution<float> dist_x{0.0f, static_cast<float>(window.getSize().x)};
    std::uniform_real_distribution<float> dist_y{0.0f, static_cast<float>(window.getSize().y)};
    for (int i = 0; i < 200; i++)
    {
        particlePtr particle_obj = std::make_shared<particle>(sf::Vector2f{dist_x(rng), dist_y(rng)}, particleSize);
        mainQT->insert(particle_obj);
        objects.push_back(particle_obj);
    }
}

class FPS
{
    sf::Clock m_clock;
    sf::Time m_start_time;

public:
    FPS()
    {
        m_start_time = m_clock.getElapsedTime();
    }
    ~FPS()
    {
        sf::Time end_time = m_clock.getElapsedTime();
        float fps = 1.0f / (end_time.asSeconds() - m_start_time.asSeconds());
        std::cout << "FPS: " << fps << '\n';
    }
};

int main()
{
    bool drawQuadTree = true;

    sf::RenderWindow window{{1600, 900}, "Boids Simulation"};
    window.setFramerateLimit(144);

    std::vector<particlePtr> objects;
    quadTreePtr mainQT = std::make_shared<quadTree>(0.0f, 0.0f, window.getSize().x + 10.0f, window.getSize().y + 10.0f, quadTreeCapacity);
    addInitialRandomPoints(window, mainQT, objects);

    while (window.isOpen())
    {
        FPS fps_obj;

        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.scancode == sf::Keyboard::Scan::Q)
                {
                    drawQuadTree = !drawQuadTree;
                }
            }
        }

        // Insert new particle objects on mouse click
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i position = sf::Mouse::getPosition(window);
            particlePtr particle_object = std::make_shared<particle>(sf::Vector2f(position), particleSize);
            mainQT->insert(particle_object);
            objects.push_back(particle_object);
        }
        // Update
        mainQT = std::make_shared<quadTree>(0.0f, 0.0f, window.getSize().x + 10.0f, window.getSize().y + 10.0f, quadTreeCapacity);
        for (auto obj : objects)
        {
            mainQT->insert(obj);
        }

        // Draw
        window.clear();
        if (drawQuadTree)
        {
            mainQT->draw(window);
        }
        // Check for collisions
        for (particlePtr obj : objects)
        {
            std::vector<particlePtr> others;
            // mainQT->query(obj->getSeparationRect(),others);
            mainQT->query(obj->getSearchRect(), others);
            obj->separation(others);
            obj->alignment(others);
            obj->cohesion(others);
            obj->update();
        }

        for (auto obj : objects)
        {
            obj->draw(window);
        }
        // std::cout<<objects[1]->getPosition().x<<" Y: " << objects[1]->getPosition().y << std::endl;
        window.display();
    }
}
