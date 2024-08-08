#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"
#include "log.h"
#include "position.h"
#include "move.h"

/* Standardizes user input to include a `-` between squares even when the user omits it. */
void sanitizeMove(char * userInput)
{
    if (strcmp(userInput, "0-0") == 0 || strcmp(userInput, "0-0-0") == 0) { return; }
    if (userInput[2] != '-') { // this was *(userInput +2) before
        int newLength = strlen(userInput) + 1;
        char * tempString = (char *) malloc(newLength);
        strncpy(tempString, "\0", newLength);
        strncpy(tempString, userInput, 2);
        strcat(tempString, "-");
        strncat(tempString, userInput + 2, 2);
        userInput = (char* ) realloc(userInput, newLength);
        strncpy(userInput, tempString, newLength);
        free(tempString);
    }
}


/* Makes moves from dash separated algebraic notation, with no validation. Also understands castling */
int makeMove(struct Position * currentPosition, char * move)
{
    // printf("Move: %s\n", move);
    if (isFile(*move)) {
        int * from = getFromSquareCoordinates(move);
        int * to = getToSquareCoordinates(move);
        // printf("TO: %d, %d \n", to[0], to[1]); // file, rank as ints
        // printf("FROM: %d, %d \n", from[0], from[1] );
        int piece = getSquareOccupant(currentPosition, move);
        
        if (piece == WK) {
            currentPosition->whiteKingsideCastleStatus = PROHIBITED;
            currentPosition->whiteQueensideCastleStatus = PROHIBITED;
        }

        if (piece == BK) {
            currentPosition->blackKingsideCastleStatus = PROHIBITED;
            currentPosition->blackQueensideCastleStatus = PROHIBITED;
        }

        if (from[0] == 7 && from[1] == 0) { // white kingside rook square
            currentPosition->whiteKingsideCastleStatus = PROHIBITED;
        }

        if (from[0] == 0 && from[1] == 0) { // white queenside rook square
            currentPosition->whiteQueensideCastleStatus = PROHIBITED;
        }

        if (from[0] == 7 && from[1] == 7) { // black kingside rook square
            currentPosition->blackKingsideCastleStatus = PROHIBITED;
        }

        if (from[0] == 0 && from[1] == 7) { // a8 square
            currentPosition->blackQueensideCastleStatus = PROHIBITED;
        }

        movePiece(currentPosition, from, to);
        free(from);
        free(to);

        return 1;
    }

    if (strcmp(move, "0-0") == 0) {
        castleKingSide(currentPosition);
        return 1;
    }

    if (strcmp(move, "0-0-0") == 0) {
        castleQueenSide(currentPosition);
        return 1;
    }

    return 0;
}

int * getToSquareCoordinates(char * move)
{
    int * square = (int *) malloc(sizeof(int) * 2);
    square[0] = (int) (*(move + 3) - 'a');
    square[1] = (int) (*(move + 4) - '0' - 1);

    return square;
}

int * getFromSquareCoordinates(char * move)
{
    int * square = (int *) malloc(sizeof(int) * 2);
    square[0] = (int) (*move - 'a');
    square[1] = (int) (*(move + 1) - '0' - 1);

    return square;
}

    /* Moves piece from one part of the board array to another. Only understands ints */
    void movePiece(struct Position * currentPosition, int from[2], int to[2])
    {
        currentPosition->board[to[0]][to[1]] = currentPosition->board[from[0]][from[1]];
        currentPosition->board[from[0]][from[1]] = 0;
    }

void castleKingSide(struct Position * currentPosition)
{
    if (currentPosition->turn == WHITE) {
        makeMove(currentPosition, "e1-g1");
        makeMove(currentPosition, "h1-f1");
    }

    if (currentPosition->turn == BLACK) {
        makeMove(currentPosition, "e8-g8");
        makeMove(currentPosition, "h8-f8");
    }
}

void castleQueenSide(struct Position * currentPosition)
{
    if (currentPosition->turn == WHITE) {
        makeMove(currentPosition, "e1-c1");
        makeMove(currentPosition, "a1-d1");
    }

    if (currentPosition->turn == BLACK) {
        makeMove(currentPosition, "e8-g8");
        makeMove(currentPosition, "a8-d8");
    }
}