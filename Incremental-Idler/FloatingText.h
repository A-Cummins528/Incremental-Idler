#pragma once
#include <SFML/Graphics.hpp>
#include <string>
class FloatingText
{
public:
	// Pass the font by reference
	FloatingText(float x, float y, const std::string& text, const sf::Font& font);

	// Returns false when text has faded out (so it can be deleted)
	bool update(float dt);

	void draw(sf::RenderWindow& window);

private:
	sf::Text textObj;
	float lifeTime;
	float maxLifeTime;
	float speed;
};

