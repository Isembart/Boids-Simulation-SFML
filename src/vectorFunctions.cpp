#include <SFML/Graphics.hpp>
#include "math.h"
#include "vectorFunctions.hpp"

float magnitude(sf::Vector2f vec) {
	return sqrt(vec.x*vec.x + vec.y*vec.y);
}
sf::Vector2f normalize(sf::Vector2f vec){
	float mag = magnitude(vec);
	if(mag==0){
		return sf::Vector2f(0,0);
	}
	return sf::Vector2f(vec.x/mag, vec.y/mag);
}
float distance(sf::Vector2f a, sf::Vector2f b){
	return sqrt((b.x-a.x)*(b.x-a.x) + (b.y - a.y)*(b.y - a.y));
}