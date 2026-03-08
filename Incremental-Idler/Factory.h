#pragma once
#include "Building.h"
class Factory : public Building
{
public:
	Factory(float x, float y, const sf::Texture& texture);

	std::string getClassName() const override;
};
