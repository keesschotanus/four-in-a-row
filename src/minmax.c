#include <limits.h>
#include <stdlib.h>

#include "four.h"

struct move_t minimax(char player, int maximizing, int depth)
{
	evaluatedPositions++;

	struct move_t move;
	move.score = evaluateBoard();

	if (depth == 0 || move.score > WINNING_SCORE || move.score < -WINNING_SCORE) {
		move.col = -1;
		move.row = -1;
		move.symbol = player;
		return move;
	}

	int bestScore = maximizing ? INT_MIN : INT_MAX;
	struct move_t bestMove;

	for (int col = 0; col < COLS; ++col) {
		// Check if the column is not full
		if (board[0][col] == ' ') {
			int row;
			for (row = 1; board[row][col] == ' '; ++row)
				;
			--row;

			board[row][col] = player;
			struct move_t move = minimax(player == 'X' ? 'O' : 'X',
						     !maximizing, depth - 1);
			if (maximizing) {
				if (move.score > bestScore) {
					bestScore = move.score;
					bestMove.col = col;
					bestMove.row = row;
					bestMove.score = bestScore;
				}
			} else {
				if (move.score < bestScore) {
					bestScore = move.score;
					bestMove.col = col;
					bestMove.row = row;
					bestMove.score = bestScore;
				}
			}

			// Undo move
			board[row][col] = ' ';

			// If a score that wins the game is found we don't need to check the other columns
			if ((maximizing && bestScore >= WINNING_SCORE) || (!maximizing && bestScore <= -WINNING_SCORE)) {
				break;
			}
		}
	}

	return bestMove;
}
