#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Coin
{
public:

	// Constructor: Set up the coin
	Coin(float x, float y, const sf::Texture& texture);

	// Method to draw the coin to the window
	void draw(sf::RenderWindow& window);

	// Method to check if clicked
	bool isClicked(sf::Vector2f mousePos);

	// Visual effect methods
	void shrink();
	void resetScale();

private:
	sf::Sprite sprite;
};