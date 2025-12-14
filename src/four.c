/*
 * four-in-a-row.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "four.h"

// This score is directly related to the evaluation function in eval-simple.c
// Currently it is the score for 4 in a row divided by 10 to allow some margin
int WINNING_SCORE = 10000000;

int evaluatedPositions = 0;
int ply = 5; // Default number of plies
int verbose = 0; // Verbose flag

enum { MINIMAX, ALPHABETA } algorithm = ALPHABETA;
enum players { CPU = 'C', HUMAN = 'H' };

struct {
	int player1;
	char player1Symbol;
	int player2;
	char player2Symbol;
	int nextPlayer;
	int numberOfMoves;
} game = { HUMAN, 'O', CPU, 'X', 1, 0 };

static void processArguments(int argc, char *argv[]);
static void usersTurn(char symbol);
static void cpusTurn(char symbol);
static void play();

int main(int argc, char *argv[])
{
	processArguments(argc, argv);
	initBoard();
	printBoard();

	play();

	if (verbose) {
		printf("Positions evaluated:%d\n", evaluatedPositions);
	}

	return 0;
}

/*
 * The following command line arguments are supported:
 * -p <number> Number of plies
 * -v Verbose mode
 * -a <algorithm> Algorithm to use (mm or ab)
 */
static void processArguments(int argc, char *argv[])
{
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
			int plies = atoi(argv[++i]);
			if (plies > 0) {
				ply = plies;
			} else {
				fprintf(stderr, "Invalid number of plies: %s\n",
					argv[i]);
				exit(EXIT_FAILURE);
			}
		} else if (strcmp(argv[i], "-v") == 0) {
			verbose = 1;
		} else if (strcmp(argv[i], "-a") == 0 && i + 1 < argc) {
			if (strcmp(argv[++i], "mm") == 0) {
				algorithm = MINIMAX;
			} else if (strcmp(argv[i], "ab") == 0) {
				algorithm = ALPHABETA;
			} else {
				fprintf(stderr,
					"Invalid algorithm: %s, must be mm {minimax} or ab {alphabeta}\n",
					argv[i]);
				exit(EXIT_FAILURE);
			}
		} else {
			fprintf(stderr, "Unknown argument: %s\n", argv[i]);
			fputs("Usage: four [-p <number-of-plies>] [-v] [-a {mm|ab}]\n",
			      stderr);
			exit(EXIT_FAILURE);
		}
	}
}

static void play()
{
	int score;
	do {
		int player = game.nextPlayer == 1 ? game.player1 : game.player2;
		int playerSymbol = game.nextPlayer == 1 ? game.player1Symbol :
							  game.player2Symbol;

		if (player == HUMAN)
			usersTurn(playerSymbol);
		else
			cpusTurn(playerSymbol);

		game.nextPlayer = game.nextPlayer == 1 ? 2 : 1;
		game.numberOfMoves++;
		printBoard();
		score = evaluateBoard();
	} while (game.numberOfMoves < ROWS * COLS && abs(score) < WINNING_SCORE);

	if (game.numberOfMoves == ROWS * COLS)
		puts("It is a draw!");
	else if (score > WINNING_SCORE)
		puts("Player 'X' wins!");
	else
		puts("Player 'O' wins!");
}

static void usersTurn(char symbol)
{
	int moved = 0;
	do {
		int col;
		printf("Your move:");
		scanf("%d", &col);
		getchar();
		--col;
		if (col >= 0 && col < COLS && board[0][col] == ' ') {
			// Drop token into col by placing the players symbol on the right row
			int row;
			for (row = ROWS - 1; row >= 0 && board[row][col] != ' ';
			     --row)
				;
			board[row][col] = symbol;
			moved = 1;
		} else {
			printf("Illegal move\n");
		}
	} while (!moved);
}

static void cpusTurn(char symbol)
{
	struct move_t move;
	if (algorithm == ALPHABETA)
		move = alphabeta(symbol, 1, ply, INT_MIN, INT_MAX);
	else
		move = minimax(symbol, 1, ply);

	board[move.row][move.col] = symbol;
	printf("Move: %d\n", move.col + 1);
}
