#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "pgn.h"

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
#define RANKS 8
#define FILES 8
#define ORIGIN_FILE 0
#define ORIGIN_RANK 1
#define DESTINATION_FILE 3
#define DESTINATION_RANK 4
#define TURN_WHITE 1
#define TURN_BLACK 2
#define NONE -1
#define ALLOWED 1
#define PROHIBITED 0

struct Position {
    int board[RANKS][FILES];
    int turn;
    int enPassantFile;
    int whiteKingsideCastleStatus;
    int blackKingsideCastleStatus;
    int whiteQueensideCastleStatus;
    int blackQueensideCastleStatus;
};

void gameLoop();
void displayInterface(struct Position * currentPosition, struct PgnGame * record);
void displayPgnGame(struct PgnGame * record);
void drawSquare(int value);
void drawBoard(struct Position * currentPosition);
void displayLegalMoves(struct Position * currentPosition);
void sanitizeMove(char ** move);
int * getFromSquareCoordinates(char * move);
int * getToSquareCoordinates(char * move);
int isFile(char character);
int isRank(char character);



#endif
