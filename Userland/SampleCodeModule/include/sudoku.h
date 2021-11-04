#ifndef SUDOKU_H
#define SUDOKU_H

#include <games.h>

#define DIM 9
#define SUB_DIM 3

void sudoku(char c);
void getMatrixPosition(int row, int col, int *x, int *y);
void printMatrix(int row, int col, int value);
void baseSudoku();
void message();
#endif