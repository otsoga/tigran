#ifndef RULES_H
#define RULES_H

// struct LegalMoveList {
//     char move[7];
// };

int isLegalMove(char * move, struct Position * currentPosition);
int areToAndFromSquaresValid(char * move, struct Position * currentPosition);
int isLegalMoveForPiece(char * move, struct Position * currentPosition);
int isLegalPawnMove(char * move, struct Position * currentPosition);
int isLegalKnightMove(char * move, struct Position * currentPosition);
int isLegalBishopMove(char * move, struct Position * currentPosition);
int isLegalRookMove(char * move, struct Position * currentPosition);
int isLegalQueenMove(char * move, struct Position * currentPosition);
int isLegalKingMove(char * move, struct Position * currentPosition);
int isLegalCastleMove(char * move, struct Position * currentPosition);
struct LegalMoveList * getLegalMoves(struct Position * currentPosition);

#endif
