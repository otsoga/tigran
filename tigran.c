#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "log.h"
#include "rules.h"
#include "input.h"

int main(void)
{
    logEvent("Program Started", "");
    gameLoop();

    return 0;
}

void gameLoop()
{
    struct Position * currentPosition = calloc(1, sizeof(struct Position));
    initPosition(currentPosition);
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
            free(currentPosition);
            break;
        }

        if (strcmp(userInput, "restart") == 0 || strcmp(userInput, "exit") == 0) {
            free(userInput);
            initPosition(currentPosition);
            continue;
        }

        formatMove(userInput);

        if (!isLegalMove(userInput, currentPosition)) {
          printf("\nIllegal move, try again.\n");
          free(userInput);
          continue;
        }

        makeMove(currentPosition, userInput);
        free(userInput);
        switchTurn(currentPosition);
    }
}

void initPosition(struct Position * position)
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
        NOT_POSSIBLE,
        NOT_PROHBITED,
        NOT_PROHBITED,
    };

    copyPosition(&initialPosition, position);
}
