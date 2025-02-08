#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

#include <stdbool.h>

#define N 9

bool isSafe(int grid[N][N], int row, int col, int num);
bool solveSudoku(int grid[N][N]);
bool findEmptyLocation(int grid[N][N], int *row, int *col);
void printGrid(int grid[N][N]);

#endif // SUDOKU_SOLVER_H
