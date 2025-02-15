#include <stdio.h>

#include "four.h"

// Theoretically we can get 7 in a row!
int scoresPerTokenLength [] = {0, 1, 100, 10000, 10000000, 10000000, 10000000, 10000000};

static int evaluateLine(int row, int col, int incRow, int incCol);
static int getScoreForTokenLength(char token, int tokenLength);

int evaluateBoard()
{
    int score = 0;
    for (int row = 0; row < ROWS; ++row) {
        // Horizontally
        score += evaluateLine(row, 0,         0,  1);

        // Diagonally
        score += evaluateLine(row, 0,         1,  1);
        score += evaluateLine(row, COLS - 1, -1, -1);
        score += evaluateLine(row, 0,        -1,  1);
        score += evaluateLine(row, COLS - 1,  1, -1);
    }
    
    // Vertically
    for (int col = 0; col < COLS; ++col) {
        score += evaluateLine(0, col, 1, 0);
    }

    return score;
}

/*
 * Evaluates a single line on the board.
 * row Row number.
 * col Column number.
 * incRow Number by which the row should be incremented (may be negative)
 * incCol Number by which the col should be incremented (may be negative)
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
                score += getScoreForTokenLength(previousToken, tokenLength);
                tokenLength = 0;
            }
        } else if (currentToken == previousToken) {
            tokenLength++;
        } else {
            score += getScoreForTokenLength(previousToken, tokenLength);
            tokenLength = 1;
        }

        previousToken = currentToken;
    }
    // We might be in the middle of processing tokens
    score += previousToken == ' ' ? 0 : getScoreForTokenLength(previousToken, tokenLength);
    return score;
}

static inline int getScoreForTokenLength(char token, int tokenLength)
{
    return token == 'X' ? scoresPerTokenLength[tokenLength] : -scoresPerTokenLength[tokenLength];
}
