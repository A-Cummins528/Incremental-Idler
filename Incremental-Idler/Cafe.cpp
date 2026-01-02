#include "Cafe.h"

Cafe::Cafe(float x, float y)
{
	// Load Texture
	if (!texture.loadFromFile("assets/images/cafe.png"))
	{
		std::cout << "Error loading cafe.png" << std::endl;
	}

	sprite.setTexture(texture);

	// Set Scale
	sprite.setScale(0.05f, 0.05f);

	// Centre Origin
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	// Set Position
	sprite.setPosition(x, y);
}

void Cafe::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

bool Cafe::isClicked(sf::Vector2f mousePos)
{
	return sprite.getGlobalBounds().contains(mousePos);
}

void Cafe::shrink()
{
	sprite.setScale(0.04f, 0.04f);
}

void Cafe::resetScale()
{
	sprite.setScale(0.05f, 0.05f);
}