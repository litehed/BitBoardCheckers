#include <stdio.h>
#include <string.h>

#include "game.h"

int validInput(char *input);

int main() {
    char from[5];
    char to[5];
    int running = 1;
    Game game = {
        .player1_pieces = 0x00000000000AA55AAULL,  // Bottom 3 rows (rows 0–2)
        .player2_pieces = 0x55AA550000000000ULL,   // Top 3 rows (rows 5–7)
        .player1_kings = 0,
        .player2_kings = 0,
        .current_turn = 1};

    printf("Type: 'quit' or 'exit' to end the game\n\n");

    while (running) {
        PrintBoard(game);

        printf("Player %d's turn\n", game.current_turn);
        do {
            printf("Enter piece to move (e.g., A3): ");
            fgets(from, sizeof(from), stdin);
            from[0] = toupper(from[0]);
            from[strcspn(from, "\n")] = '\0';
        } while (!validInput(from) && strcmp(from, "quit") != 0 &&
                 strcmp(from, "exit") != 0);

        if (checkExit(from, &running)) continue;
        if (game.current_turn == 1) {
            if (!GetBitLL(game.player1_pieces, BoardToIndex(from))) {
                printf("No piece at %s. Try again.\n\n", from);
                continue;
            }
        } else {
            if (!GetBitLL(game.player2_pieces, BoardToIndex(from))) {
                printf("No piece at %s. Try again.\n\n", from);
                continue;
            }
        }
        do {
            printf("Enter destination (e.g., B4): ");
            fgets(to, sizeof(to), stdin);
            to[0] = toupper(to[0]);
            to[strcspn(to, "\n")] = '\0';
        } while (!validInput(to) && strcmp(to, "quit") != 0 &&
                 strcmp(to, "exit") != 0);

        if (checkExit(to, &running)) continue;
        // Current turn alternates between 1 and 2
        int move_success = MovePiece(&game, from, to);

        if (running && move_success) {
            game.current_turn = 3 - game.current_turn;
        }
    }

    return 0;
}

int validInput(char *input) {
    if (strlen(input) != 2) return 0;
    if (input[0] < 'A' || input[0] > 'H') return 0;
    if (input[1] < '1' || input[1] > '8') return 0;
    return 1;
}

int checkExit(char *input, int *running) {
    if (strcmp(input, "quit") == 0 || strcmp(input, "exit") == 0) {
        *running = 0;
        printf("\nThanks for playing!\n");
        return 1;
    }
    return 0;
}