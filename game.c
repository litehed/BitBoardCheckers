#include "game.h"

void PrintBoardSimplified(Game game) {
    for (int i = 63; i >= 0; i--) {
        Board mask = 1ULL << i;
        if (game.player1_pieces & mask) {
            printf(RED "o" NONE);  // regular red
        } else if (game.player1_kings & mask) {
            printf(RED "O" NONE);  // king red
        } else if (game.player2_pieces & mask) {
            printf(BLACK "o" NONE);  // regular black
        } else if (game.player2_kings & mask) {
            printf(BLACK "O" NONE);  // king black
        } else {
            printf(".");  // empty square
        }

        if (i % 8 == 0) {
            printf("\n");
        }
    }
}

void PrintBoard(Game game) {
    // Draw column letters
    printf("  A B C D E F G H\n");
    for (int i = 63; i >= 0; i--) {
        // Mask to isolate the bit at position i
        Board mask = 1ULL << i;
        // Draw row numbers
        if (i % 8 == 7) {
            printf("%d ", (i / 8) + 1);
        }

        // Draw pieces and spaces
        if (game.player1_pieces & mask) {
            printf(RED "o " NONE);  // regular red
        } else if (game.player1_kings & mask) {
            printf(RED "O " NONE);  // king red
        } else if (game.player2_pieces & mask) {
            printf(BLACK "o " NONE);  // regular black
        } else if (game.player2_kings & mask) {
            printf(BLACK "O " NONE);  // king black
        } else {
            printf(". ");  // empty square
        }

        // New line at the end of each row
        if (i % 8 == 0) {
            printf("\n");
        }
    }
}

int MovePiece(Game* game, char* from, char* to) {
    // This took forever to figure out
    // Convert 'A'-'H' and '1'-'8' to 0-63 index
    // While remembering A1 is bottom left, H8 is top right
    int from_pos = BoardToIndex(from);
    int to_pos = BoardToIndex(to);
    int move_type = CheckMovement(game, from_pos, to_pos);
    if (move_type == 1) {
        if (game->current_turn == 1) {
            game->player1_pieces = ClearBitLL(game->player1_pieces, from_pos);
            game->player1_pieces = SetBitLL(game->player1_pieces, to_pos);
        } else {
            game->player2_pieces = ClearBitLL(game->player2_pieces, from_pos);
            game->player2_pieces = SetBitLL(game->player2_pieces, to_pos);
        }
        printf("Player %d successfully moved from %s to %s\n",
               game->current_turn, from, to);
    } else if (move_type == 2) {
        // Jump move
        int jumped_pos = (from_pos + to_pos) / 2;
        if (game->current_turn == 1) {
            game->player1_pieces = ClearBitLL(game->player1_pieces, from_pos);
            game->player1_pieces = SetBitLL(game->player1_pieces, to_pos);
            game->player2_pieces = ClearBitLL(game->player2_pieces, jumped_pos);
        } else {
            game->player2_pieces = ClearBitLL(game->player2_pieces, from_pos);
            game->player2_pieces = SetBitLL(game->player2_pieces, to_pos);
            game->player1_pieces = ClearBitLL(game->player1_pieces, jumped_pos);
        }
        printf(
            "Player %d jumped from %s to %s and captured an opponent's "
            "piece!\n",
            game->current_turn, from, to);
    } else {
        printf("Invalid move from %s to %s. Try again.\n\n", from, to);
        printf("--------------------------------------------------\n\n");
        return 0;
    }

    // printf("Moving from %d to %d\n\n", from_pos, to_pos);
    printf("--------------------------------------------------\n\n");
    return 1;
}

// H1 = 0, A8 = 63
int BoardToIndex(char* pos) {
    return (pos[1] - '1') * 8 + (7 - (pos[0] - 'A'));
}

int CheckMovement(Game* game, int from, int to) {
    if (game->current_turn == 1) {
        if (to == from + 7 || to == from + 9) {
            return 1;  // Valid
        } else if (to == from + 14 || to == from + 18) {
            return 2;  // Take
        } else {
            return 0;  // Invalid
        }
    } else {
        // Player 2 moves down the board (to lower indices)
        if (to == from - 7 || to == from - 9) {
            return 1;
        } else if (to == from - 14 || to == from - 18) {
            return 2;
        } else {
            return 0;
        }
    }
}