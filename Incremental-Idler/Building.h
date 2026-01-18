#pragma once
#include <SFML/Graphics.hpp>
class Building
{
public:
	// Constructor
	Building(float x, float y, const sf::Texture& texture, long long baseCost, int incomeAmt);

	// Virtual Destructor
	virtual ~Building() = default;

	// --- SHARED FUNCTIONS ---
	void draw(sf::RenderWindow& window);
	bool isClicked(sf::Vector2f mousePos);

	// Shop Logic
	void purchase();
	long long getCost();
	int getOwnedCount();
	long long getIncomePerSecond();

	// Load Logic
	void setOwnedCount(int count);
	void setCost(long long newCost);

	// Visuals
	void shrink();
	void resetScale();

protected:
	sf::Sprite sprite;

	long long cost;
	int ownedCount;
	int baseIncome;
	float increaseRate;

	// Helper to keep track of the original scale
	sf::Vector2f originalScale;
};

