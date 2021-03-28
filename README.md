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
the computer played the following game against another program.
In parenthesis the score is given after the computer's turn.

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

### Alpha/Beta Algorithm
Using the Alpha/Beta algorithm, and the same simple evaluation of the board,
playing the exact game from above, the computer played the exact same game.
The number of evaluated positions differed greatly.

Positions evaluated:218901
user    0m0,337s

Alpha/Beta only generates: (218901 / 5715791) * 100 = 3.83% of the moves.
Using only: (0.337 / 5.244) * 100  = 6.43% of the time.


