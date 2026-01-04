/*
 * Process command line arguments.
 */


#include "four.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int verbose = 0;

static int processPlies(const char *arg);
static enum players processPlayer(const char *arg);
static enum algorithm processAlgorithm(const char *arg);

/*
 * The following command line arguments are supported:
 * -p <number> Number of plies
 * -v Verbose mode
 * -a <algorithm> Algorithm to use (mm or ab)
 * -o <player> Where player is h (human) or c (computer).
 * -x <player> Where player is h (human) or c (computer).
 */
struct game_t processArguments(int argc, char *argv[])
{
	struct game_t game = { HUMAN, 'O', CPU, 'X', 0, 0, ALPHABETA, 5 };

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
			game.plies = processPlies(argv[++i]);
		} else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
			game.player1 = processPlayer(argv[++i]);
		} else if (strcmp(argv[i], "-x") == 0 && i + 1 < argc) {
			game.player2 = processPlayer(argv[++i]);
		} else if (strcmp(argv[i], "-v") == 0) {
			verbose = 1;
		} else if (strcmp(argv[i], "-a") == 0 && i + 1 < argc) {
			game.algorithm = processAlgorithm(argv[++i]);
		} else {
			fprintf(stderr, "Unknown argument: %s\n", argv[i]);
			fputs("Usage: four [-o h|c] [-x h|c] [-p <number-of-plies>] [-v] [-a {mm|ab}]\n",
			      stderr);
			exit(EXIT_FAILURE);
		}
	}
	return game;
}

enum players processPlayer(const char *arg)
{
	enum players player;

	if (strcmp(arg, "h") == 0) {
		player = HUMAN;
	} else if (strcmp(arg, "c") == 0) {
		player = CPU;
	} else {
		fprintf(stderr,	"Invalid player: %s, using default value of cpu\n", arg);
		player = CPU;
	}

	return player;
}

int processPlies(const char *arg)
{
	int plies = atoi(arg);
	if (plies < 1) {
		fprintf(stderr, "Invalid number of plies: %s, using a default value of 5\n", arg);
		plies = 5;
	}

	return plies;
}

enum algorithm processAlgorithm(const char *arg)
{
	enum algorithm algorithm;

	if (strcmp(arg, "mm") == 0) {
		algorithm = MINIMAX;
	} else if (strcmp(arg, "ab") == 0) {
		algorithm = ALPHABETA;
	} else {
		fprintf(stderr,	"Invalid algorithm: %s, using default value of alphabeta\n", arg);
		algorithm = ALPHABETA;
	}

	return algorithm;
}