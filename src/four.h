#include <stdbool.h>

// Level of play, where one ply is one move 
extern int ply;

// Standard board size (should not be changed)
#define ROWS 6
#define COLS 7

extern char board [ROWS][COLS];

extern int verbose;

extern int WINNING_SCORE;

void    initBoard(void);
void    printBoard(void);
int     evaluateBoard(void);
struct  move_t minimax(char symbol, bool maximizing, int depth);
struct  move_t alphabeta(char symbol, bool maximizing, int depth, int alpha, int beta);

struct move_t
{
    int row;
    int col;
    char symbol;
    int score;
};

extern int evaluatedPositions;
