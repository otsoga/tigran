#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "log.h"
#include "rules.h"
#include "input.h"
#include "position.h"

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

    logEvent("New Game Started", "");
    while(1) {
        displayInterface(currentPosition);

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

        sanitizeMove(userInput);

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


