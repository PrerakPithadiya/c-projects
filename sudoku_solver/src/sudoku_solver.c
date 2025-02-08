#include <stdio.h>
#include <stdbool.h>

#define N 9
#define ANSI_COLOR_RED "\x1b[91m"
#define ANSI_COLOR_GREEN "\x1b[92m"
#define ANSI_COLOR_BLUE "\x1b[96m"
#define ANSI_COLOR_YELLOW "\x1b[93m"
#define ANSI_COLOR_MAGENTA "\x1b[95m"
#define ANSI_COLOR_RESET "\x1b[0m"

// Function prototypes
bool isSafe(int grid[N][N], int row, int col, int num);
bool solveSudoku(int grid[N][N]);
bool findEmptyLocation(int grid[N][N], int *row, int *col);
void printGrid(int grid[N][N]);

// Main function to test the solver
int main()
{
    int grid[N][N] = {
        {0, 0, 0, 2, 6, 0, 7, 0, 1},
        {6, 8, 0, 0, 7, 0, 0, 9, 0},
        {1, 9, 0, 0, 0, 4, 5, 0, 0},
        {8, 2, 0, 1, 0, 0, 0, 4, 0},
        {0, 0, 4, 6, 0, 2, 9, 0, 0},
        {0, 5, 0, 0, 0, 3, 0, 2, 8},
        {0, 0, 9, 3, 0, 0, 0, 7, 4},
        {0, 4, 0, 0, 5, 0, 0, 3, 6},
        {7, 0, 3, 0, 1, 8, 0, 0, 0}};

    printf(ANSI_COLOR_YELLOW "\nUnsolved Sudoku:" ANSI_COLOR_RESET);
    printGrid(grid);

    if (solveSudoku(grid) == true)
    {
        printf(ANSI_COLOR_YELLOW "\nSolved Sudoku:" ANSI_COLOR_RESET);
        printGrid(grid);
    }
    else
        printf(ANSI_COLOR_RED "No solution exists\n" ANSI_COLOR_RESET);

    return 0;
}

// Function to check if it's safe to place a number in a given cell
bool isSafe(int grid[N][N], int row, int col, int num)
{
    // Check row
    for (int x = 0; x < N; x++)
        if (grid[row][x] == num)
            return false;

    // Check column
    for (int x = 0; x < N; x++)
        if (grid[x][col] == num)
            return false;

    // Check 3x3 subgrid
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;
}

// Recursive backtracking function to solve the Sudoku puzzle
bool solveSudoku(int grid[N][N])
{
    int row, col;

    // If there's no empty cell left, puzzle is solved
    if (!findEmptyLocation(grid, &row, &col))
        return true;

    // Try numbers 1 to 9 in the empty cell
    for (int num = 1; num <= 9; num++)
    {
        if (isSafe(grid, row, col, num))
        {
            grid[row][col] = num;

            // Recursively attempt to solve the rest of the grid
            if (solveSudoku(grid))
                return true;

            // If placing num doesn't lead to a solution, backtrack
            grid[row][col] = 0;
        }
    }
    return false; // Trigger backtracking
}

// Function to find an empty cell in the grid
bool findEmptyLocation(int grid[N][N], int *row, int *col)
{
    for (*row = 0; *row < N; (*row)++)
        for (*col = 0; *col < N; (*col)++)
            if (grid[*row][*col] == 0)
                return true;
    return false;
}

// Function to print the Sudoku grid
void printGrid(int grid[N][N])
{
    printf(ANSI_COLOR_BLUE "\n+-------+-------+-------+" ANSI_COLOR_RESET "\n");
    for (int row = 0; row < N; row++)
    {
        printf(ANSI_COLOR_MAGENTA "| " ANSI_COLOR_RESET);
        for (int col = 0; col < N; col++)
        {
            if (grid[row][col] == 0)
                printf(ANSI_COLOR_RED " " ANSI_COLOR_RESET);
            else
                printf(ANSI_COLOR_GREEN "%d" ANSI_COLOR_RESET, grid[row][col]);

            if ((col + 1) % 3 == 0)
                printf(ANSI_COLOR_MAGENTA " | " ANSI_COLOR_RESET);
            else
                printf(" ");
        }
        printf("\n");
        if ((row + 1) % 3 == 0)
            printf(ANSI_COLOR_BLUE "+-------+-------+-------+" ANSI_COLOR_RESET "\n");
    }
}