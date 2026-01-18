#pragma once

// Saves the current score to a file
void saveGame(long long score, int cafesOwned, long long cafeCost, int minesOwned, long long mineCost);

// Loads the score from a file (returns 0 if no file exists)
// Pass references (&) so the function can change these variables directly
void loadGame(long long& score, int& cafesOwned, long long& cafeCost, int& minesOwned, long long& mineCost);