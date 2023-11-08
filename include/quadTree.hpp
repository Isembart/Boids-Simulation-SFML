#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class gameObject;

class quadTree
{
private:
    // sf::Vector2f size;
    sf::RectangleShape rect;
    sf::FloatRect boundary;
    int capacity;
    std::vector<particlePtr> objects; 
    bool divided;

    //child quadTrees, remains NULL till division
    quadTreePtr nw;
    quadTreePtr ne;
    quadTreePtr sw;
    quadTreePtr se;
public:
    //used to make empty quadtree objects available in the parent quadtree before subdivision
    quadTree();
    // quadTree(sf::Vector2f size,int capacity);
    quadTree(float x,float y, float a, float b, int capacity);
    ~quadTree();

    void subdivide();
    void draw(sf::RenderWindow& window);
    void insert(particlePtr object);

    const sf::Vector2f getPosition();
    sf::FloatRect* getBoundary();
    sf::RectangleShape* getRect();

    
    /// @brief Finds other gameObjects in the specified range 
    /// @param range the rectangle within a search occurs
    /// @param found Found objectswill be returned in this array
    /// @return 
    void query(sf::FloatRect range,std::vector<particlePtr> &found);
};


