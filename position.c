#include <stdio.h>
#include "functions.h"
#include "position.h"

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

void copyPosition(struct Position * sourcePosition, struct Position * destinationPosition)
{
    for (int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            destinationPosition->board[i][j] = sourcePosition->board[i][j];
        }
    }

    destinationPosition->turn = sourcePosition->turn;
    destinationPosition->enPassantFile = sourcePosition->enPassantFile;
    destinationPosition->kingsideCastleStatus = sourcePosition->kingsideCastleStatus;
    destinationPosition->queensideCastleStatus = sourcePosition->queensideCastleStatus;
}

void switchTurn(struct Position * currentPosition)
{
    currentPosition->turn = currentPosition->turn == WHITE ? BLACK : WHITE;
}

/* Returns occupant of a AN square */
int getSquareOccupant(struct Position * currentPosition, char * square)
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