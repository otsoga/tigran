#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "log.h"
#include "rules.h"

int main(void)
{
    struct Position initialPosition = {
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
        WHITE,
        NOT_POSSIBLE
    };

    struct Position * currentPosition = calloc(1, sizeof(struct Position));
    copyPosition(&initialPosition, currentPosition);

    gameLoop(&initialPosition, currentPosition);
    free(currentPosition);

    return 0;
}

void gameLoop(struct Position * initialPosition, struct Position * currentPosition)
{
    char * userInput;
    char turn[6];

    logEvent("New Game Started", "");
    while(1) {
        drawBoard(currentPosition);
        strncpy(turn, currentPosition->turn  == TURN_BLACK ? "Black" : "White", 6);
        printf("Legal moves for %s: \n", turn);
        // displayLegalMoves(currentPosition);
        printf("%s's move: ", turn);
        userInput = getUserInput();

        if (strcmp(userInput, "quit") == 0 || strcmp(userInput, "exit") == 0) {
            free(userInput);
            break;
        }

        if (strcmp(userInput, "restart") == 0 || strcmp(userInput, "exit") == 0) {
            free(userInput);
            copyPosition(initialPosition, currentPosition);
            continue;
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
