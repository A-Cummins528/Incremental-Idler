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

private:
	sf::Sprite sprite;
	long long cost;
	int ownedCount;
	int baseIncome;
};