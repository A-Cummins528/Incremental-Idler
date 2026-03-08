#include "Factory.h"
Factory::Factory(float x, float y, const sf::Texture& texture)
	: Building(x, y, texture, 1000000, 10000)
{
}

std::string Factory::getClassName() const {
	return "Factory";
}
