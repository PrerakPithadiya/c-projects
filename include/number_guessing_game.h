#ifndef NUMBER_GUESSING_GAME_H
#define NUMBER_GUESSING_GAME_H

// Function prototypes
int generateRandomNumber(int maxRange);
int getUserGuess(int maxRange);
void provideFeedback(int guess, int targetNumber);
int getMaxAttempts(char difficulty);
void printHeader(const char *title);

#endif // NUMBER_GUESSING_GAME_H
