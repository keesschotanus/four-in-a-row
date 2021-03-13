/*
 * four-in-a-row.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "four.h"


char board [ROWS][COLS];

// Theoretically we can get 7 in a row!
int scoresPerTokenLength [] = {0, 1, 100, 10000, 10000000, 10000000, 10000000, 10000000};

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

struct move
{
    struct move *nextMove;
    int row;
    int col;
    char symbol;
    int score;
};

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

    printf("Score: %d\n", evaluateBoard());
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
        struct move move = alphabeta(symbol, 1, 7, -10000000, 10000000);
    #else
        struct move move = minimax(symbol, 1, 7);
    #endif

    board[move.row][move.col] = symbol;
    printf("Move: %d\n", move.col + 1);
}

int evaluateBoard()
{
    int score = 0;
    int row, col;

    for (row = 0; row < ROWS; ++row)
    {
        // Horizontally
        score += evaluateLine(row, 0,         0,  1);

        // Diagonally
        score += evaluateLine(row, 0,         1,  1);
        score += evaluateLine(row, COLS - 1, -1, -1);
        score += evaluateLine(row, 0,        -1,  1);
        score += evaluateLine(row, COLS - 1,  1, -1);
    }
    
    // Vertically
    for (col = 0; col < COLS; ++col)
    {
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
int evaluateLine(int row, int col, int incRow, int incCol)
{
    int score = 0;
    char previousToken = ' ';
    int tokenLength = 0;
    for (; row >= 0 && row < ROWS && col >= 0 && col < COLS; row += incRow, col += incCol) {
        int currentToken = board[row][col];
        if (currentToken == ' ')
        {
            if (previousToken != ' ')
            {
                score += getScoreForTokenLength(previousToken, tokenLength);
                tokenLength = 0;
            }
        } else if (currentToken == previousToken)
        {
            tokenLength++;
        } else
        {
            score += getScoreForTokenLength(previousToken, tokenLength);
            tokenLength = 1;
        }

        previousToken = currentToken;
    }
    // We might be in the middle of processing tokens
    score += previousToken == ' ' ? 0 : getScoreForTokenLength(previousToken, tokenLength);
    return score;
}

inline int getScoreForTokenLength(char token, int tokenLength)
{
    return token == 'X' ? scoresPerTokenLength[tokenLength] : -scoresPerTokenLength[tokenLength];
}

struct move *createPossibleMoves(char symbol)
{
    struct move *pPreviousMove = NULL;
    struct move *pMove = NULL;

    int col;
    int row;
    for (col = 0; col < COLS; ++col)
    {
        for (row = ROWS - 1; row >= 0; --row)
        {
            if (board[row][col] == ' ')
            {
                pMove = (struct move *)malloc(sizeof(struct move));
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

struct move minimax(char player, int maximizing, int depth)
{
    struct move move;
    move.score = evaluateBoard();

    if (depth == 0 || move.score > 1000000 || move.score < -1000000)
    {
        return move;
    }

    int bestScore = maximizing ? INT_MIN : INT_MAX;
    struct move *moves = createPossibleMoves(player);
    if (moves == NULL)
    {
        return move;
    }

    struct move bestMove;
    int row, col;
    while (moves)
    {
        board[moves->row][moves->col] = player;
        row = moves->row;
        col = moves->col;
        struct move move = minimax(player == 'X' ? 'O' : 'X', !maximizing, depth - 1);
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
        struct move *freeMove = moves;
        moves = moves->nextMove;
        free(freeMove);
        #ifdef STATISTICS
            statistics.movesRemoved++;
        #endif

    }
    return bestMove;
}


struct move alphabeta(char player, int maximizing, int depth, int alpha, int beta)
{
    struct move move;
    move.score = evaluateBoard();

    if (depth == 0 || move.score > 1000000 || move.score < -1000000)
    {
        return move;
    }

    int bestScore = maximizing ? INT_MIN : INT_MAX;
    struct move *moves = createPossibleMoves(player);
    if (moves == NULL)
    {
        return move;
    }

    struct move bestMove;
    int row, col;
    while (moves)
    {
        board[moves->row][moves->col] = player;
        row = moves->row;
        col = moves->col;
        struct move move = alphabeta(player == 'X' ? 'O' : 'X', !maximizing, depth - 1, alpha, beta);
        if (maximizing)
        {
            if (move.score > bestScore) 
            {
                bestScore = move.score;
                bestMove.col = col;
                bestMove.row = row;
                bestMove.score = bestScore;
            }
            alpha = alpha  > bestScore ? alpha : bestScore;
        } else {
            if (move.score < bestScore)
            {
                bestScore = move.score;
                bestMove.col = col;
                bestMove.row = row;
                bestMove.score = bestScore;
            }
            beta = beta < bestScore ? beta : bestScore;
        }

        // Undo move
        board[row][col]= ' ';
        struct move *freeMove = moves;
        moves = moves->nextMove;
        free(freeMove);
        #ifdef STATISTICS
            statistics.movesRemoved++;
        #endif

        if (beta <= alpha) 
        {
            break;
        }
    }
    return bestMove;
}
