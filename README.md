# CS 3503 Project 1 - BitBoard Checkers Game

## Author
[ Ethan Leitner ]

## Description
A game of checkers represented by bitboards in C

## Build Instructions
```bash
cl.exe /Zi /EHsc /Fe: checkers.exe main.c, bitops.c, game.c
./checkers
```

## How to Play
1. After building and launching checkers.exe a board will show up that looks like the following (It will have color on the pieces in the terminal)
```bash
  A B C D E F G H
8 . o . o . o . o
7 o . o . o . o .
6 . o . o . o . o
5 . . . . . . . .
4 . . . . . . . .
3 o . o . o . o .
2 . o . o . o . o
1 o . o . o . o .
Player x's turn
```
2. The user will be prompted to enter the location of the piece they want to move. This will be in the form of A1-H8. For example A3. (Case doesnt matter but it will not be accepted in forms like 3A or A 3).

3. Then the user will be prompted to enter a destination this will work as the same as above. 

4. If their positions are valid the board will be reprinted with updated values and the turn will switch to the next players.

5. The game can end early if a player types quit or exit. It can also end if a player wins by making the opponent have no availble moves or capturing all of their pieces.

## Example Play
```bash
.\checkers.exe
Type: 'quit' or 'exit' to end the game

  A B C D E F G H
8 . o . o . o . o
7 o . o . o . o .
6 . o . o . o . o
5 . . . . . . . .
4 . . . . . . . .
3 o . o . o . o .
2 . o . o . o . o
1 o . o . o . o .
Player 1's turn
Enter piece to move (e.g., A3): A3
Enter destination (e.g., B4): B4
Player 1 successfully moved from A3 to B4

--------------------------------------------------

  A B C D E F G H
8 . o . o . o . o 
7 o . o . o . o . 
6 . o . o . o . o 
5 . . . . . . . . 
4 . o . . . . . .
3 . . o . o . o .
2 . o . o . o . o
1 o . o . o . o .
Player 2's turn
Enter piece to move (e.g., A3): D6
Enter destination (e.g., B4): C5
Player 2 successfully moved from D6 to C5

--------------------------------------------------

  A B C D E F G H
8 . o . o . o . o
7 o . o . o . o .
6 . o . . . o . o
5 . . o . . . . .
4 . o . . . . . .
3 . . o . o . o .
2 . o . o . o . o
1 o . o . o . o .
Player 1's turn
Enter piece to move (e.g., A3): B4
Enter destination (e.g., B4): C5
Invalid move from B4 to C5. Try again.

--------------------------------------------------

  A B C D E F G H
8 . o . o . o . o
7 o . o . o . o .
6 . o . . . o . o
5 . . o . . . . .
4 . o . . . . . .
3 . . o . o . o .
2 . o . o . o . o
1 o . o . o . o .
Player 1's turn
Enter piece to move (e.g., A3): B4
Enter destination (e.g., B4): D6
Player 1 jumped from B4 to D6 and captured player 2's piece!

--------------------------------------------------

  A B C D E F G H
8 . o . o . o . o
7 o . o . o . o .
6 . o . o . o . o
5 . . . . . . . .
4 . . . . . . . .
3 . . o . o . o .
2 . o . o . o . o
1 o . o . o . o .
Player 2's turn
Enter piece to move (e.g., A3):
```