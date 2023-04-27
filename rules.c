#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"
#include "log.h"

int isLegalMove(char * move, struct Position * currentPosition)
{
    if (strcmp(move, "0-0") == 0 || strcmp(move, "0-0-0") == 0) {
        logEvent("move", "castling is always legal");
        return 1;
    }

    int isValidFromSquare = isFile(move[FROM_FILE]) && isRank(move[FROM_RANK]);
    int isValidToSquare = isFile(move[TO_FILE]) && isRank(move[TO_RANK]);
    
    if (!isValidFromSquare || !isValidToSquare) { 
        logEvent("user error", "invalid to/from square");
        return 0; 
    }

    int fromSquareOccupant = getSquareOccupant(move, currentPosition);
    int toSquareOccupant = getSquareOccupant(&move[3], currentPosition);

    if (getOccupantColor(fromSquareOccupant) != currentPosition->turn) { 
        logEvent("user error", "trying move enemy piece or nonexistent piece.");
        return 0;
    }

    if (getOccupantColor(toSquareOccupant) == currentPosition->turn) { 
        logEvent("user error", "cannot capture own piece");
        return 0;
    }

    if (!isLegalMoveForPiece(move, currentPosition)) { return 0; }
    
    return 1;
}

int isLegalMoveForPiece(char * move, struct Position * currentPosition)
{
    int piece = getSquareOccupant(move, currentPosition);

    switch(getOccupantPieceType(piece)) {
        case PAWN:
            return isLegalPawnMove(move, currentPosition);
        case KNIGHT:
            return isLegalKnightMove(move, currentPosition);
        case BISHOP:
            return isLegalBishopMove(move, currentPosition);
        case ROOK:
            return isLegalRookMove(move, currentPosition);
        default:
            return 1;
    }
}

int isLegalPawnMove(char * move, struct Position * currentPosition)
{
    int isWhite = currentPosition->turn == WHITE;
    int rankDiff = isWhite ? move[TO_RANK] - move[FROM_RANK] : move[FROM_RANK] - move[TO_RANK];
    int notOnSecondRank = (int) move[FROM_RANK] - '0' != (isWhite ? 2 : 7);
    int fileDiff = abs(move[TO_FILE] - move[FROM_FILE]);
    int pieceDiagonallyAdjacent = fileDiff == 1 && rankDiff == 1;
    int toSquareOccupant = getSquareOccupant(&move[3], currentPosition);
    char squareInFrontOfPawn[] = {move[FROM_FILE], move[FROM_RANK] + (isWhite ? 1 : -1)};
    int squareInFrontOfPawnOccupied = getSquareOccupant(squareInFrontOfPawn, currentPosition);

    if (rankDiff > 2 || rankDiff < 1) { return 0; }
    if (notOnSecondRank && rankDiff == 2) { return 0; }
    if (fileDiff > 1) { return 0; }
    if (pieceDiagonallyAdjacent && !toSquareOccupant) { return 0; }
    if (fileDiff == 0 && (toSquareOccupant || squareInFrontOfPawnOccupied)) { return 0; }

    return 1;
}

int isLegalKnightMove(char * move, struct Position * currentPosition)
{
    int rankDiff = abs(move[TO_RANK] - move[FROM_RANK]);
    int fileDiff = abs(move[TO_FILE] - move[FROM_FILE]);
    int knightJumps = ((rankDiff == 2 && fileDiff == 1) || (rankDiff == 1 && fileDiff == 2));

    if (!knightJumps) { return 0; }

    return 1;
}

int isLegalBishopMove(char * move, struct Position * currentPosition)
{
    int rankDiff = abs(move[TO_RANK] - move[FROM_RANK]);
    int fileDiff = abs(move[TO_FILE] - move[FROM_FILE]);
    int moveOnDiagonal = rankDiff == fileDiff;

    if (!moveOnDiagonal) { return 0; }

    return 1;
}

int isLegalRookMove(char * move, struct Position * currentPosition)
{
    int rankDiff = abs(move[TO_RANK] - move[FROM_RANK]);
    int fileDiff = abs(move[TO_FILE] - move[FROM_FILE]);
    int moveOnRankOrFile = rankDiff == 0 || fileDiff == 0;

    if (!moveOnRankOrFile) { return 0; }

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
    return (character >= 'a' && character <= 'h') ? 1 : 0;
}

int isRank(char character)
{
    return (character >= '1' && character <= '8') ? 1 : 0;
}

struct CandidateMoveList * getLegalMoves(struct Position * currentPosition)
{
    struct CandidateMoveList * legalMoves = malloc(sizeof * legalMoves);
    strncpy(legalMoves->move, "e2-e4", 7);

    return legalMoves;
}
