//test for gameObject.cpp
#include <SFML/Graphics.hpp>
#include <gtest/gtest.h>

#include "gameObject.hpp"

TEST(gameObjectTest, gettersAndSetters) {
    gameObject obj;
    obj.setPosition(sf::Vector2f(10,10));
    EXPECT_EQ(obj.getPosition(), sf::Vector2f(10,10));
    obj.setHitboxRadius(10);
    EXPECT_EQ(obj.getHitboxRadius(), 10);
}

TEST(gameObjectTest, collision) {
    gameObjectPtr obj1 = std::make_shared<gameObject>();
    gameObjectPtr obj2 = std::make_shared<gameObject>();
    obj1->setPosition(sf::Vector2f(10,10));
    obj2->setPosition(sf::Vector2f(10,10));
    obj1->setHitboxRadius(10);
    obj2->setHitboxRadius(10);
    EXPECT_EQ(obj1->intersects(obj2), true);
    obj2->setPosition(sf::Vector2f(100,100));
    EXPECT_EQ(obj1->intersects(obj2), false);
}

