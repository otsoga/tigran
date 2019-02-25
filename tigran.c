#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main(void)
{
    const struct Position initialPosition = {
        {
            {WR, WN, WB, WQ, WK, WB, WN, WR},
            {WP, WP, WP, WP, WP, WP, WP, WP},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {BP, BP, BP, BP, BP, BP, BP, BP},
            {BR, BN, BB, BQ, BK, BB, BN, BR}
        }, 
        WHITE
    };
    struct Position currentPosition;
    currentPosition = initialPosition;
    char userInput[USER_INPUT_LENGTH];
    
    while(1) {
        printf("\n");
        drawBoard(currentPosition.board);
        printf("\n");
        strcpy(userInput, getMove(currentPosition.turn));

        if (strcmp(userInput, "quit\n") == 0 || strcmp(userInput, "exit\n") == 0) { 
            break;
        }

        if (isLegalMove(userInput, currentPosition.board, currentPosition.turn)) {
            makeMove(userInput, currentPosition.board, currentPosition.turn);
        }

        currentPosition.turn = !currentPosition.turn;
    }

    return 0;
}

