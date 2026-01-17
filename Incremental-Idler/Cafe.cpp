#include "Cafe.h"

Cafe::Cafe(float x, float y, const sf::Texture& textureInput)
{
	sprite.setTexture(textureInput);
	sprite.setScale(0.05f, 0.05f);

	// Centre Origin
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	sprite.setPosition(x, y);

	cost = 1000;
	ownedCount = 0;
	baseIncome = 10;
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

float Cafe::getIncreaseRate()
{
	return increaseRate;
}

void Cafe::purchase()
{
	ownedCount++;
	cost = (cost * getIncreaseRate());
}

long long Cafe::getCost()
{
	return cost;
}

int Cafe::getOwnedCount()
{
	return ownedCount;
}

int Cafe::getIncomePerSecond()
{
	return ownedCount * baseIncome;
}

void Cafe::setOwnedCount(int count)
{
	ownedCount = count;
}

void Cafe::setCost(long long newCost)
{
	cost = newCost;
}