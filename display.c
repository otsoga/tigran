#include <stdio.h>
#include "functions.h"

// TODO: these draw functions should be placed in a new display.c
void drawBoard(struct Position * currentPosition)
{
    printf("\n");

    for (int i = 7; i > -1; i--) {
        for(int j = 0; j < 8; j++) {
            drawSquare(currentPosition->board[j][i]);
        }
        printf("\n");
    }

    printf("\n");
}

void drawSquare(int value)
{
    char piece[13];
    piece[WK] = 'K';
    piece[WQ] = 'Q';
    piece[WR] = 'R';
    piece[WB] = 'B';
    piece[WN] = 'N';
    piece[WP] = 'P';
    piece[BK] = 'k';
    piece[BQ] = 'q';
    piece[BR] = 'r';
    piece[BB] = 'b';
    piece[BN] = 'n';
    piece[BP] = 'p';
    piece[0]  = '.';

    printf("%c", piece[value]);
}

void displayLegalMoves(struct Position * currentPosition)
{
    struct CandidateMoveList * move = getLegalMoves(currentPosition);
    printf("Moves: %s", move->move );
}