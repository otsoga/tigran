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

    struct Position currentPosition = initialPosition;

    gameLoop(&currentPosition);

    return 0;
}

void gameLoop(struct Position * currentPosition)
{
    char * userInput;
    char turn[5];

    while(1) {
        drawBoard(currentPosition);
        strncpy(turn, currentPosition->turn  == TURN_BLACK ? "Black" : "White", 5);
        printf("%s's move: ", turn);
        userInput = getUserInput();

        if (strcmp(userInput, "quit") == 0 || strcmp(userInput, "exit") == 0) {
            free(userInput);
            break;
        }

        formatMove(userInput);

        if (!isLegalMove(userInput, currentPosition)) {
          printf("\nIllegal move, try again.\n");
          free(userInput);
          continue;
        }

        makeMove(userInput, currentPosition);
        free(userInput);
        currentPosition->turn = currentPosition->turn == WHITE ? BLACK : WHITE;
    }
}
