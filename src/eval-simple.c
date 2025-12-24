#include <stdio.h>

#include "four.h"

const int DISC_LENGTH_0 = 0;
const int DISC_LENGTH_1 = 1;
const int DISC_LENGTH_2 = 100;
const int DISC_LENGTH_3 = 10000;
const int DISC_LENGTH_4 = 10000000;

// Theoretically we can get 7 in a row!
int scoresPerTokenLength[] = {
	DISC_LENGTH_0,
	DISC_LENGTH_1,
	DISC_LENGTH_2,
	DISC_LENGTH_3,
	DISC_LENGTH_4, DISC_LENGTH_4, DISC_LENGTH_4, DISC_LENGTH_4
};

int lines[][4] = {
	// Rows
	{0, 0, 0, 1}, {1, 0, 0, 1},{2, 0, 0, 1},{3, 0, 0, 1},{4, 0, 0, 1},{5, 0, 0, 1},
	// Columns
	{0, 0, 1, 0}, {0, 1, 1, 0},{0, 2, 1, 0},{0, 3, 1, 0},{0, 4, 1, 0},{0, 5, 1, 0},{0, 6, 1, 0},
	// Diagonals (bottom right to top left)
	{3, 0, -1, 1}, {4, 0, -1, 1}, {5, 0, -1, 1}, {5, 1, -1, 1}, {5, 2, -1, 1} ,{5, 3, -1, 1},
	// Diagonals (bottom left to top right)
	{3, 6, -1, -1}, {4, 6, -1, -1}, {5, 6, -1, -1}, {5, 5, -1, -1}, {5, 4, -1, -1} ,{5, 3, -1, -1}
};

static int evaluateLine(int row, int col, int incRow, int incCol);
static int getScoreForTokenLength(char token, int tokenLength);

int evaluateBoard()
{
	int score = 0;
	for (int line = 0; line < 25; ++line)
		score += evaluateLine(lines[line][0], lines[line][1], lines[line][2], lines[line][3]);

	return score;
}

/**
 * Evaluates a single line on the board.
 *
 * @param row Row number.
 * @param col Column number.
 * @param incRow Number by which the row should be incremented (may be negative)
 * @param incCol Number by which the col should be incremented (may be negative)
 * @returns The score for the line.
 */
static int evaluateLine(int row, int col, int incRow, int incCol)
{
	int score = 0;
	char previousToken = ' ';
	int tokenLength = 0;
	for (; row >= 0 && row < ROWS && col >= 0 && col < COLS; row += incRow, col += incCol) {
		int currentToken = board[row][col];
		if (currentToken == ' ') {
			if (previousToken != ' ') {
				score += getScoreForTokenLength(previousToken,
								tokenLength);
				tokenLength = 0;
			}
		} else if (currentToken == previousToken) {
			tokenLength++;
		} else {
			score += getScoreForTokenLength(previousToken,
							tokenLength);
			tokenLength = 1;
		}

		previousToken = currentToken;
	}
	// We might be in the middle of processing tokens
	score += previousToken == ' ' ?
			 0 :
			 getScoreForTokenLength(previousToken, tokenLength);
	return score;
}

static inline int getScoreForTokenLength(char token, int tokenLength)
{
	return token == 'X' ? scoresPerTokenLength[tokenLength] :
			      -scoresPerTokenLength[tokenLength];
}
