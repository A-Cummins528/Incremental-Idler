#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Cafe
{
public:
	Cafe(float x, float y, const sf::Texture& texture);

	void draw(sf::RenderWindow& window);
	bool isClicked(sf::Vector2f mousePos);
	void shrink();
	void resetScale();

	void purchase();
	long long getCost();
	int getOwnedCount();
	int getIncomePerSecond();
	void setOwnedCount(int count);
	void setCost(long long newCost);
	float getIncreaseRate();

private:
	sf::Sprite sprite;
	long long cost;
	int ownedCount;
	int baseIncome;
	float increaseRate = 1.15f; // 15% increase rate
};