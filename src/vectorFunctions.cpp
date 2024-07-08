#include "vectorFunctions.hpp"
#include <cmath>

float magnitude(const sf::Vector2f &vec)
{
	return std::sqrt(std::pow(vec.x, 2.0f) + std::pow(vec.y, 2.0f));
}

sf::Vector2f normalize(const sf::Vector2f &vec)
{
	float mag = magnitude(vec);
	if (mag == 0.0f)
	{
		return sf::Vector2f(0.0f, 0.0f);
	}
	return vec / mag;
}

float distance(const sf::Vector2f &a, const sf::Vector2f &b)
{
	return magnitude(b - a);
}