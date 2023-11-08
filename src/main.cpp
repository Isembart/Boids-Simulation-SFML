#include <SFML/Graphics.hpp>
#include "typedefs.hpp"
#include "quadTree.hpp"
#include "gameObject.hpp"
#include "particle.hpp"
#include <iostream>
#include <math.h>
#include "vectorFunctions.hpp"

const float particleSize = 4;
const int quadTreeCapacity = 3;

void randomPoints(sf::RenderWindow &window, quadTreePtr mainQT, std::vector<particlePtr> &objects){
    // random initial points
    for (int i = 0; i < 500; i++)
    {
        sf::Vector2f vec(rand()%window.getSize().x,rand()%window.getSize().y);
        particlePtr go = std::make_shared<particle>(vec,particleSize);
        mainQT->insert(go);
        objects.push_back(go);
    }
}

int main()
{
    sf::Clock clock;
    sf::Time previousTime = clock.getElapsedTime();
    sf::Time currentTime;
    float fps;
    bool drawQuadTree = true;

    auto window = sf::RenderWindow{ { 1600, 900 }, "CMake SFML Project" };
    window.setFramerateLimit(144);

    std::vector<particlePtr> objects;    
    quadTreePtr mainQT = std::make_shared<quadTree>(0,0,window.getSize().x+10,window.getSize().y+10,quadTreeCapacity);
    randomPoints(window,mainQT,objects);
    
    while (window.isOpen())
    {
        //fps 
        currentTime = clock.getElapsedTime();
        fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds()); // the asSeconds returns a float
        std::cout << "fps =" << fps << std::endl; // flooring it will make the frame rate a rounded number
        previousTime = currentTime;

        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if(event.type == sf::Event::KeyPressed){
                if(event.key.scancode == sf::Keyboard::Scan::Q){
                    drawQuadTree = !drawQuadTree;
                }
            }
        }

        //insert new points on mouseClick
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            sf::Vector2 position = sf::Mouse::getPosition(window);
            particlePtr go = std::make_shared<particle>(sf::Vector2f(position),particleSize);
            mainQT->insert(go); 
            objects.push_back(go);
        }
/////////////////////////////////////////////////////Update////////////////////
        mainQT = std::make_shared<quadTree>(0,0,window.getSize().x+10 ,window.getSize().y+10,quadTreeCapacity);		
        for(auto obj : objects){
            mainQT->insert(obj);
        }
//////////////////////////////////////////////DRAW/////////////////////////////
        window.clear();
        if(drawQuadTree) mainQT->draw(window);
        ///////////////////////////////////////////Collision Check////////////////////////
        for(particlePtr obj : objects) {
            std::vector<particlePtr> others;
            mainQT->query(obj->getSeparationRect(),others);
			obj->separation(others);
            mainQT->query(obj->getSearchRect(), others);
            obj->alignment(others);
            obj->cohesion(others);

            obj->update();
        }

        //draw object in the objects vector
        for(auto obj : objects) {
            obj->draw(window);
        }
        // std::cout<<objects[1]->getPosition().x<<" Y: " << objects[1]->getPosition().y << std::endl;
        window.display();

    }
}
