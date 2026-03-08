#pragma once
#include <SFML/Graphics.hpp>

class Button
{
public: 	Button(float x, float y, const sf::Texture& texture);
	void draw(sf::RenderWindow& window);
	bool isClicked(sf::Vector2f mousePos);

	// Allows the switching of textures (e.g., for mute/unmute button)
	void setTexture(const sf::Texture& texture);

private:
	sf::Sprite sprite;
};

