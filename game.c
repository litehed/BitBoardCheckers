#include "game.h"

void PrintBoardSimplified(Game game) {
    // Loops through each bit of the ULongLong and prints piece positions as Os
    // and empty squares as dots
    for (int i = 63; i >= 0; i--) {
        Board mask = 1ULL << i;
        if (game.player1_pieces & mask) {
            printf(RED "o" NONE);  // regular red
        } else if (game.player1_kings & mask) {
            printf(RED_BOLD "O" NONE);  // king red
        } else if (game.player2_pieces & mask) {
            printf(BLACK "o" NONE);  // regular black
        } else if (game.player2_kings & mask) {
            printf(BLACK_BOLD "O" NONE);  // king black
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
            printf(RED_BOLD "O " NONE);  // king red
        } else if (game.player2_pieces & mask) {
            printf(BLACK "o " NONE);  // regular black
        } else if (game.player2_kings & mask) {
            printf(BLACK_BOLD "O " NONE);  // king black
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
    // move_type: 0 = invalid, 1 = normal, 2 = jump
    if (move_type == 1) {
        // Do a normal move depending on turn and piece type (king or normal)
        // Finally check if the piece can be made into a king after movement
        if (game->current_turn == 1) {
            if (GetBitLL(game->player1_pieces, from_pos)) {
                game->player1_pieces =
                    ClearBitLL(game->player1_pieces, from_pos);
                game->player1_pieces = SetBitLL(game->player1_pieces, to_pos);
            } else {
                game->player1_kings = ClearBitLL(game->player1_kings, from_pos);
                game->player1_kings = SetBitLL(game->player1_kings, to_pos);
            }
        } else {
            if (GetBitLL(game->player2_pieces, from_pos)) {
                game->player2_pieces =
                    ClearBitLL(game->player2_pieces, from_pos);
                game->player2_pieces = SetBitLL(game->player2_pieces, to_pos);
            } else {
                game->player2_kings = ClearBitLL(game->player2_kings, from_pos);
                game->player2_kings = SetBitLL(game->player2_kings, to_pos);
            }
        }
        MakeKing(game, to_pos);
        printf("Player %d successfully moved from %s to %s\n\n",
               game->current_turn, from, to);
    } else if (move_type == 2) {
        // Jump move
        // Gets the jumped position by averaging from and to positions
        int jumped_pos = (from_pos + to_pos) / 2;
        // Just as before get the turn and the piece type to determine possible
        // moves and make king
        if (game->current_turn == 1) {
            if (GetBitLL(game->player1_pieces, from_pos)) {
                game->player1_pieces =
                    ClearBitLL(game->player1_pieces, from_pos);
                game->player1_pieces = SetBitLL(game->player1_pieces, to_pos);
            } else {
                game->player1_kings = ClearBitLL(game->player1_kings, from_pos);
                game->player1_kings = SetBitLL(game->player1_kings, to_pos);
            }
            // Capture
            game->player2_pieces = ClearBitLL(game->player2_pieces, jumped_pos);
            game->player2_kings = ClearBitLL(game->player2_kings, jumped_pos);
        } else {
            if (GetBitLL(game->player2_pieces, from_pos)) {
                game->player2_pieces =
                    ClearBitLL(game->player2_pieces, from_pos);
                game->player2_pieces = SetBitLL(game->player2_pieces, to_pos);
            } else {
                game->player2_kings = ClearBitLL(game->player2_kings, from_pos);
                game->player2_kings = SetBitLL(game->player2_kings, to_pos);
            }
            // Capture
            game->player1_pieces = ClearBitLL(game->player1_pieces, jumped_pos);
            game->player1_kings = ClearBitLL(game->player1_kings, jumped_pos);
        }
        MakeKing(game, to_pos);
        printf(
            "Player %d jumped from %s to %s and captured player %d's "
            "piece!\n\n",
            game->current_turn, from, to, game->current_turn == 1 ? 2 : 1);
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
    // Converts board position like A1 to index 0-63
    return (pos[1] - '1') * 8 + (7 - (pos[0] - 'A'));
}

int CheckMovement(Game* game, int from, int to) {
    // First get the piece type using the from position and init move and jump
    // positions
    int piece_type = GetSpotPiece(game, from);
    int move_pos = 0;
    int jump_pos = 0;
    // Determine possible move and jump positions based on piece type king or
    // normal
    if (piece_type == 2 || piece_type == 4) {
        move_pos = (to == from + 7 || to == from + 9) ||
                   (to == from - 7 || to == from - 9);
        jump_pos = (to == from + 14 || to == from + 18) ||
                   (to == from - 14 || to == from - 18);
    }
    // Now I check movement based on current turn
    if (game->current_turn == 1) {
        // Player 1 moves up the board
        if (to == from + 7 || to == from + 9 || move_pos) {
            if (GetSpotPiece(game, to) != 0) {
                return 0;
            }
            return 1;  // Valid
        } else if (to == from + 14 || to == from + 18 || jump_pos) {
            // Player 1 jumps up the board
            int spot_piece = GetSpotPiece(game, to);
            int middle = (from + to) / 2;
            if (spot_piece != 0) {
                return 0;
            }

            // Check if the middle piece is opponent's
            if (GetSpotPiece(game, middle) == 3 ||
                GetSpotPiece(game, middle) == 4) {
                return 2;
            }
            return 2;  // Take
        } else {
            return 0;  // Invalid
        }
    } else {
        // Player 2 moves down the board (to lower indices)
        if (to == from - 7 || to == from - 9 || move_pos) {
            if (GetSpotPiece(game, to) != 0) {
                return 0;
            }
            return 1;
        } else if (to == from - 14 || to == from - 18 || jump_pos) {
            // Player 2 jumps down the board
            int spot_piece = GetSpotPiece(game, to);
            int middle = (from + to) / 2;
            if (spot_piece != 0) {
                return 0;
            }
            // Check if the middle piece is opponent's
            if (GetSpotPiece(game, middle) == 1 ||
                GetSpotPiece(game, middle) == 2) {
                return 2;
            }

            return 0;
        } else {
            return 0;
        }
    }
}

int GetSpotPiece(Game* game, int position) {
    Board mask = 1ULL << position;
    if (game->player1_pieces & mask) {
        return 1;  // Player 1 piece
    } else if (game->player1_kings & mask) {
        return 2;  // Player 1 king
    } else if (game->player2_pieces & mask) {
        return 3;  // Player 2 piece
    } else if (game->player2_kings & mask) {
        return 4;  // Player 2 king
    }
    return 0;
}

void MakeKing(Game* game, int position) {
    // Check if the piece reached the opposite end to become a king
    if (game->current_turn == 1 && position >= 56) {
        game->player1_pieces = ClearBitLL(game->player1_pieces, position);
        game->player1_kings = SetBitLL(game->player1_kings, position);
    } else if (game->current_turn == 2 && position < 8) {
        game->player2_pieces = ClearBitLL(game->player2_pieces, position);
        game->player2_kings = SetBitLL(game->player2_kings, position);
    }
}

int HasLegalMoves(Game* game, int player) {
    unsigned long long pieces, kings, opponent_pieces, opponent_kings;
    int direction;

    // Set up variables based on the current player for easy access
    if (player == 1) {
        pieces = game->player1_pieces;
        kings = game->player1_kings;
        opponent_pieces = game->player2_pieces;
        opponent_kings = game->player2_kings;
        direction = 1;
    } else {
        pieces = game->player2_pieces;
        kings = game->player2_kings;
        opponent_pieces = game->player1_pieces;
        opponent_kings = game->player1_kings;
        direction = -1;
    }

    // Check each piece for possible moves
    for (int i = 0; i < 64; i++) {
        Board mask = 1ULL << i;
        // If there's a piece at this position movement will be checked
        if (pieces & mask) {
            int from_pos = i;

            // Check normal moves by calculating target positions as well as
            // possible blocks by other pieces
            int move_offsets[] = {7 * direction, 9 * direction};
            for (int j = 0; j < 2; j++) {
                int to_pos = from_pos + move_offsets[j];
                if (to_pos >= 0 && to_pos < 64) {
                    if (GetSpotPiece(game, to_pos) == 0) {
                        return 1;  // Found a possible move
                    }
                }
            }

            // Check jump moves
            int jump_offsets[] = {14 * direction, 18 * direction};
            // Check each jump move by ensuring the landing spot is empty and
            // the jumped piece belongs to the opponent
            for (int j = 0; j < 2; j++) {
                int to_pos = from_pos + jump_offsets[j];
                int middle_pos = from_pos + (jump_offsets[j] / 2);
                if (to_pos >= 0 && to_pos < 64) {
                    if (GetSpotPiece(game, to_pos) == 0) {
                        int middle_piece = GetSpotPiece(game, middle_pos);
                        // Checking if the middle piece belongs to the opponent
                        if ((player == 1 &&
                             (middle_piece == 3 || middle_piece == 4)) ||
                            (player == 2 &&
                             (middle_piece == 1 || middle_piece == 2))) {
                            return 1;  // Found a possible jump move
                        }
                    }
                }
            }
        }
        // Check king moves
        if (kings & mask) {
            int from_pos = i;

            // Check normal moves for kings
            int move_offsets[] = {7, 9, -7, -9};
            for (int j = 0; j < 4; j++) {
                int to_pos = from_pos + move_offsets[j];
                if (to_pos >= 0 && to_pos < 64) {
                    if (GetSpotPiece(game, to_pos) == 0) {
                        return 1;  // Found a possible move
                    }
                }
            }

            // Check jump moves for kings
            int jump_offsets[] = {14, 18, -14, -18};
            for (int j = 0; j < 4; j++) {
                int to_pos = from_pos + jump_offsets[j];
                int middle_pos = from_pos + (jump_offsets[j] / 2);
                if (to_pos >= 0 && to_pos < 64) {
                    if (GetSpotPiece(game, to_pos) == 0) {
                        int middle_piece = GetSpotPiece(game, middle_pos);
                        if ((player == 1 &&
                             (middle_piece == 3 || middle_piece == 4)) ||
                            (player == 2 &&
                             (middle_piece == 1 || middle_piece == 2))) {
                            return 1;  // Found a possible jump move
                        }
                    }
                }
            }
        }
    }
    return 0;
}