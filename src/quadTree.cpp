#include "quadTree.hpp"

quadTree::quadTree(float x, float y, float a, float b, int capacity_)
    : boundary{x, y, a, b}, capacity{capacity_}
{
}

sf::Vector2f quadTree::getPosition() const
{
    return rect.getPosition();
}

/*
sf::RectangleShape* quadTree::getRect()
{
    return &rect;
}

sf::FloatRect* quadTree::getBoundary()
{
    return &boundary;
}
*/

void quadTree::draw(sf::RenderWindow &window)
{
    // construct a rectangle shape from sf::Rect
    rect.setSize(sf::Vector2f(boundary.width, boundary.height));
    rect.setPosition(sf::Vector2f(boundary.left, boundary.top));
    rect.setFillColor(sf::Color::Black);
    rect.setOutlineColor(sf::Color::White);
    rect.setOutlineThickness(1.0f);

    window.draw(rect);

    if (divided)
    {
        // draw the child quadTrees
        ne->draw(window);
        nw->draw(window);
        se->draw(window);
        sw->draw(window);
    }
}

void quadTree::insert(particlePtr object)
{
    if (!boundary.contains(object->getPosition()))
    {
        return;
    }
    if (objects.size() < capacity)
    {
        objects.push_back(object);
    }
    else
    {
        if (!divided)
        {
            subdivide();
        }
        // once the quadTree has subdivided it passes the object to its children
        nw->insert(object);
        sw->insert(object);
        ne->insert(object);
        se->insert(object);
    }
}

// subidives the quadtree
void quadTree::subdivide()
{
    divided = true;
    // the quadtrees are named as the poles
    // eg: southwest = se
    const float &l = boundary.left;
    const float &t = boundary.top;
    const float &w = boundary.width;
    const float &h = boundary.height;
    const float half_w = w / 2.0f;
    const float half_h = h / 2.0f;
    nw = std::make_shared<quadTree>(l, t, half_w, half_h, capacity);
    sw = std::make_shared<quadTree>(l, t + half_h, half_w, half_h, capacity);
    ne = std::make_shared<quadTree>(l + half_w, t, half_w, half_h, capacity);
    se = std::make_shared<quadTree>(l + half_w, t + half_h, half_w, half_h, capacity);
}

void quadTree::query(sf::FloatRect range, std::vector<particlePtr> &found)
{
    // static_assert(std::is_base_of<gameObject,T>::value, "T must be descendant of gameObject");
    if (range.left - range.width > boundary.left + boundary.width
        || range.left + range.width < boundary.left - boundary.width
        || range.top - range.height > boundary.top + boundary.height
        || range.top + range.height < boundary.top - boundary.height)
    {
        return;
    }
    // TODO: Use a for-each loop
    for (size_t i = 0; i < objects.size(); i++)
    {
        if (range.contains(objects[i]->getPosition()))
        {
            found.push_back(objects[i]);
        }
    }

    if (divided)
    {
        nw->query(range, found);
        sw->query(range, found);
        ne->query(range, found);
        se->query(range, found);
    }
}