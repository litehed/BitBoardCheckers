#include "bitops.h"

#define RED "\033[0;31m"
#define BLACK "\033[0;30m"
#define NONE "\033[0m"

typedef struct {
    unsigned long long player1_pieces;
    unsigned long long player1_kings;
    unsigned long long player2_pieces;
    unsigned long long player2_kings;
    int current_turn;
} Game;

typedef unsigned long long Board;

void PrintBoardSimplified(Game game);
void PrintBoard(Game game);

int MovePiece(Game* game, char* from, char* to);
int CheckMovement(Game* game, int from, int to);
