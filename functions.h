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

void drawSquare(int value);
void drawBoard(int board[8][8]);
void movePiece(int from[2], int to[2], int board[8][8]);
void formatMove(char * move);
int isLegalMove(char move[USER_INPUT_LENGTH], int board[8][8], int turn);
int makeMove(char * move, int board[8][8], int turn);
char * getMove(int turn);
char * rtrim(char * string);
char * ltrim(char * string);
char * trim(char * string);
int isFile(char character);
int isRank(char character);

struct Position {
    int board[8][8];
    int turn;
};

struct Move {
    int squares[2];
};

#endif
