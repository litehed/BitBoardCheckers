#include <stdio.h>
#include <string.h>

#include "game.h"

int ValidInput(char* input);               // Validates board position input
int CheckExit(char* input, int* running);  // Checks for exit commands

int main() {
    char from[5];
    char to[5];
    int running = 1;
    Game game = {
        .player1_pieces = 0x00000000000AA55AAULL,  // Bottom 3 rows (rows 0-2)
        .player2_pieces = 0x55AA550000000000ULL,   // Top 3 rows (rows 5-7)
        .player1_kings = 0,
        .player2_kings = 0,
        .current_turn = 1};

    printf("Type: 'quit' or 'exit' to end the game\n\n");

    while (running) {
        PrintBoard(game);

        // Prints the current player's turn and prompts for a piece to move
        printf("Player %d's turn\n", game.current_turn);
        do {
            printf("Enter piece to move (e.g., A3): ");
            fgets(from, sizeof(from), stdin);
            from[0] = toupper(from[0]);
            from[strcspn(from, "\n")] = '\0';
        } while (!ValidInput(from) && strcmp(from, "quit") != 0 &&
                 strcmp(from, "exit") != 0);

        if (CheckExit(from, &running)) continue;

        int from_pos = BoardToIndex(from);
        int piece_type = GetSpotPiece(&game, from_pos);

        // Validate that the selected piece belongs to the current player and if
        // it even exists
        if (game.current_turn == 1) {
            if (piece_type != 1 && piece_type != 2) {
                printf("No piece at %s. Try again.\n\n", from);
                printf(
                    "--------------------------------------------------\n\n");
                continue;
            }
        } else {
            if (piece_type != 3 && piece_type != 4) {
                printf("No piece at %s. Try again.\n\n", from);
                printf(
                    "--------------------------------------------------\n\n");
                continue;
            }
        }

        // Prompts the player for the destination position
        do {
            printf("Enter destination (e.g., B4): ");
            fgets(to, sizeof(to), stdin);
            to[0] = toupper(to[0]);
            to[strcspn(to, "\n")] = '\0';
        } while (!ValidInput(to) && strcmp(to, "quit") != 0 &&
                 strcmp(to, "exit") != 0);

        if (CheckExit(to, &running)) continue;
        // Attempts to move the piece and checks for game over conditions
        int move_success = MovePiece(&game, from, to);
        // Win conditions
        int p1_total =
            CountBitsLL(game.player1_pieces) + CountBitsLL(game.player1_kings);
        int p2_total =
            CountBitsLL(game.player2_pieces) + CountBitsLL(game.player2_kings);
        // Checks for pieces left
        if (p1_total == 0 || p2_total == 0) {
            printf("Game Over! Player %d Wins!!! :)\n", game.current_turn);
            running = 0;
        }
        // Checks for legal moves
        if (!HasLegalMoves(&game, game.current_turn)) {
            printf("Player %d is out of moves.\n", game.current_turn);
            printf("Game Over! Player %d Wins!!! :)\n", 3 - game.current_turn);
            running = 0;
        }

        // Current turn alternates between 1 and 2
        if (running && move_success) {
            game.current_turn = 3 - game.current_turn;
        }
    }

    return 0;
}

int ValidInput(char* input) {
    // Valid inputs are in the format LetterNumber (A1 to H8)
    if (strlen(input) != 2) return 0;
    if (input[0] < 'A' || input[0] > 'H') return 0;
    if (input[1] < '1' || input[1] > '8') return 0;
    return 1;
}

int CheckExit(char* input, int* running) {
    // Checks for quit or exit to end the game
    if (strcmp(input, "quit") == 0 || strcmp(input, "exit") == 0) {
        *running = 0;
        printf("\nThanks for playing!\n");
        return 1;
    }
    return 0;
}