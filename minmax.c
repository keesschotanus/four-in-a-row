#include <limits.h>
#include <stdlib.h>

#include "four.h"


struct move_t minimax(char player, int maximizing, int depth)
{
    #ifdef STATISTICS
        evaluatedPositions++;
    #endif

    struct move_t move;
    move.score = evaluateBoard();

    if (depth == 0 || move.score > 1000000 || move.score < -1000000)
    {
        return move;
    }

    int bestScore = maximizing ? INT_MIN : INT_MAX;
    struct move_t bestMove;

    for (int col = 0; col < COLS; ++col)
    {
        if (board[0][col] == ' ')
        {
            int row;
            for (row = 1; board[row][col] == ' '; ++row)
                ;
            --row;


            board[row][col] = player;
            struct move_t move = minimax(player == 'X' ? 'O' : 'X', !maximizing, depth - 1);
            if (maximizing)
            {
                if (move.score > bestScore) 
                {
                    bestScore = move.score;
                    bestMove.col = col;
                    bestMove.row = row;
                    bestMove.score = bestScore;
                }
            } else {
                if (move.score < bestScore)
                {
                    bestScore = move.score;
                    bestMove.col = col;
                    bestMove.row = row;
                    bestMove.score = bestScore;
                }
            }

            // Undo move
            board[row][col]= ' ';

        }
    }



    return bestMove;
}

