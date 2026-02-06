#pragma once
#include <vector>
#include <memory>
#include "Building.h"

void saveGame(long long score, const std::vector<std::unique_ptr<Building>>& shop);
void loadGame(long long& score, std::vector<std::unique_ptr<Building>>& shop);