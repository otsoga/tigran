#ifndef RULES_H
#define RULES_H

struct CandidateMoveList {
    char move[7];
    struct CandidateMoveList * next;
};

int isLegalMove(char * move, struct Position * currentPosition);
int isLegalMoveForPiece(char * move, struct Position * currentPosition);
int isLegalPawnMove(char * move, struct Position * currentPosition);
int isLegalKnightMove(char * move, struct Position * currentPosition);
int isLegalBishopMove(char * move, struct Position * currentPosition);
int isLegalRookMove(char * move, struct Position * currentPosition);
int isLegalQueenMove(char * move, struct Position * currentPosition);
int isLegalKingMove(char * move, struct Position * currentPosition);
struct CandidateMoveList * getLegalMoves(struct Position * currentPosition);

#endif
