#ifndef POSITION_H
#define POSITION_H

#define WHITE 1
#define BLACK 2
#define KING 1
#define QUEEN 2
#define ROOK 3
#define BISHOP 4
#define KNIGHT 5
#define PAWN 6
#define WK 1
#define WQ 2
#define WR 3
#define WB 4
#define WN 5
#define WP 6
#define BK 7
#define BQ 8
#define BR 9
#define BB 10
#define BN 11
#define BP 12

void initPosition(struct Position * position);
void copyPosition(struct Position * sourcePosition, struct Position * destinationPosition);

#endif
