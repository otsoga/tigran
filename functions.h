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

void drawSquare(int value);
void drawBoard(int board[8][8]);
void movePiece(int from[2], int to[2], int board[8][8]);
int makeMove(char move[5], int board[8][8], int turn);
char * getMove(int turn);

struct Position {
    int board[8][8];
    int turn;
};

struct Move {
    int squares[2];
};

#endif
