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

| Number of discs in a row | Points |
| - | -------- |
| 1 | 1        |
| 2 | 100      |
| 3 | 10000    |
| 4 | 10000000 |

So there is no intelligence here, it only counts discs in any direction.

If the bottom row of the board looks like this: XOOX, the computer evaluates this position
as much better since it has a rw of 2 discs.

## Playing at ply 1
Let's play a game against the computer at ply 1.
At ply one the computer only evaluates its own move.
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
for every direction. In this case horizontal, vertical and 
in 2 diagonal directions.

The computer starts looking at column 1, sees that this is 
currently the best move and then looks at the remaining columns,
only to see that it can not improve its score.

```
Move: 1
Score: 0
|       |
|       |
|       |
|       |
|       |
|X  O   |
 1234567
``` 
The human player keeps on stacking its discs and so does the computer, until we have this situation:

```
Move: 1
Score: 0
|       |
|       |
|       |
|X  O   |
|X  O   |
|X  O   |
 1234567
 ```

Remember at ply 1 the computer only looks at its own move.
On the next move the human wins.

## Playing at ply 3
Let's increase the number of plies to 3 so the computer likes 1.5 moves ahead.
The human playing 'O' makes the first move, as before.

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
At this level, the computer still places its disc in column 1.
The human keeps stacking it discs and so does the computer until this board position:

```
Your move:4
Score: -9903
|       |
|       |
|       |
|   O   |
|X  O   |
|X  O   |
 1234567
 ```
This time however the computer looks further ahead and makes the correct move:

Move: 4
Score: -9899
|       |
|       |
|   X   |
|   O   |
|X  O   |
|X  O   |
 1234567

So we have to think of another strategy now to win.
Let's see what happens when we place our discs side by side.

We get this board:
```
Move: 1
Score: 0
|       |
|       |
|       |
|       |
|X      |
|X  OO  |
 1234567
 ```

So the computer keeps stacking its discs but the human placed them side by side.
The computer does not see that it has lost since the human can place it disc at either
column 3 or 6 and win on the next move.

## Playing at ply 5
We will try the same moves as done at ply 3, so this is what the board looks like:
```
Your move:5
Score: -102
|       |
|       |
|       |
|       |
|       |
|X  OO  |
 1234567
```
This time however the computer looks further ahead and figures out it will lose if it doesn't
place the disc at either column 3 or 6.

```
Move: 3
Score: -98
|       |
|       |
|       |
|       |
|       |
|X XOO  |
 1234567
 ```

## Playing at ply 7
At ply 7 something interesting happens.
The computer finally notices that placing its opening disc in column 1
is not a good move. 
Even though the algorithm did not change, by looking further ahead,
the program finally showed some intelligence.

Here is the board after the computer moved.
```
Move: 3
Score: 0
|       |
|       |
|       |
|       |
|       |
|  XO   |
 1234567
 ```

# Minimax versus Alpha/Beta pruning
The initial version used the [Minimax algorithm](https://en.wikipedia.org/wiki/Minimax),
with the evaluation function mentioned above.

This program played the following game against another program.
Moves are represented as the column number where discs were dropped.
In parentheses the score is given after the computer's turn.

```
3,4 (    0)
1,4 (   98)
4,5 (  294)
7,3 (  490)
4,3 (10389)
4,4 (  490)
1,5 (10487)
1,1 (  588)
5,2 (  490)
2,2 Computer wins
Positions evaluated: 5715791
user    0m5,244s
```

### Alpha/Beta Algorithm
The second version used [Alpha/Beta pruning](https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning)

Using this algorithm I replayed the game played using minimax and the  computer played exactly the
same moves, but with these statistics:

```Positions evaluated:218901
user    0m0,337s
````

So, Alpha/Beta only evaluates: (218901 / 5715791) * 100 = 3.83% of the moves.
Using only: (0.337 / 5.244) * 100  = 6.43% of the time.

# What's next

I need to write a better evaluation function, that keeps track of the possibility
to create 4 in a row. Currently a board like this: '  XOOX  ' evaluates the position of 'O'
way better than for 'X' since 'O' has a disc length of 2.
A smarter evaluation function should determine that the value of 'O' is 0 for the
horizontal direction as it can not lead to 4 in a row.
The same is true by the way for 'X' in horizontal direction.





