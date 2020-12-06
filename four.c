/*
 * four-in-a-row.
 */

#include <stdio.h>

// Standard board size (may be increased to 9 columns)
#define ROWS 6
#define COLS 7

void initBoard(void);
void printBoard(void);
void play(void);
void usersTurn(char symbol);
void cpusTurn(char symbol);

char board [ROWS][COLS];

enum players { CPU = 'C', HUMAN = 'H'};
struct 
{
    int player1;
    char player1Symbol;
    int player2;
    char player2Symbol;
    int nextPlayer;
    int numberOfMoves;
} game = {HUMAN, 'O', CPU, 'X', 1, 0};

int main()
{
    initBoard();
    printBoard();


    play();
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

void play() 
{
    do
    {
        int player = game.nextPlayer == 1 ? game.player1 : game.player2;
        int playerSymbol = game.nextPlayer == 1 ? game.player1Symbol : game.player2Symbol;
        
        if (player == HUMAN)
            usersTurn(playerSymbol);
        else
            cpusTurn(playerSymbol);

        game.nextPlayer = game.nextPlayer == 1 ? 2 : 1;
        game.numberOfMoves++;
        printBoard();
    } while (game.numberOfMoves < ROWS * COLS);
}

void usersTurn(char symbol)
{
    int moved = 0;
    do {
        int col;
        printf("Your move:");
        scanf("%d", &col); getchar();
        --col;
        if (col >=0 && col < COLS && board[0][col] == ' ')
        {
            // Drop token into col by placing the players symbol on the right row
            int row;
            for (row = 0; board[row][col] == ' '; ++row);
            board[row - 1][col] = symbol;
            moved = 1;
        }
        else
        {
            printf("Illegal move\n");
        }
    } while(!moved);
}

void cpusTurn(char symbol)
{
    int row, col;
    // Find the first empty column
    for (col = 0; col < COLS && board[0][col] != ' '; ++col);

    // Drop the token in this column
    for (row = 0; row < ROWS && board[row][col] == ' '; ++row);
    board[row - 1][col] = symbol;
}