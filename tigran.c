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
            {00, 00, 00, 00, 00, 00, 00, 00},
            {00, 00, 00, 00, 00, 00, 00, 00},
            {00, 00, 00, 00, 00, 00, 00, 00},
            {00, 00, 00, 00, 00, 00, 00, 00},
            {BP, BP, BP, BP, BP, BP, BP, BP},
            {BR, BN, BB, BQ, BK, BB, BN, BR}
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

        if (isLegalMove(userInput, currentPosition.board, currentPosition.turn)) {
            makeMove(userInput, currentPosition.board, currentPosition.turn);
        }

        free(userInput);
        currentPosition.turn = !currentPosition.turn;
    }

    return 0;
}

