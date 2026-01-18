#include "Mine.h"

Mine::Mine(float x, float y, const sf::Texture& texture)
	: Building(x, y, texture, 10000, 100)
{
	originalScale = sf::Vector2f(0.3f, 0.3f);
}