#include "SaveSystem.h"
#include <fstream>
#include <iostream>
#include <string>

void saveGame(long long score, const std::vector<std::unique_ptr<Building>>& shop)
{
    std::ofstream outFile("assets/data/save.txt", std::ios::trunc);
    if (outFile.is_open())
    {
        outFile << "Score: " << score << std::endl;

        // Loop through the vector and save every building
        for (const auto& building : shop)
        {
            // Format: Name: Owned Cost
            outFile << building->getClassName() << ": "
                << building->getOwnedCount() << " "
                << building->getCost() << std::endl;
        }

        outFile.close();
        std::cout << "Game Saved!" << std::endl;
    }
}

void loadGame(long long& score, std::vector<std::unique_ptr<Building>>& shop)
{
    std::ifstream inFile("assets/data/save.txt");
    std::string label;

    if (inFile.is_open())
    {
        while (inFile >> label)
        {
            if (label == "Score:")
            {
                inFile >> score;
            }
            else
            {
                // It must be a building
                // 1. Remove the colon from the label (e.g., "Cafe:" -> "Cafe")
                std::string buildingName = label.substr(0, label.size() - 1);

                // 2. Find the building in the shop list
                for (auto& building : shop)
                {
                    if (building->getClassName() == buildingName)
                    {
                        int count;
                        long long cost;
                        // Read the next two numbers from the file
                        inFile >> count >> cost;

                        // Update the building
                        building->setOwnedCount(count);
                        building->setCost(cost);
                    }
                }
            }
        }
        inFile.close();
        std::cout << "Game Loaded!" << std::endl;
    }
}