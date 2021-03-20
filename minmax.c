#include <limits.h>
#include <stdlib.h>

#include "four.h"


struct move_t minimax(char player, int maximizing, int depth)
{
    struct move_t move;
    move.score = evaluateBoard();

    if (depth == 0 || move.score > 1000000 || move.score < -1000000)
    {
        return move;
    }

    int bestScore = maximizing ? INT_MIN : INT_MAX;
    struct move_t *moves = createPossibleMoves(player);
    if (moves == NULL)
    {
        return move;
    }

    struct move_t bestMove;
    int row, col;
    while (moves)
    {
        board[moves->row][moves->col] = player;
        row = moves->row;
        col = moves->col;
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
        struct move_t *freeMove = moves;
        moves = moves->nextMove;
        free(freeMove);
        #ifdef STATISTICS
            statistics.movesRemoved++;
        #endif

    }
    return bestMove;
}

