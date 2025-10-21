#include "bitops.h"

// Color codes for terminal output
#define RED "\033[0;31m"
#define RED_BOLD "\033[1;31m"   // I cant tell if this works or not
#define BLACK "\033[0;30m"
#define BLACK_BOLD "\033[1;30m"
#define NONE "\033[0m"

// Game structure definition
typedef struct {
    unsigned long long player1_pieces;
    unsigned long long player1_kings;
    unsigned long long player2_pieces;
    unsigned long long player2_kings;
    int current_turn;
} Game;

typedef unsigned long long Board; // 64-bit board representation

void PrintBoardSimplified(Game game); // Prints a simplified version of the game board
void PrintBoard(Game game); // Prints the game board to the console

int MovePiece(Game* game, char* from, char* to); // Moves a piece from one position to another
int CheckMovement(Game* game, int from, int to); // Checks if a movement from 'from' to 'to' is valid
int BoardToIndex(char* position); // Converts board position (B1) to an index
int GetSpotPiece(Game* game, int position); // Gets the piece type at a given position
void MakeKing(Game* game, int position); // Makes a piece a king at a given position

int HasLegalMoves(Game* game, int player); // Checks if the specified player has any legal moves left
