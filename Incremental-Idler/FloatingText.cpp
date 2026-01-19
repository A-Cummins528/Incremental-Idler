#include "FloatingText.h"

FloatingText::FloatingText(float x, float y, const std::string& text, const sf::Font& font)
	: lifeTime(0.0f), maxLifeTime(2.0f), speed(50.0f)
{
	textObj.setFont(font);
	textObj.setString(text);
	textObj.setCharacterSize(24);
	textObj.setFillColor(sf::Color::Black);
	textObj.setPosition(x, y);

	// Settings
	maxLifeTime = 1.0f; // seconds
	lifeTime = 0.0f;
	speed = 100.0f; // pixels per second
}

bool FloatingText::update(float dt)
{
	lifeTime += dt;

	// Check if dead
	if (lifeTime >= maxLifeTime)
		return false;

	// Move up
	textObj.move(0, -speed * dt);

	// Fade out
	// Calculate Alpha (Transparency). 255 = Solid, 0 = Invisible.
	// Ratio goes from 1.0 (start) to 0.0 (end)
	float ratio = 1.0f - (lifeTime / maxLifeTime);

	sf::Color c = textObj.getFillColor();
	c.a = static_cast<sf::Uint8>(255 * ratio); // Update Alpha
	textObj.setFillColor(c);

	return true; // still alive
}

void FloatingText::draw(sf::RenderWindow& window)
{
	window.draw(textObj);
}