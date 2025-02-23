# Four-in-a-row
This is my attempt to write the classic four-in-row game
in the C programming language.

## Build
To build this program, simply run make.
I only tried this on Linux using gcc.
The result is an executable named four.

### Execute
Simply execute ./four to start the program with the default settings.
The default settings are:
- Play at level 5 (think 2.5 moves ahead)
- Use Alpha/Beta algorithm
- Use a very simple function to evaluate the board.

You can change the defaults using command line parameters:

./four [-p <number-of-plies>] [-v] [-a {mm|ab}]

A single ply is one move of a player.
It takes two plies for each player to make a move.

The -v is for verbose (showing statistics).
The algorithm used is determined by the -a option and should either be
- mm for mini/max
- ab for alpha/beta

# Evaluation of the board
The [eval-simple](src/eval-simple.c) file contains a simple function to evaluate the board.
It simply counts the lengths of the player's discs (in any direction).
For the diagonals, only the ones with length of four and higher are considered.

| Number of discs in a row | Points |
| - | -------- |
| 1 | 1        |
| 2 | 100      |
| 3 | 10000    |
| 4 | 10000000 |

So there is no intelligence here, it only counts discs in any direction.

If the bottom row of the board looks like this: XOOX, the computer evaluates this position
as much better since it has 2 discs in a row.
In reality the score for 'O' in horizontal direction should be 0 as it can never
result in 4 in a row.

## Playing at ply 1
Let's play a game against the computer at ply 1.
At ply 1 the computer only evaluates its own move.
The human is 'O', the computer is 'X'.

```
Your move:4
Score: -4
|       |
|       |
|       |
|       |
|       |
|   O   |
 1234567
```
A negative score is a better score for the human player.
In this case it is -4 as a row of one discs counts as -1,
for every direction. In this case horizontally, vertically and 
in 2 diagonal directions.

The computer starts placing a disc at column 1 and computes the score.
It rewards 1 point for the horizontal direction, 1 point for the vertical
direction and 1 point for the single diagonal.
The remaining diagonal does not receive a point as it is shorter than 4.

Now the disc from column 1 is removed and placed at column 2,
before the score is computed.
Column 4 is the first column where 2 diagonals are involved, so it receives
the highest score of 4.
Placing the disc at yet a higher column, does not result in a higher score,
so the disc is placed at column 4 and the board is in balance since the 
total score of both players is 0.

The board now looks like this:
```text
Move: 4
Score: 0
|       |
|       |
|       |
|       |
|   X   |
|   O   |
 1234567
```

I place my disc at column 5 to horizontally get a length of 2 discs.
```text
Your move:5
Score: -101
|       |
|       |
|       |
|       |
|   X   |
|   OO  |
 1234567
```
The score of -101 indicates I'm well ahead and I will win if the computer
does not place its disc at column 3 or 6.
Unfortunately at ply 1 the computer only looks at its current move and not
what the opponent is going to do after the computer moves, so it places its
disc at column 4 since the simple evaluation function determines that the 
computer is now ahead.
```text
Move: 4
Score: 1
|       |
|       |
|       |
|   X   |
|   X   |
|   OO  |
 1234567

```
I place my disc at column 6 and win the game on my next move.
```text
Your move:7
Score: -9990000
|       |
|       |
|   X   |
|   X   |
|   X   |
|   OOOO|
 1234567
Player 'O' wins
```

## Playing at ply 3
Let's increase the number of plies to 3 so the computer  looks 1.5 moves ahead.
Replaying the same moves as above, we get the exact same game.
When the bottom rows looks like this:
```text
   X
   OO  '
 ```
The computer is determined to get 3 discs in a row and fails to see that its opponent
will win the game on the next move.

## Playing at ply 5
As before I place my disc at column 4 and the computer responds with using the same column.
```text
Score: 0
|       |
|       |
|       |
|       |
|   X   |
|   O   |
 1234567
```
Again a place my disc at column 5, but tis time the computer sees it will lose if it does
not place it disc at either column 3 or 6.
```text
Score: 0
|       |
|       |
|       |
|       |
|   X   |
|  XOO  |
 1234567
```

# Minimax versus Alpha/Beta pruning
The initial version used the [Minimax algorithm](https://en.wikipedia.org/wiki/Minimax),
with the evaluation function mentioned above, at ply 9.

This program played the following game against the unbeatable
[Connect 4 Solver](https://connect4.gamesolver.org/) another program.

Moves are represented as the column number where discs were dropped.
In parentheses the score is given after the computer's turn.

```
4 ,3 (-1)
6 ,3 (98)
7 ,5 (0)
6 ,3 (9704)
3 ,4 (19897)
4 ,5 (29796)
5 ,4 (19897)
6 ,6 (99)
4 ,2 (196)
2 ,5 (10194)
4 ,3 (10194)
3 ,6 (10194)
6 ,1 (20093)
1 ,2 (20192)
2 ,2 (20191)
2 ,1 (20191)
1 ,1 (20191)
1    (-9969811)

Player 'O' wins!
Positions evaluated:263223653

user  2m5,179s


### Alpha/Beta Algorithm
The second version used [Alpha/Beta pruning](https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning)

Using this algorithm I replayed the same game as played using minimax and the computer played exactly the
same moves, but with these statistics:

```text
Positions evaluated:8469475

user	0m4,171s

````

So, Alpha/Beta only evaluates: (8469475 / 263223653) * 100 = 3.2% of the moves.
Using only: (4171 / 125179) * 100  = 3.3% of the time.

# What's next

I need to write a better evaluation function, that keeps track of the possibility
to create 4 in a row. Currently a board like this: '  XOOX  ' evaluates the position of 'O'
way better than for 'X' since 'O' has a disc length of 2.
A smarter evaluation function should determine that the value of 'O' is 0 for the
horizontal direction as it can not lead to 4 in a row.
The same is true by the way for 'X' in horizontal direction.

The current evaluation function often misses the winning move!

An opening book would be great.
Even if it only contains a few moves it will save a lot of computation time.





