#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

int isLegalMove(char * move, struct Position * currentPosition)
{
    if (strcmp(move, "0-0") == 0 || strcmp(move, "0-0-0") == 0) { return 1; }
    int isValidFromSquare = isFile(move[FROM_FILE]) && isRank(move[FROM_RANK]);
    int isValidToSquare = isFile(move[TO_FILE]) && isRank(move[TO_RANK]);
    if (!isValidFromSquare || !isValidToSquare) { return 0; }
    int fromSquareOccupant = getSquareOccupant(move, currentPosition);
    int toSquareOccupant = getSquareOccupant(&move[3], currentPosition);
    if (getOccupantColor(fromSquareOccupant) != currentPosition->turn) { return 0; }
    if (getOccupantColor(toSquareOccupant) == currentPosition->turn) { return 0; }
    if (!isLegalMoveForPiece(move, currentPosition)) { return 0; }
    return 1;
}

int isLegalMoveForPiece(char * move, struct Position * currentPosition)
{
    int piece = getSquareOccupant(move, currentPosition);

    switch(getOccupantPieceType(piece)) {
        case PAWN:
            return isLegalMoveForPawn(move, currentPosition);
        default:
            return 1;
    }
}

int isLegalMoveForPawn(char * move, struct Position * currentPosition)
{
    if (currentPosition->turn == WHITE) {
        int rankDiff = move[TO_RANK] - move[FROM_RANK];
        if (rankDiff > 2 || rankDiff < 1) { return 0; } 
        int notOnSecondRank = (int) move[FROM_RANK] - '0' != 2;
        if (notOnSecondRank && rankDiff == 2) { return 0; } 
        int fileDiff = abs(move[TO_FILE] - move[FROM_FILE]);
        if (fileDiff > 1) { return 0; }
        int pieceDiagonallyAdjacent = fileDiff == 1 && rankDiff == 1;
        int toSquareOccupant = getSquareOccupant(&move[3], currentPosition);
        printf("occupant: %d\n", toSquareOccupant);
        if (pieceDiagonallyAdjacent && !toSquareOccupant) { return 0; }
        char squareInFrontOfPawn[] = {move[FROM_FILE], move[FROM_RANK] + 1};
        char * squarePointer = squareInFrontOfPawn;
        int squareInFrontOfPawnOccupied = getSquareOccupant(squarePointer, currentPosition);
        if (fileDiff == 0 && (toSquareOccupant || squareInFrontOfPawnOccupied)) { return 0; }
    } 
    
    return 1;
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
    return (character >= 'a' && character <='h') ? 1 : 0;
}

int isRank(char character)
{
    return (character >='1' && character <='8') ? 1 : 0;
}
