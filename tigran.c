#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main(void)
{
    const struct Position initialPosition = {
        {
            {WR, WP, 00, 00, 00, 00, BP, BR},
            {WN, WP, 00, 00, 00, 00, BP, BN},
            {WB, WP, 00, 00, 00, 00, BP, BB},
            {WQ, WP, 00, 00, 00, 00, BP, BQ},
            {WK, WP, 00, 00, 00, 00, BP, BK},
            {WB, WP, 00, 00, 00, 00, BP, BB},
            {WN, WP, 00, 00, 00, 00, BP, BN},
            {WR, WP, 00, 00, 00, 00, BP, BR}
        },
        WHITE
    };
    struct Position currentPosition;
    currentPosition = initialPosition;
    char * userInput;

    while(1) {
        printf("\n");
        drawBoard(currentPosition.board);
        printf("\n");
        userInput = getMove(currentPosition.turn);
        if (strcmp(userInput, "quit") == 0 || strcmp(userInput, "exit") == 0) {
            free(userInput);
            break;
        }

        formatMove(userInput);

        if (!isLegalMove(userInput, currentPosition.board, currentPosition.turn)) {
          printf("\nIllegal move, try again.\n");
          continue;
        }

        makeMove(userInput, currentPosition.board, currentPosition.turn);
        free(userInput);
        currentPosition.turn = !currentPosition.turn;
    }

    return 0;
}
