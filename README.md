# Four-in-a-row
This is my attempt to write the classic four-in-row game
in the C programming language.

### Initial attempt
Initially there won't be any optimizations as I want to measure the performance
of any optimizations.
The first draft will use a simple mini-max algorithm and the evaluation of the board
will be simple. Future versions will use alpha/beta and have a more sophisticated 
algorithm to evaluate the board.

### Mini/max Algorithm
Using the minimax algorithm, and the simple evaluation of the board,
the computer played the following game against me.
In parenthesis the score is given after the computer's turn.

4,5 (0)
4,4 (-98)
4,3 (-98)
3,5 (-98)
3,5 (9605)
5,3 (19406)
6,7 (19406)
5,7 (9507)
7,7 (9507)
3,4 (9507)
4,6 (29403)
5,7 (19504)
3,7 (19406)
2,2 (19406)
2,2 (9507)
2,2 (9311)
1,1 (9311)
1,1 (9311)
1,1 (-490)
6,6 (94049
6,6 (9311)

It is a draw!
Moves created:7278866
Moves removed:7278866

### Alpha/Beta Algorithm
Using the Alpha/Beta algorithm, and the same simple evaluation of the board,
playing the exact game from above, the computer played the exact same game.
The number of created moves however differed greatly.

It is a draw!
Moves created:614491
Moves removed:320249

One conclusion is that I have a memory leak!
The other conclusion is that I only generate:
(614491 / 7278866) * 100 = 8.44% of the moves.
