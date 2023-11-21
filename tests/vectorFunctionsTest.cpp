#include <gtest/gtest.h>
#include "vectorFunctions.hpp"

TEST(vectorFunctionsTest, magnitude) {
    sf::Vector2f vec(3,4);
    EXPECT_EQ(magnitude(vec), 5);
}

TEST(vectorFunctionsTest, normalize) {
    sf::Vector2f vec(3,4);
    EXPECT_EQ(normalize(vec), sf::Vector2f(0.6,0.8));
}

TEST(vectorFunctionsTest, distance) {
    sf::Vector2f a(0,0);
    sf::Vector2f b(3,4);
    EXPECT_EQ(distance(a,b), 5);
}