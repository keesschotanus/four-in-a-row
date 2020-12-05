/*
 * four-in-a-row.
 */

#include <stdio.h>

// Standard board size (may be increased to 9 columns)
#define ROWS 6
#define COLS 7

void initBoard(void);
void printBoard(void);

char board [ROWS][COLS];

enum players { CPU = 'C', HUMAN = 'H'};
struct 
{
    int player1;
    char player1Symbol;
    int player2;
    char player2Symbol;
    int nextPlayer;
} game = {HUMAN, 'O', CPU, 'X', 1};

int main()
{
    initBoard();
    printBoard();

    return 0;
}

/*
 * Initializes the board by emptying all cells.
 */
void initBoard(void)
{
    int rows, cols;
    for (rows = 0; rows < ROWS; ++rows)
    {
        for (cols = 0; cols < COLS; ++cols)
        {
            board[rows][cols] = ' ';
        }
    }
}

void printBoard(void)
{
    int rows, cols;

    for (rows = 0; rows < ROWS; ++rows)
    {
        putchar('|');
        for (cols = 0; cols < COLS; ++cols)
        {
            printf("%c", board[rows][cols]);
        }
        printf("|\n");
    }
    printf("%.*s\n", COLS + 1, " 123456789");
}
