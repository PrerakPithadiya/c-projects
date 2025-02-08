/*******************************************************************************
 * Tic Tac Toe Game Implementation
 *
 * A console-based Tic Tac Toe game featuring a player versus computer gameplay
 * with two difficulty levels: Human (Standard) and God (Impossible).
 *
 * Dependencies:
 * - stdio.h  : Standard input/output operations
 * - stdlib.h : Standard library functions (rand, srand)
 * - time.h   : Time functions for random seed
 *
 * Features:
 * - Colorful console interface using ANSI color codes
 * - Two difficulty levels
 * - Score tracking
 * - Minimax algorithm for unbeatable AI
 *
 * Usage:
 * 1. Compile: gcc tic_tac_toe.c -o tic_tac_toe
 * 2. Run: /tic_tac_toe
 * 3. Choose difficulty level (1 for Human, 2 for God)
 * 4. Enter moves using row and column numbers (1-3)
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 3

/* ANSI Color codes for enhanced visual experience */
#define RED "\x1b[38;5;196m"     // Bright red
#define GREEN "\x1b[38;5;46m"    // Neon green
#define YELLOW "\x1b[38;5;226m"  // Bright yellow
#define BLUE "\x1b[38;5;39m"     // Deep sky blue
#define MAGENTA "\x1b[38;5;201m" // Hot pink
#define CYAN "\x1b[38;5;51m"     // Bright cyan
#define RESET "\x1b[0m"

/* Global variables for game state */
int playerX_score = 0, computer_score = 0, draws = 0;
char board[SIZE][SIZE];

/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/

/* Board Management Functions */
void initialize_board(); // Initializes empty game board
void display_board();    // Displays current game state
void display_score();    // Shows current scores
void clear_screen();     // Clears console screen

/* Game Logic Functions */
int is_winner(char symbol);                                       // Checks if given symbol has won
int is_draw();                                                    // Checks if game is a draw
void player_move();                                               // Handles player's move input
void computer_move(int difficulty);                               // Manages computer's move based on difficulty
int minimax(char board[SIZE][SIZE], int depth, int isMaximizing); // AI algorithm
int check_available_moves();                                      // Checks for available moves
void play_game(int difficulty);                                   // Main game loop
int prompt_difficulty();                                          // Difficulty selection menu

/*******************************************************************************
 * Main Function
 *
 * Entry point of the program. Handles game initialization and replay logic.
 * Returns: 0 on successful execution
 ******************************************************************************/
int main()
{
    srand(time(0)); // Seed random number generator

    while (1)
    {
        int difficulty = prompt_difficulty();
        play_game(difficulty);

        // Ask to play again
        char play_again;
        printf(CYAN "\nPlay again? (y/n): " RESET);
        scanf(" %c", &play_again);
        if (play_again != 'y')
        {
            printf(GREEN "Thanks for playing!\n" RESET);
            break;
        }
    }
    return 0;
}

/*******************************************************************************
 * Difficulty Selection
 *
 * Prompts user to select game difficulty:
 * 1. Human (Standard) - Makes some strategic moves but can be beaten
 * 2. God (Impossible) - Uses minimax algorithm, cannot be beaten
 *
 * Returns: Selected difficulty level (1 or 2)
 ******************************************************************************/
int prompt_difficulty()
{
    int difficulty;
    while (1)
    {
        printf(MAGENTA "\nChoose Difficulty:\n" RESET);
        printf(CYAN "1) Human (Standard)\n2) God (Impossible to Win)\n> " RESET);
        if (scanf("%d", &difficulty) != 1 || (difficulty != 1 && difficulty != 2))
        {
            printf(RED "Invalid choice. Please enter 1 or 2.\n" RESET);
            while (getchar() != '\n')
                ; // Clear invalid input
        }
        else
        {
            break;
        }
    }
    return difficulty;
}

/*******************************************************************************
 * Game Loop
 *
 * Manages the main game flow including:
 * - Turn management
 * - Win/draw detection
 * - Score updating
 *
 * Parameters:
 * difficulty: Selected game difficulty level
 ******************************************************************************/
void play_game(int difficulty)
{
    initialize_board();
    display_score();

    int player_turn = rand() % 2; // 0 for computer, 1 for Player X

    while (1)
    {
        clear_screen();
        display_score();
        display_board();

        if (player_turn)
        {
            player_move();
        }
        else
        {
            computer_move(difficulty);
        }

        if (is_winner(player_turn ? 'X' : 'O'))
        {
            clear_screen();
            display_board();
            if (player_turn)
            {
                printf(GREEN "Player X wins!\n" RESET);
                playerX_score++;
                display_score();
            }
            else
            {
                printf(RED "Computer wins!\n" RESET);
                computer_score++;
                display_score();
            }
            break;
        }
        else if (is_draw())
        {
            clear_screen();
            display_board();
            printf(YELLOW "It's a draw!\n" RESET);
            draws++;
            display_score();
            break;
        }

        player_turn = !player_turn;
    }
}

/*******************************************************************************
 * Board Management Functions
 ******************************************************************************/

/* Initializes the game board with empty spaces */
void initialize_board()
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = ' ';
}

/* Displays the current game board with colored symbols */
void display_board()
{
    printf(CYAN "Current Board:\n" RESET);
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] == 'X')
                printf(GREEN " %c " RESET, board[i][j]);
            else if (board[i][j] == 'O')
                printf(RED " %c " RESET, board[i][j]);
            else
                printf(" %c ", board[i][j]);

            if (j < SIZE - 1)
                printf(BLUE "|" RESET);
        }
        printf("\n");
        if (i < SIZE - 1)
            printf(BLUE "---+---+---\n" RESET);
    }
}

/* Displays current game scores */
void display_score()
{
    printf(YELLOW "Score - " GREEN "Player X: %d" RESET " | " RED "Computer: %d" RESET " | " CYAN "Draws: %d\n" RESET, playerX_score, computer_score, draws);
}

/* Clears the console screen */
void clear_screen()
{
    printf("\e[1;1H\e[2J"); // ANSI escape code to clear screen
}

/*******************************************************************************
 * Game Logic Functions
 ******************************************************************************/

/* Checks if the specified symbol has won */
int is_winner(char symbol)
{
    for (int i = 0; i < SIZE; i++)
        if ((board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) ||
            (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol))
            return 1;
    if ((board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) ||
        (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol))
        return 1;
    return 0;
}

/* Checks if the game is a draw */
int is_draw()
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] == ' ')
                return 0;
    return 1;
}

/* Handles player move input and validation */
void player_move()
{
    int row, col;
    while (1)
    {
        printf(GREEN "Enter your move (row and column): " RESET);
        scanf("%d %d", &row, &col);
        if (row >= 1 && row <= SIZE && col >= 1 && col <= SIZE && board[row - 1][col - 1] == ' ')
        {
            board[row - 1][col - 1] = 'X';
            break;
        }
        else
        {
            printf(RED "Invalid move. Try again.\n" RESET);
        }
    }
}

/*******************************************************************************
 * AI Logic Functions
 ******************************************************************************/

/* Manages computer moves based on difficulty level */
void computer_move(int difficulty)
{
    if (difficulty == 1)
    { // Human difficulty with smarter strategy
        // Check if the computer can win in the next move
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = 'O';
                    if (is_winner('O'))
                        return;
                    board[i][j] = ' ';
                }
            }
        }

        // Block Player X if they can win in the next move
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = 'X';
                    if (is_winner('X'))
                    {
                        board[i][j] = 'O';
                        return;
                    }
                    board[i][j] = ' ';
                }
            }
        }

        // If no imminent win or block, choose random available position
        int row, col;
        do
        {
            row = rand() % SIZE;
            col = rand() % SIZE;
        } while (board[row][col] != ' ');
        board[row][col] = 'O';
    }
    else
    { // God difficulty using Minimax for optimal moves
        int best_score = -1000;
        int move_row = -1, move_col = -1;
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = 'O';
                    int score = minimax(board, 0, 0);
                    board[i][j] = ' ';
                    if (score > best_score)
                    {
                        best_score = score;
                        move_row = i;
                        move_col = j;
                    }
                }
            }
        }
        board[move_row][move_col] = 'O';
    }
}

/* Minimax algorithm for unbeatable AI
 * Returns the best possible score for the current board state
 */
int minimax(char board[SIZE][SIZE], int depth, int isMaximizing)
{
    if (is_winner('O'))
        return 10 - depth;
    if (is_winner('X'))
        return depth - 10;
    if (is_draw())
        return 0;

    int best_score = isMaximizing ? -1000 : 1000;
    char symbol = isMaximizing ? 'O' : 'X';

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = symbol;
                int score = minimax(board, depth + 1, !isMaximizing);
                board[i][j] = ' ';
                if (isMaximizing)
                {
                    best_score = (score > best_score) ? score : best_score;
                }
                else
                {
                    best_score = (score < best_score) ? score : best_score;
                }
            }
        }
    }
    return best_score;
}
