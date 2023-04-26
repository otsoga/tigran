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
#define FROM_FILE 0
#define FROM_RANK 1
#define TO_FILE 3
#define TO_RANK 4
#define TURN_WHITE 1
#define TURN_BLACK 2
#define NOT_POSSIBLE -1

struct Position {
    int board[8][8];
    int turn;
    int enPassantFile;
};

struct CandidateMoveList {
    char move[7];
    struct CandidateMoveList * next;
};

void gameLoop(struct Position * currentPosition);
void drawSquare(int value);
void drawBoard(struct Position * currentPosition);
void movePiece(int from[2], int to[2], struct Position * currentPosition);
void formatMove(char * move);
int isLegalMove(char * move, struct Position * currentPosition);
int isLegalMoveForPiece(char * move, struct Position * currentPosition);
int isLegalPawnMove(char * move, struct Position * currentPosition);
int isLegalKnightMove(char * move, struct Position * currentPosition);
int isLegalBishopMove(char * move, struct Position * currentPosition);
int isLegalRookMove(char * move, struct Position * currentPosition);
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
int getOccupantPieceType(int occupant);
void displayLegalMoves(struct Position * currentPostion);
struct CandidateMoveList * getLegalMoves(struct Position * currentPosition);
void logEvent(char * text);

#endif
