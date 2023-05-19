#ifndef FUNCTIONS_H
#define FUNCTIONS_H

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
#define USER_INPUT_LENGTH 20
#define RANKS 8
#define FILES 8
#define ORIGIN_FILE 0
#define ORIGIN_RANK 1
#define DESTINATION_FILE 3
#define DESTINATION_RANK 4
#define TURN_WHITE 1
#define TURN_BLACK 2
#define NOT_POSSIBLE -1
#define NOT_PROHBITED 0

struct Position {
    int board[8][8];
    int turn;
    int enPassantFile;
    int kingsideCastleStatus;
    int queensideCastleStatus;
};

void gameLoop();
void drawSquare(int value);
void drawBoard(struct Position * currentPosition);
void displayLegalMoves(struct Position * currentPosition);

int getSquareOccupant(struct Position * currentPosition, char * move);
int getOccupantColor(int occupant);
int getOccupantPieceType(int occupant);

// these modify the given position
void initPosition(struct Position * position);
void movePiece(struct Position * currentPosition, int from[2], int to[2]);
int makeMove(struct Position * currentPosition, char * move);
void castleKingSide(struct Position * currentPosition);
void castleQueenSide(struct Position * currentPosition);
void switchTurn(struct Position * currentPosition);
void copyPosition(struct Position * sourcePosition, struct Position * destinationPosition);


void formatMove(char * move);
int * getFromSquareCoordinates(char * move);
int * getToSquareCoordinates(char * move);



int isFile(char character);
int isRank(char character);



#endif
