// Standard board size (may be increased to 9 columns)
#define ROWS 6
#define COLS 7

char board [ROWS][COLS];

#define STATISTICS
#define ALPHABETA
// #define MINIMAX

void    initBoard(void);
void    printBoard(void);
void    play(void);
void    usersTurn(char symbol);
void    cpusTurn(char symbol);
int     evaluateBoard(void);
int     getScoreForTokenLength(char token, int tokenLength);
struct  move_t minimax(char symbol, int maximizing, int depth);
struct  move_t alphabeta(char symbol, int maximizing, int depth, int alpha, int beta);

struct move_t
{
    int row;
    int col;
    char symbol;
    int score;
};

int evaluatedPositions;
