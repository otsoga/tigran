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

/* Returns occupant of a AN square */
int getSquareOccupant(char * square, struct Position * currentPosition)
{
    // subracting by 'a' and '1' because of zero-indexed arrays
    int file = (int) square[0] - 'a';
    int rank = (int) square[1] - '1';
    // printf("file: %d, rank: %d\n", file, rank);

    return currentPosition->board[file][rank];
}

int getOccupantColor(int occupant)
{
    if (occupant < WK || occupant > BP) { return 0; }
    if (occupant >= WK && occupant <= WP) { return WHITE; }
    if (occupant >= BK && occupant <= BP) { return BLACK; }
}

int getOccupantPieceType(int occupant)
{
    return occupant > WP ? occupant - WP : occupant;
}

int isFile(char character)
{
    return (character >= 'a' && character <= 'h') ? 1 : 0;
}

int isRank(char character)
{
    return (character >= '1' && character <= '8') ? 1 : 0;
}