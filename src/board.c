#include <stdio.h>

#include "four.h"

char board [ROWS][COLS];

/*
 * Initializes the board by emptying all cells.
 */
void initBoard(void)
{
    for (int rows = 0; rows < ROWS; ++rows) {
        for (int cols = 0; cols < COLS; ++cols) {
            board[rows][cols] = ' ';
        }
    }
}

void printBoard(void)
{
    printf("Score: %d\n", evaluateBoard());
    for (int rows = 0; rows < ROWS; ++rows) {
        putchar('|');
        for (int cols = 0; cols < COLS; ++cols) {
            printf("%c", board[rows][cols]);
        }
        printf("|\n");
    }
    printf("%.*s\n", COLS + 1, " 1234567");
}
