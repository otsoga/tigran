#include <stdio.h>
#include "functions.h"

int main(void)
{
    int to[2];
    int from[2];
    int board[8][8] = {
        {WR, WN, WB, WQ, WK, WB, WN, WR},
        {WP, WP, WP, WP, WP, WP, WP, WP},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {BP, BP, BP, BP, BP, BP, BP, BP},
        {BR, BN, BB, BQ, BK, BB, BN, BR}
    };
    
    makeMove("e2-e4", board, WHITE);
    makeMove("e7-e5", board, BLACK);
    makeMove("g1-f3", board, WHITE);
    makeMove("b8-c6", board, BLACK);
    makeMove("f1-b5", board, WHITE);
    makeMove("d7-d6", board, BLACK);
    makeMove("0-0", board, WHITE);
    makeMove("f8-e7", board, BLACK);
    makeMove("f1-e1", board, WHITE);
    makeMove("g8-f6", board, BLACK);
    makeMove("c2-c3", board, WHITE);
    makeMove("0-0", board, BLACK);

    drawBoard(board);

    return 0;
}

