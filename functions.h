#ifndef FUNCTIONS_H
#define FUNCTIONS_H

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
#define WHITE 1
#define BLACK 2
#define USER_INPUT_LENGTH 20
#define RANKS 8
#define FILES 8

struct Position {
    int board[8][8];
    int turn;
};

struct Move {
    int squares[2];
};

void gameLoop(struct Position * currentPosition);
void drawSquare(int value);
void drawBoard(struct Position * currentPosition);
void movePiece(int from[2], int to[2], struct Position * currentPosition);
void formatMove(char * move);
int isLegalMove(char * move, struct Position * currentPosition);
int makeMove(char * move, struct Position * currentPosition);
char * getUserInput();
char * rtrim(char * string);
char * ltrim(char * string);
char * trim(char * string);
int * getFromSquareCoordinates(char * move);
int * getToSquareCoordinates(char * move);
int isFile(char character);
int isRank(char character);
int getSquareOccupant(char * move, struct Position * currentPosition);
void castleKingSide(struct Position * currentPosition);
void castleQueenSide(struct Position * currentPosition);
int getOccupantColor(int occupant);

#endif
