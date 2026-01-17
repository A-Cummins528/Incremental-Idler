#include "SaveSystem.h"
#include <fstream>
#include <iostream>
#include <string>

void saveGame(long long score, int cafesOwned, long long cafeCost)
{
	// Open file for writing output

	std::ofstream outFile("assets/data/save.txt", std::ios::trunc);

	if (outFile.is_open())
	{
		outFile << "Coins: " << score << std::endl; // Write the label and the score
		outFile << "Cafes: " << cafesOwned << std::endl;
		outFile << "CafeCost: " << cafeCost << std::endl;

		outFile.close(); // Close when done

		std::cout << "Game Saved: " << score << std::endl;
		std::cout << "Cafes: " << cafesOwned << std::endl;
		std::cout << "CafeCost: " << cafeCost << std::endl;
	}
	else
	{
		std::cout << "Errir: Could not save game!" << std::endl;
	}
}

void loadGame(long long& score, int& cafesOwned, long long& cafeCost)
{
	// Open file for reading (input)
	std::ifstream inFile("assets/data/save.txt");
	std::string label; // A temporary bucket for the text "Coins:"

	// Reset variables
	score = 0;
	cafesOwned = 0;
	cafeCost = 1000;

	// Check if file exists
	if (inFile.is_open())
	{
		// "while" loop keeps reading words until the file ends
		while (inFile >> label)
		{
			if (label == "Coins:")
			{
				inFile >> score;
			}
			if (label == "Cafes:")
			{
				inFile >> cafesOwned;
			}
			else if (label == "CafeCost:")
			{
				inFile >> cafeCost;
			}
		}

		inFile.close();
		std::cout << "Game Loaded -> Score: " << score << ", Cafes: " << cafesOwned << std::endl;
	}
	else
	{
		std::cout << "No save file found. Starting new game." << std::endl;
	}
}