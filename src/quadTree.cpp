#include "typedefs.hpp"
#include "quadTree.hpp"
#include "gameObject.hpp"
#include "particle.hpp"

#include <type_traits>

quadTree::quadTree()
{
    divided=false;
}

quadTree::quadTree(float x, float y, float a, float b,int _capacity)
{
    // rect.setSize(sf::Vector2f(x,y));
    boundary.left=x;
    boundary.top=y;
    boundary.width=a;
    boundary.height=b;
    //capacity
    capacity = _capacity;
    divided=false;
}

quadTree::~quadTree()
{
}

const sf::Vector2f quadTree::getPosition()
{
    return rect.getPosition();
}

sf::RectangleShape* quadTree::getRect()
{
    return &rect;
}

sf::FloatRect* quadTree::getBoundary()
{
    return &boundary;
}
void quadTree::draw(sf::RenderWindow &window)
{
    //construct a recntagle shape from sf::Rect
    rect.setSize(sf::Vector2f(boundary.width, boundary.height));
    rect.setPosition(sf::Vector2f(boundary.left,boundary.top));
    rect.setFillColor(sf::Color(0,0,0,0));
    rect.setOutlineColor(sf::Color(255,255,255,255));
    rect.setOutlineThickness(1); 
    window.draw(rect);
    // window.draw(rect);   
    if(divided){
        //draw the child quadTrees
        ne->draw(window);
        nw->draw(window);
        se->draw(window);
        sw->draw(window);
    }
}

void quadTree::insert(particlePtr object)
{
    if(!boundary.contains(object->getPosition())) {
        return;
    }
    if(objects.size() < capacity) {
        objects.push_back(object);
    } 
    else {
        if(divided==false) {
            subdivide();
        }
        //once the quadTree has subdivided it passes the object to its children
        nw->insert(object);
        sw->insert(object);
        ne->insert(object);
        se->insert(object);
    }
}

//subidives the quadtree 
void quadTree::subdivide()
{
    divided = true;
    //the quadtrees are named as the poles
    //eg: southwest = se
    nw = std::make_shared<quadTree>(boundary.left, boundary.top, boundary.width/2, boundary.height/2, capacity);
    sw = std::make_shared<quadTree>(boundary.left, boundary.top+boundary.height/2, boundary.width/2, boundary.height/2, capacity);
    ne = std::make_shared<quadTree>(boundary.left + boundary.width/2, boundary.top, boundary.width/2, boundary.height/2, capacity);
    se = std::make_shared<quadTree>(boundary.left + boundary.width/2, boundary.top+ boundary.height/2, boundary.width/2, boundary.height/2, capacity);
}

void quadTree::query(sf::FloatRect range, std::vector<particlePtr> &found)
{
    // static_assert(std::is_base_of<gameObject,T>::value, "T must be descendant of gameObject");
    if(range.left - range.width > boundary.left + boundary.width || range.left + range.width < boundary.left - boundary.width || range.top - range.height > boundary.top + boundary.height || range.top + range.height < boundary.top - boundary.height ) {
        return;
    }
    for (unsigned short i = 0; i < objects.size(); i++)
    {
        if(range.contains(objects[i]->getPosition())){
            found.push_back(objects[i]);
        }
    }

    if(divided){
        nw->query(range,found);
        sw->query(range,found);
        ne->query(range,found);
        se->query(range,found);
    }
}