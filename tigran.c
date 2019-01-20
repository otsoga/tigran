#include <stdio.h>
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
    
    makeMove("e2-e4", currentPosition.board, currentPosition.turn);
    makeMove("e7-e5", currentPosition.board, BLACK);
    makeMove("g1-f3", currentPosition.board, WHITE);
    makeMove("b8-c6", currentPosition.board, BLACK);
    makeMove("f1-b5", currentPosition.board, WHITE);
    makeMove("d7-d6", currentPosition.board, BLACK);
    makeMove("0-0", currentPosition.board, WHITE);
    makeMove("f8-e7", currentPosition.board, BLACK);
    makeMove("f1-e1", currentPosition.board, WHITE);
    makeMove("g8-f6", currentPosition.board, BLACK);
    makeMove("c2-c3", currentPosition.board, WHITE);
    makeMove("0-0", currentPosition.board, BLACK);

    drawBoard(currentPosition.board);
    printf("\n");
    currentPosition = initialPosition;
    drawBoard(currentPosition.board);
    
    return 0;
}

