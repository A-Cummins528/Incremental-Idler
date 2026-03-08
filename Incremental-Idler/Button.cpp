#include "Button.h"

Button::Button(float x, float y, const sf::Texture& texture)
{
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
	// Centre Origin
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Button::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

bool Button::isClicked(sf::Vector2f mousePos)
{
	return sprite.getGlobalBounds().contains(mousePos);
}

void Button::setTexture(const sf::Texture& texture)
{
	sprite.setTexture(texture);
}
