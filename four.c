/*
 * four-in-a-row.
 */

#include <stdio.h>
#include <stdlib.h>

#include "four.h"

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

    #ifdef STATISTICS
        printf("Moves created:%d\n", statistics.movesCreated);
        printf("Moves removed:%d\n", statistics.movesRemoved);
    #endif

    return 0;
}

void play() 
{
    int score;
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
        score = evaluateBoard();

    } while (game.numberOfMoves < ROWS * COLS && abs(score) < 1000000);

    if (game.numberOfMoves == ROWS * COLS)
        puts("It is a draw!");
    else if (score > 1000000)
        puts("Player 'X' wins!");
    else
        puts("Player 'O' wins!");
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
    #ifdef ALPHABETA
        struct move_t move = alphabeta(symbol, 1, 7, -10000000, 10000000);
    #else
        struct move move = minimax(symbol, 1, 7);
    #endif

    board[move.row][move.col] = symbol;
    printf("Move: %d\n", move.col + 1);
}


struct move_t *createPossibleMoves(char symbol)
{
    struct move_t *pPreviousMove = NULL;
    struct move_t *pMove = NULL;

    int col;
    int row;
    for (col = 0; col < COLS; ++col)
    {
        for (row = ROWS - 1; row >= 0; --row)
        {
            if (board[row][col] == ' ')
            {
                pMove = (struct move_t *)malloc(sizeof(struct move_t));
                #ifdef STATISTICS
                    statistics.movesCreated++;
                #endif
                pMove->row = row;
                pMove->col = col;
                pMove->symbol = symbol;
                pMove->nextMove = pPreviousMove;
                pPreviousMove = pMove;
                break;
            }
        }
    }

    return pMove;
}


