#ifndef MOVE_H
#define MOVE_H

void movePiece(struct Position * currentPosition, int from[2], int to[2]);
int makeMove(struct Position * currentPosition, char * move);
void castleKingSide(struct Position * currentPosition);
void castleQueenSide(struct Position * currentPosition);
void switchTurn(struct Position * currentPosition);

#endif
