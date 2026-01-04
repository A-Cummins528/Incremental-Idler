#pragma once

// Saves the current score to a file
void saveGame(long long score, int cafesOwned);

// Loads the score from a file (returns 0 if no file exists)
// Pass references (&) so the function can change these variables directly
void loadGame(long long& score, int& cafesOwned);