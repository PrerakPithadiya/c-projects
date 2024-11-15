/**
 * @file kaun_banega_crorepati.c
 * @brief A console-based implementation of the popular quiz game "Kaun Banega Crorepati" (Who Wants to Be a Millionaire?)
 *
 * This program implements a quiz game where players answer questions to win virtual money.
 * Features include multiple-choice questions, lifelines, time limits, and colorful console output.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>   // For getch()
#include <windows.h> // For Sleep()

/* Game Configuration Constants */
#define NUM_QUESTIONS 10     // Total number of questions in the game
#define TIME_LIMIT 10        // Time limit in seconds for each question
#define MAX_LIFELINES 5      // Maximum number of lifelines available
#define TOTAL_PRIZE 21100000 // Total prize money in Rupees (2.11 Crore)

/* ANSI Color Code Definitions for Enhanced Visual Output */
#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[1;91m"        // Bright Red
#define COLOR_GREEN "\033[1;92m"      // Bright Green
#define COLOR_YELLOW "\033[1;93m"     // Bright Yellow
#define COLOR_BLUE "\033[1;94m"       // Bright Blue
#define COLOR_MAGENTA "\033[1;95m"    // Bright Magenta
#define COLOR_CYAN "\033[1;96m"       // Bright Cyan
#define COLOR_WHITE "\033[1;97m"      // Bright White
#define COLOR_GOLD "\033[38;5;220m"   // Gold color
#define COLOR_ORANGE "\033[38;5;208m" // Orange color
#define COLOR_PINK "\033[38;5;205m"   // Pink color
#define COLOR_PURPLE "\033[38;5;129m" // Purple color
#define COLOR_TEAL "\033[38;5;51m"    // Teal color

/**
 * @struct Question
 * @brief Structure to store question data
 *
 * @var question The actual question text
 * @var options Array of four possible answers
 * @var correctAnswer The correct answer (a, b, c, or d)
 */
typedef struct
{
    char question[256];
    char options[4][50];
    char correctAnswer;
} Question;

/* Global Variables */
Question questions[NUM_QUESTIONS] = {
    {"What is the capital of India?", {"a) New Delhi", "b) Mumbai", "c) Kolkata", "d) Chennai"}, 'a'},
    {"Which planet is known as the Red Planet?", {"a) Earth", "b) Mars", "c) Jupiter", "d) Saturn"}, 'b'},
    {"What is the largest ocean on Earth?", {"a) Atlantic Ocean", "b) Indian Ocean", "c) Arctic Ocean", "d) Pacific Ocean"}, 'd'},
    {"Who wrote 'Hamlet'?", {"a) Mark Twain", "b) Leo Tolstoy", "c) William Shakespeare", "d) Charles Dickens"}, 'c'},
    {"What is the hardest natural substance on Earth?", {"a) Gold", "b) Iron", "c) Diamond", "d) Sapphire"}, 'c'},
    {"In which year did the Titanic sink?", {"a) 1905", "b) 1912", "c) 1915", "d) 1920"}, 'b'},
    {"Which gas do plants absorb from the atmosphere?", {"a) Oxygen", "b) Carbon Dioxide", "c) Nitrogen", "d) Hydrogen"}, 'b'},
    {"Who painted the Mona Lisa?", {"a) Vincent Van Gogh", "b) Pablo Picasso", "c) Leonardo da Vinci", "d) Claude Monet"}, 'c'},
    {"What is the smallest country in the world?", {"a) Monaco", "b) Vatican City", "c) San Marino", "d) Nauru"}, 'b'},
    {"What is the chemical symbol for water?", {"a) O2", "b) CO2", "c) H2O", "d) NaCl"}, 'c'},
};

int questionPrizes[NUM_QUESTIONS] = {100000, 200000, 300000, 500000, 1000000, 1500000, 2000000, 2500000, 3000000, 10000000};
int totalLifelinesUsed = 0;

/**
 * @brief Displays the game title and prize structure
 *
 * Clears the screen and shows the welcome message along with the prize money
 * for each question level.
 */
void displayTitle()
{
    system("cls");
    printf("%s", COLOR_GOLD);
    printf("Welcome to Kaun Banega Crorepati!\n");
    printf("===================================\n");
    printf("%s", COLOR_ORANGE);
    printf("Prize Structure:\n");
    for (int i = 0; i < NUM_QUESTIONS; i++)
    {
        printf("%sQuestion %d: Rupees %d\n", COLOR_TEAL, i + 1, questionPrizes[i]);
    }
    printf("%sTotal Prize: Rupees %d\n\n", COLOR_GREEN, TOTAL_PRIZE);
    printf("%s", COLOR_RESET);
}

/**
 * @brief Implements the 50-50 lifeline functionality
 *
 * @param questionIndex Index of the current question
 *
 * Displays only two options: the correct answer and one random wrong answer
 */
void display50_50Options(int questionIndex)
{
    char correctAnswer = questions[questionIndex].correctAnswer;
    int shownCorrect = 0, shownIncorrect = 0;
    printf("\n%s50-50 Lifeline used. Two options remaining:%s\n", COLOR_PINK, COLOR_RESET);
    for (int i = 0; i < 4; i++)
    {
        if (questions[questionIndex].options[i][0] == correctAnswer && !shownCorrect)
        {
            printf("%s%s%s\n", COLOR_PURPLE, questions[questionIndex].options[i], COLOR_RESET);
            shownCorrect = 1;
        }
        else if (questions[questionIndex].options[i][0] != correctAnswer && !shownIncorrect)
        {
            printf("%s%s%s\n", COLOR_PURPLE, questions[questionIndex].options[i], COLOR_RESET);
            shownIncorrect = 1;
        }

        if (shownCorrect && shownIncorrect)
            break;
    }
}

/**
 * @brief Handles the question asking and answer validation process
 *
 * @param questionIndex Index of the current question
 * @param lifelinesUsed Array tracking used lifelines
 * @return int Returns prize money won (-1 for timeout, 0 for wrong answer, 2 for skip)
 *
 * Displays the question, handles user input, manages lifelines, and validates answers
 */
int askQuestion(int questionIndex, int *lifelinesUsed)
{
    char answer;
    int timeElapsed = 0;
    char correctAnswer = questions[questionIndex].correctAnswer;
    printf("\n%sQuestion %d (Prize: Rupees %d):%s %s\n", COLOR_GOLD, questionIndex + 1, questionPrizes[questionIndex], COLOR_RESET, questions[questionIndex].question);
    for (int i = 0; i < 4; i++)
    {
        printf("%s%s%s\n", COLOR_TEAL, questions[questionIndex].options[i], COLOR_RESET);
    }
    printf("\n%sYou have %d seconds to answer. Press 'l' for lifeline, or enter your answer (a/b/c/d):%s\n", COLOR_PINK, TIME_LIMIT, COLOR_RESET);

    time_t startTime = time(NULL);

    while (timeElapsed < TIME_LIMIT)
    {
        if (_kbhit())
        {
            answer = _getch();
            if (answer == 'l' || answer == 'L')
            {
                if (totalLifelinesUsed < MAX_LIFELINES)
                {
                    // Check if a lifeline has already been used for this question
                    if (lifelinesUsed[questionIndex] == 0)
                    {
                        printf("\n%sLifeline options:%s\n", COLOR_PURPLE, COLOR_RESET);
                        printf("%s1. 50-50\n2. Skip Question%s\n", COLOR_ORANGE, COLOR_RESET);
                        char lifelineChoice = _getch();
                        if (lifelineChoice == '1')
                        {
                            lifelinesUsed[questionIndex] = 1; // Mark lifeline as used for this question
                            totalLifelinesUsed++;
                            display50_50Options(questionIndex);
                        }
                        else if (lifelineChoice == '2')
                        {
                            lifelinesUsed[questionIndex] = 1; // Mark lifeline as used for this question
                            totalLifelinesUsed++;
                            printf("\n%sYou skipped the question. No winnings from this question.%s\n", COLOR_ORANGE, COLOR_RESET);
                            return 2; // Question skipped
                        }
                        else
                        {
                            printf("%sInvalid lifeline option.%s\n", COLOR_RED, COLOR_RESET);
                        }
                    }
                    else
                    {
                        // Lifeline has already been used for this question
                        printf("%sOnly one lifeline is allowed per question.%s\n", COLOR_RED, COLOR_RESET);
                    }
                }
                else
                {
                    printf("\n%sNo lifelines remaining.%s\n", COLOR_RED, COLOR_RESET);
                }
            }
            else
            {
                break;
            }
        }
        timeElapsed = time(NULL) - startTime;
    }

    if (timeElapsed >= TIME_LIMIT)
    {
        printf("\n%sTime's up! You couldn't answer in time.%s\n", COLOR_RED, COLOR_RESET);
        return -1;
    }
    if (answer == correctAnswer)
    {
        printf("%sCorrect! You win Rupees %d!%s\n", COLOR_GREEN, questionPrizes[questionIndex], COLOR_RESET);
        return questionPrizes[questionIndex];
    }
    else
    {
        printf("%sWrong answer! The correct answer was %c.%s\n", COLOR_RED, correctAnswer, COLOR_RESET);
        return 0;
    }
}

/**
 * @brief Main game loop and program entry point
 *
 * @return int Returns 0 on successful program completion
 *
 * Initializes the game, manages the question sequence, tracks winnings,
 * and handles game termination conditions
 */
int main()
{
    system(""); // Enable ANSI escape sequences in Windows

    int totalWinnings = 0;
    int lifelinesUsed[NUM_QUESTIONS] = {0};

    displayTitle();

    for (int i = 0; i < NUM_QUESTIONS; i++)
    {
        int result = askQuestion(i, lifelinesUsed);
        if (result == -1)
        {
            printf("%sYou won a total of Rupees %d.%s\n", COLOR_GOLD, totalWinnings, COLOR_RESET);
            return 0;
        }
        else if (result == 0)
        {
            printf("%sYou won a total of Rupees %d.%s\n", COLOR_GOLD, totalWinnings, COLOR_RESET);
            return 0;
        }
        else if (result == 2)
        {
            continue;
        }
        else
        {
            totalWinnings += result;
        }
    }

    if (totalWinnings == TOTAL_PRIZE)
    {
        printf("%sCongratulations! You've answered all questions correctly!%s\n", COLOR_GREEN, COLOR_RESET);
    }
    else
    {
        printf("%sYou have not answered all questions correctly!%s\n", COLOR_RED, COLOR_RESET);
    }
    printf("%sYou won a total of Rupees %d.%s\n", COLOR_GOLD, totalWinnings, COLOR_RESET);
    return 0;
}
