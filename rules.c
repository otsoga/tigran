#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"
#include "rules.h"
#include "log.h"
#include "position.h"

int isLegalMove(char * move, struct Position * currentPosition)
{
    if (strcmp(move, "0-0") == 0 || strcmp(move, "0-0-0") == 0) {
        return isLegalCastleMove(move, currentPosition);
    }

    if (!isEachSquareValid(move, currentPosition)) { return 0; }
    if (!isLegalMoveForPiece(move, currentPosition)) { return 0; }
    
    return 1;
}

int isKingInCheck(struct Position * currentPosition)
{
    struct Position currentPositionWithOpponentTurn;
    return 0;
}

int isLegalCastleMove(char * move, struct Position * currentPosition)
{
    if (strcmp(move, "0-0") == 0) {
        return 1;
    }

    if (strcmp(move, "0-0-0") == 0) {
        return 1;
    }

    return 0;
}

int isEachSquareValid(char * move, struct Position * currentPosition) 
{
    int isValidFromSquare = isFile(move[ORIGIN_FILE]) && isRank(move[ORIGIN_RANK]);
    int isValidToSquare = isFile(move[DESTINATION_FILE]) && isRank(move[DESTINATION_RANK]);
    
    if (!isValidFromSquare || !isValidToSquare) { 
        logUserError("invalid to/from square");
        return 0; 
    }

    int fromSquareOccupant = getSquareOccupant(currentPosition, move);
    int toSquareOccupant = getSquareOccupant(currentPosition, &move[3]);

    if (getOccupantColor(fromSquareOccupant) != currentPosition->turn) { 
        logUserError("trying move enemy piece or nonexistent piece.");
        return 0;
    }

    if (getOccupantColor(toSquareOccupant) == currentPosition->turn) { 
        logUserError("cannot capture own piece");
        return 0;
    }

    return 1;
}

int isLegalMoveForPiece(char * move, struct Position * currentPosition)
{
    int piece = getSquareOccupant(currentPosition, move);

    switch(getOccupantPieceType(piece)) {
        case PAWN:
            return isLegalPawnMove(move, currentPosition);
        case KNIGHT:
            return isLegalKnightMove(move, currentPosition);
        case BISHOP:
            return isLegalBishopMove(move, currentPosition);
        case ROOK:
            return isLegalRookMove(move, currentPosition);
        case QUEEN:
            return isLegalQueenMove(move, currentPosition);
        case KING:
            return isLegalKingMove(move, currentPosition);
        default:
            return 1;
    }
}

int isLegalPawnMove(char * move, struct Position * currentPosition)
{
    int isWhite = currentPosition->turn == WHITE;
    int rankDiff = isWhite ? move[DESTINATION_RANK] - move[ORIGIN_RANK] : move[ORIGIN_RANK] - move[DESTINATION_RANK];
    int notOnSecondRank = (int) move[ORIGIN_RANK] - '0' != (isWhite ? 2 : 7);
    int fileDiff = abs(move[DESTINATION_FILE] - move[ORIGIN_FILE]);
    int pieceDiagonallyAdjacent = fileDiff == 1 && rankDiff == 1;
    int toSquareOccupant = getSquareOccupant(currentPosition, &move[3]);
    char squareInFrontOfPawn[] = {move[ORIGIN_FILE], move[ORIGIN_RANK] + (isWhite ? 1 : -1)};
    int squareInFrontOfPawnOccupied = getSquareOccupant(currentPosition, squareInFrontOfPawn);

    if (rankDiff > 2 || rankDiff < 1) {
        logUserError("pawns can only move one or two squares");
        return 0;    
    }

    if (notOnSecondRank && rankDiff == 2) { 
        logUserError("pawns can only move two squares if they are on the second rank");
        return 0;
    }
    if (fileDiff > 1) { 
        return 0;
        logUserError("pawns cannot move across multiple files");   
    }

    if (pieceDiagonallyAdjacent && !toSquareOccupant) { 
        logUserError("pawns can only capture enemy pieces that are diagonally adjacent to them.");
        return 0;
    }

    if (fileDiff == 0 && (toSquareOccupant || squareInFrontOfPawnOccupied)) {
        logUserError("pawns can only move forward ");
        return 0;
    }

    return 1;
}

int isLegalKnightMove(char * move, struct Position * currentPosition)
{
    int rankDiff = abs(move[DESTINATION_RANK] - move[ORIGIN_RANK]);
    int fileDiff = abs(move[DESTINATION_FILE] - move[ORIGIN_FILE]);
    int knightJumps = ((rankDiff == 2 && fileDiff == 1) || (rankDiff == 1 && fileDiff == 2));

    if (!knightJumps) { 
        logUserError("knights move in an L shape.");    
        return 0; 
    }

    return 1;
}

int isLegalBishopMove(char * move, struct Position * currentPosition)
{
    int rankDiff = abs(move[DESTINATION_RANK] - move[ORIGIN_RANK]);
    int fileDiff = abs(move[DESTINATION_FILE] - move[ORIGIN_FILE]);
    int moveOnDiagonal = rankDiff == fileDiff;

    if (!moveOnDiagonal) { 
        logUserError("bishops can only move along daigonals.");
        return 0;
    }

    return 1;
}

int isLegalRookMove(char * move, struct Position * currentPosition)
{
    int rankDiff = abs(move[DESTINATION_RANK] - move[ORIGIN_RANK]);
    int fileDiff = abs(move[DESTINATION_FILE] - move[ORIGIN_FILE]);
    int moveOnRankOrFile = rankDiff == 0 || fileDiff == 0;

    if (!moveOnRankOrFile) { 
        logUserError("rooks can only move along ranks and files.");
        return 0; 
    }

    return 1;
}

int isLegalQueenMove(char * move, struct Position * currentPosition)
{
    int rankDiff = abs(move[DESTINATION_RANK] - move[ORIGIN_RANK]);
    int fileDiff = abs(move[DESTINATION_FILE] - move[ORIGIN_FILE]);
    int moveOnRankOrFile = rankDiff == 0 || fileDiff == 0;
    int moveOnDiagonal = rankDiff == fileDiff;

    if (!moveOnRankOrFile && !moveOnDiagonal) { 
        logUserError("queens can only move along ranks, files, or diagonals.");
        return 0; 
    }

    return 1;
}

int isLegalKingMove(char * move, struct Position * currentPosition)
{
    int rankDiff = abs(move[DESTINATION_RANK] - move[ORIGIN_RANK]);
    int fileDiff = abs(move[DESTINATION_FILE] - move[ORIGIN_FILE]);
    int moveOnRankOrFile = rankDiff == 0 || fileDiff == 0;
    int moveOnDiagonal = rankDiff == fileDiff;

    if (rankDiff > 1 || fileDiff > 1) { 
        logUserError("kings can only move one square at a time.");
        return 0; 
    }

    if (!moveOnRankOrFile && !moveOnDiagonal) { 
        logUserError("kings can only move along ranks, files, or diagonals.");
        return 0; 
    }

    return 1;
}

// struct CandidateMoveList * getLegalMoves(struct Position * currentPosition)
// {
//     struct CandidateMoveList * legalMoves = malloc(sizeof(struct CandidateMoveList));
//     strncpy(legalMoves->move, "e2-e4", 7);

//     return legalMoves;
// }
