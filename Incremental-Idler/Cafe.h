#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Cafe
{
public:

	// Constructor: Set up the Cafe
	Cafe(float x, float y);

	// Method to draw the Cafe to the window
	void draw(sf::RenderWindow& window);

	// Method to check if clicked
	bool isClicked(sf::Vector2f mousePos);

	// Visual effect methods
	void shrink();
	void resetScale();

private:
	sf::Texture texture;
	sf::Sprite sprite;
};