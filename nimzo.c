#include <stdio.h>
#include "functions.h"

int main(void)
{
    int to[2];
    int from[2];
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
    
//    makeMove("e2-e4", currentPosition.board, currentPosition.turn);
//    makeMove("e7-e5", board, BLACK);
//    makeMove("g1-f3", board, WHITE);
//    makeMove("b8-c6", board, BLACK);
//    makeMove("f1-b5", board, WHITE);
//    makeMove("d7-d6", board, BLACK);
//    makeMove("0-0", board, WHITE);
//    makeMove("f8-e7", board, BLACK);
//    makeMove("f1-e1", board, WHITE);
//    makeMove("g8-f6", board, BLACK);
//    makeMove("c2-c3", board, WHITE);
//    makeMove("0-0", board, BLACK);

    drawBoard(currentPosition.board);
    printf("\n");
    drawBoard((int (*)[8])initialPosition.board);
    
    return 0;
}

