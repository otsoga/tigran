#include <stdio.h>
#include "functions.h"
#include "position.h"

void initPosition(struct Position * position)
{
    struct Position initialPosition = {
        // I think this structure would lead to a more intuitive program,
        // but my code elsewhere is based on the other structure
        // {
        //     {WR, WN, WB, WQ, WK, WB, WN, WR},
        //     {WP, WP, WP, WP, WP, WP, WP, WP},
        //     {00, 00, 00, 00, 00, 00, 00, 00},
        //     {00, 00, 00, 00, 00, 00, 00, 00},
        //     {00, 00, 00, 00, 00, 00, 00, 00},
        //     {00, 00, 00, 00, 00, 00, 00, 00},
        //     {BP, BP, BP, BP, BP, BP, BP, BP},
        //     {BR, BN, BB, BQ, BK, BB, BN, BR},
        // },
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
        WHITE, // turn
        NONE, // enPassant File
        ALLOWED, // whiteKingsideCastleStatus
        ALLOWED, // blackKingsideCastleStatus
        ALLOWED, // whiteQueensideCastleStatus
        ALLOWED // blackQueensideCastleStatus
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
    destinationPosition->whiteKingsideCastleStatus = sourcePosition->whiteKingsideCastleStatus;
    destinationPosition->whiteQueensideCastleStatus = sourcePosition->whiteQueensideCastleStatus;
    destinationPosition->blackKingsideCastleStatus = sourcePosition->blackKingsideCastleStatus;
    destinationPosition->blackQueensideCastleStatus = sourcePosition->blackQueensideCastleStatus;
}

void switchTurn(struct Position * currentPosition)
{
    currentPosition->turn = currentPosition->turn == WHITE ? BLACK : WHITE;
}

/* Returns occupant of a AN square */
// int getSquareOccupant(struct Position * currentPosition, char * square)
// {
//     // subracting by 'a' and '1' because of zero-indexed arrays
//     int file = (int) square[0] - 'a';
//     int rank = (int) square[1] - '1';
//     // printf("file: %d, rank: %d\n", file, rank);

//     return currentPosition->board[file][rank];
// }

int getSquareOccupant(struct Position * currentPosition, char * square)
{
    // subracting by 'a' and '1' because of zero-indexed arrays
    int rank = (int) square[0] - 'a';
    int file = (int) square[1] - '1';
    // printf("file: %d, rank: %d\n", file, rank);

    return currentPosition->board[rank][file];
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