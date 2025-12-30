#include "Coin.h"

Coin::Coin(float x, float y)
{
	// Load Texture
	if (!texture.loadFromFile("coin.png"))
	{
	std::cout << "Error loading coin.png" << std::endl;
	}

	sprite.setTexture(texture);

	// Set Scale
	sprite.setScale(0.1f, 0.1f);

	// Centre Origin
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	// Set Position
	sprite.setPosition(x, y);
}

void Coin::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

bool Coin::isClicked(sf::Vector2f mousePos)
{
	return sprite.getGlobalBounds().contains(mousePos);
}

void Coin::shrink()
{
	sprite.setScale(0.09f, 0.09f);
}

void Coin::resetScale()
{
	sprite.setScale(0.1f, 0.1f);
}