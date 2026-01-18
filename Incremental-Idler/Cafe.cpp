#include "Cafe.h"

Cafe::Cafe(float x, float y, const sf::Texture& texture)
	: Building(x, y, texture, 1000, 10)
{
	originalScale = sf::Vector2f(0.05f, 0.05f);
}
