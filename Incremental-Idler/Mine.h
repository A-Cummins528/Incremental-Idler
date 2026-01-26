#pragma once
#include "Building.h"
class Mine : public Building
{
public:
	Mine(float x, float y, const sf::Texture& texture);

	std::string getClassName() const override;
};

