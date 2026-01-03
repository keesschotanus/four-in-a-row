/*
 * four-in-a-row.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "four.h"


struct game_t game;

// This score is directly related to the evaluation function in eval-simple.c
// Currently it is the score for 3 in a row multiplied by 10 to allow some margin
int WINNING_SCORE = 100000 * 10;

int evaluatedPositions = 0;

static void usersTurn(char symbol);
static void cpusTurn(char symbol);
static void play();

int main(int argc, char *argv[])
{
	game = processArguments(argc, argv);
	initBoard();
	printBoard();

	play();

	if (verbose) {
		printf("Positions evaluated:%d\n", evaluatedPositions);
	}

	return EXIT_SUCCESS;
}


static void play()
{
	int score;
	do {
		int player = game.nextPlayer ? game.player2 : game.player1;
		int playerSymbol = game.nextPlayer ? game.player2Symbol : game.player1Symbol;
							  
		if (player == HUMAN)
			usersTurn(playerSymbol);
		else
			cpusTurn(playerSymbol);

		game.nextPlayer = !game.nextPlayer;
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
	if (game.algorithm == ALPHABETA)
		move = alphabeta(symbol, symbol == 'X', game.plies, INT_MIN, INT_MAX);
	else
		move = minimax(symbol, symbol == 'X', game.plies);

	board[move.row][move.col] = symbol;
	printf("Move: %d\n", move.col + 1);
}
