#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ANSI escape codes for styling
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"

// Function to generate a random number within a specified range
int generateRandomNumber(int maxRange)
{
    return (rand() % maxRange) + 1;
}

// Function to get user input and validate it
int getUserGuess(int maxRange)
{
    int guess;

    printf(YELLOW "Enter your guess: " RESET);

    // Input validation to ensure only integers within the range are accepted
    while (1)
    {
        if (scanf("%d", &guess) != 1)
        {
            printf(RED "Invalid input! Please enter a number between 1 and %d.\n" RESET, maxRange);
            while (getchar() != '\n') // Clear invalid input from buffer
                ;
        }
        else if (guess < 1 || guess > maxRange)
        {
            printf(RED "Out of range! Please enter a number between 1 and %d.\n" RESET, maxRange);
        }
        else
        {
            break; // Valid input received
        }
    }

    return guess;
}

// Function to provide feedback based on the guess
void provideFeedback(int guess, int targetNumber)
{
    if (guess > targetNumber)
    {
        printf(RED "Your guess is too high. Please try a smaller number.\n" RESET);
    }
    else if (guess < targetNumber)
    {
        printf(RED "Your guess is too low. Please try a larger number.\n" RESET);
    }
    else
    {
        printf(GREEN "Congratulations! You guessed the correct number %d!\n" RESET, targetNumber);
    }
}

// Function to get the maximum number of attempts based on difficulty level
int getMaxAttempts(char difficulty)
{
    switch (difficulty)
    {
    case 'E':
    case 'e':
        return 10; // Easy level has more attempts
    case 'M':
    case 'm':
        return 7; // Medium level has a standard number of attempts
    case 'H':
    case 'h':
        return 5; // Hard level has fewer attempts
    default:
        return 7; // Default to Medium attempts if invalid
    }
}

// Function to print a decorative header
void printHeader(const char *title)
{
    printf("\n" BLUE "=========================\n" RESET);
    printf(MAGENTA BOLD "%s\n" RESET, title);
    printf(BLUE "=========================\n" RESET);
}

int main()
{
    int targetNumber, guess, attempts, maxRange, maxAttempts;
    char difficulty, playAgain;

    // Initialize random number generator
    srand(time(0));

    do
    {
        attempts = 0; // Reset attempts for a new game round

        // Difficulty selection
        printHeader("Welcome to the Number Guessing Game!");
        printf("Choose a difficulty level:\n");
        printf(YELLOW "E - Easy (1 to 50, 10 attempts)\n" RESET);
        printf(YELLOW "M - Medium (1 to 100, 7 attempts)\n" RESET);
        printf(YELLOW "H - Hard (1 to 200, 5 attempts)\n" RESET);
        printf("Enter your choice: ");
        scanf(" %c", &difficulty);

        // Set the range based on difficulty
        switch (difficulty)
        {
        case 'E':
        case 'e':
            maxRange = 50;
            break;
        case 'M':
        case 'm':
            maxRange = 100;
            break;
        case 'H':
        case 'h':
            maxRange = 200;
            break;
        default:
            printf(RED "Invalid choice! Defaulting to Medium level (1 to 100, 7 attempts).\n" RESET);
            maxRange = 100;
        }

        // Set the maximum attempts based on difficulty
        maxAttempts = getMaxAttempts(difficulty);

        // Generate a random number within the chosen range
        targetNumber = generateRandomNumber(maxRange);

        printf("I have selected a number between 1 and %d. Try to guess it! You have %d attempts.\n", maxRange, maxAttempts);

        // Game loop
        while (attempts < maxAttempts)
        {
            guess = getUserGuess(maxRange);
            attempts++; // Increment attempt counter

            provideFeedback(guess, targetNumber);

            // Check if the guess is correct
            if (guess == targetNumber)
            {
                printf(GREEN "You guessed it in %d attempts!\n" RESET, attempts);
                break; // Exit the loop if the guess is correct
            }

            // Check if attempts have been exhausted
            if (attempts == maxAttempts)
            {
                printf(RED "Sorry, you've run out of attempts. The correct number was %d.\n" RESET, targetNumber);
            }
            else
            {
                printf("You have %d attempts remaining.\n", maxAttempts - attempts);
            }
        }

        // Ask if the player wants to play again
        printf("Would you like to play again? (Y/N): ");
        scanf(" %c", &playAgain);

    } while (playAgain == 'Y' || playAgain == 'y');

    printf(GREEN "Thank you for playing!\n" RESET);
    return 0;
}
