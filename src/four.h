// Level of play, where one ply is one move 
extern int ply;

// Standard board size (should not be changed)
#define ROWS 6
#define COLS 7

extern char board [ROWS][COLS];

extern int verbose;

void    initBoard(void);
void    printBoard(void);
int     evaluateBoard(void);
struct  move_t minimax(char symbol, int maximizing, int depth);
struct  move_t alphabeta(char symbol, int maximizing, int depth, int alpha, int beta);

struct move_t
{
    int row;
    int col;
    char symbol;
    int score;
};

extern int evaluatedPositions;
