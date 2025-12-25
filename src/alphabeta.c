#include <limits.h>
#include <stdlib.h>

#include "four.h"

struct move_t alphabeta(char player, bool maximizing, int depth, int alpha, int beta)
{
	evaluatedPositions++;

	struct move_t move, bestMove;
	move.score = evaluateBoard();

	if (depth == 0 || move.score > WINNING_SCORE || move.score < -WINNING_SCORE) {
		return move;
	}

	int bestScore = maximizing ? INT_MIN : INT_MAX;

	for (int col = 0; col < COLS; ++col) {
		if (board[0][col] == ' ') {
			int row = 1;
			for (; board[row][col] == ' '; ++row)
				;
			--row;
			board[row][col] = player;

			struct move_t move = alphabeta(player == 'X' ? 'O' : 'X', !maximizing, depth - 1, alpha, beta);
			if (maximizing) {
				if (move.score > bestScore) {
					bestScore = move.score;
					bestMove.col = col;
					bestMove.row = row;
					bestMove.score = bestScore;
				}
				alpha = alpha > bestScore ? alpha : bestScore;
			} else {
				if (move.score < bestScore) {
					bestScore = move.score;
					bestMove.col = col;
					bestMove.row = row;
					bestMove.score = bestScore;
				}
				beta = beta < bestScore ? beta : bestScore;
			}

			// Undo move
			board[row][col] = ' ';

			if (beta <= alpha)
				break;
		}
	}

	return bestMove;
}
