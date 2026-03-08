#include "Building.h"
#include <iostream>
#include <string>

Building::Building(float x, float y, const sf::Texture& texture, long long baseCost, int incomeAmt)
{
	sprite.setTexture(texture);
	sprite.setPosition(x, y);

	// Default scale
	sprite.setScale(1.0f, 1.0f);
	originalScale = sf::Vector2f(1.0f, 1.0f);

	// Centre Origin
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	// Stats
	cost = baseCost;
	baseIncome = incomeAmt;
	ownedCount = 0;
	increaseRate = 1.15f; // 15% increase rate
}



void Building::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

bool Building::isClicked(sf::Vector2f mousePos)
{
	return sprite.getGlobalBounds().contains(mousePos);
}

void Building::purchase()
{
	ownedCount++;
	cost = (cost * increaseRate);
	shrink();
	std::cout << getClassName() << " Purchased!" << std::endl;
}

long long Building::getCost()
{
	return cost;
}

void Building::setCost(long long newCost)
{
	cost = newCost;
}

int Building::getOwnedCount()
{
	return ownedCount;
}

long long Building::getIncomePerSecond()
{
	return (long long)ownedCount * baseIncome;
}

void Building::setOwnedCount(int count)
{
	ownedCount = count;
}

void Building::shrink()
{
	// Shrink to 90% of original scale
	sprite.setScale(originalScale.x * 0.9f, originalScale.y * 0.9f);
}

void Building::resetScale()
{
	sprite.setScale(originalScale);
}

std::string Building::getClassName() const {
	return "Building";
}

sf::Vector2f Building::getSpritePosition() const
{
	return sprite.getPosition();
}

int Building::getBaseIncome() const
{
	return baseIncome;
}