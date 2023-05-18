#include <stdio.h>
#include "functions.h"

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