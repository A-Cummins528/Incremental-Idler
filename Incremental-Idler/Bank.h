#pragma once
#include "Building.h"
class Bank : public Building
{
public:
	Bank(float x, float y, const sf::Texture& texture);

	std::string getClassName() const override;
};

