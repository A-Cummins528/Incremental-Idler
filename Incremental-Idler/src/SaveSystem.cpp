#include "SaveSystem.h"
#include <fstream>
#include <iostream>

void saveGame(long long score)
{
	// Open file for writing output

	std::ofstream outFile("assets/fonts/save.txt", std::ios::trunc);

	if (outFile.is_open())
	{
		outFile << "Coins: " << score << std::endl; // Write the label and the score

		// Placeholder commented out
		// outfile << "AutoClickers: " << autoClickerCount << std::endl;

		outFile.close(); // Close when done
		std::cout << "Game Saved: " << score << std::endl;
	}
	else
	{
		std::cout << "Errir: Could not save game!" << std::endl;
	}
}

long long loadGame()
{
	// Open file for reading (input)
	std::ifstream inFile("assets/fonts/save.txt");
	long long loadedScore = 0;
	std::string label; // A temporary bucket for the text "Coins:"

	// Check if file exists
	if (inFile.is_open())
	{
		inFile >> label;

		if (label == "Coins:")
		{
			inFile >> loadedScore;
		}

		// To do: loop for future keys (AutoClicker)

		inFile.close();
		std::cout << "Game Loaded: " << loadedScore << std::endl;
	}
	else
	{
		std::cout << "No save file found. Starting new game." << std::endl;
		return 0;
	}

	return loadedScore;
}