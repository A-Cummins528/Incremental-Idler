#include "Bank.h"

Bank::Bank(float x, float y, const sf::Texture& texture)
	: Building(x, y, texture, 100000, 1000)
{

}

std::string Bank::getClassName() const {
	return "Bank";
}