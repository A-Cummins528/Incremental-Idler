#include "Cafe.h"

Cafe::Cafe(float x, float y, const sf::Texture& texture)
	: Building(x, y, texture, 1000, 10)
{

}

std::string Cafe::getClassName() const {
	return "Cafe";
}
