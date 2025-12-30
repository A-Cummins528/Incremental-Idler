#pragma once

// Saves the current score to a file
void saveGame(long long score);

// Loads the score from a file (returns 0 if no file exists)
long long loadGame();