// Standard board size (may be increased to 9 columns)
#define ROWS 6
#define COLS 7

#define STATISTICS
#define ALPHABETA

void    initBoard(void);
void    printBoard(void);
void    play(void);
void    usersTurn(char symbol);
void    cpusTurn(char symbol);
int     evaluateBoard(void);
int     evaluateLine(int row, int col, int incRow, int incCol);
int     getScoreForTokenLength(char token, int tokenLength);
struct  move *createPossibleMoves(char symbol);
struct  move minimax(char symbol, int maximizing, int depth);
struct  move alphabeta(char symbol, int maximizing, int depth, int alpha, int beta);

#ifdef STATISTICS
    struct
    {
        int movesCreated;
        int movesRemoved;
    } statistics = {0, 0};
#endif
