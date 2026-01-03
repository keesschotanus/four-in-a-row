#include <stdbool.h>


// Standard board size (should not be changed)
#define ROWS 6
#define COLS 7

extern char board [ROWS][COLS];
extern int verbose;
extern int WINNING_SCORE;
extern int evaluatedPositions;
extern int plies;
extern int verbose;

struct game_t   processArguments(int argc, char *argv[]);
void            initBoard(void);
void            printBoard(void);
int             evaluateBoard(void);
struct move_t   minimax(char symbol, bool maximizing, int depth);
struct move_t   alphabeta(char symbol, bool maximizing, int depth, int alpha, int beta);

enum algorithm { MINIMAX, ALPHABETA };
enum players { CPU = 'C', HUMAN = 'H' };

struct game_t {
	int player1;
	char player1Symbol;
	int player2;
	char player2Symbol;
	int nextPlayer; // 0 or 1
	int numberOfMoves;
    enum algorithm algorithm;
    int plies;
};


struct move_t
{
    int row;
    int col;
    char symbol;
    int score;
};

