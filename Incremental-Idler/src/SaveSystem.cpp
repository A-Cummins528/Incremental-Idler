#include "SaveSystem.h"
#include <fstream>
#include <iostream>
#include <string>

void saveGame(long long score, int cafesOwned, long long cafeCost, int minesOwned, long long mineCost)
{
	// Open file for writing output

	std::ofstream outFile("assets/data/save.txt", std::ios::trunc);

	if (outFile.is_open())
	{
		// Write the label and the score
		outFile << "Coins: " << score << std::endl;
		outFile << "Cafes: " << cafesOwned << std::endl;
		outFile << "CafeCost: " << cafeCost << std::endl;
		outFile << "Mines: " << minesOwned << std::endl;
		outFile.close(); // Close when done

		std::cout << "Game Saved: " << score << std::endl;
		std::cout << "Cafes: " << cafesOwned << std::endl;
		std::cout << "CafeCost: " << cafeCost << std::endl;
		std::cout << "Mines: " << minesOwned << std::endl;
	}
	else
	{
		std::cout << "Errir: Could not save game!" << std::endl;
	}
}

void loadGame(long long& score, int& cafesOwned, long long& cafeCost, int& minesOwned, long long& mineCost)
{
	// Open file for reading (input)
	std::ifstream inFile("assets/data/save.txt");
	std::string label; // A temporary bucket for the text "Coins:"

	// Reset variables
	score = 0;
	cafesOwned = 0;
	cafeCost = 1000;
	minesOwned = 0;
	mineCost = 10000;

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
			if (label == "CafeCost:")
			{
				inFile >> cafeCost;
			}
			if (label == "Mines:")
			{
				inFile >> minesOwned;
			}
			else if (label == "MineCost:")
			{
				inFile >> mineCost;
			}
		}

		inFile.close();
		std::cout << "Game Loaded -> Score: " << score << ", Cafes: " << cafesOwned << ", Mines: " << minesOwned << std::endl;
	}
	else
	{
		std::cout << "No save file found. Starting new game." << std::endl;
	}
}