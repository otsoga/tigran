#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

/* Board coordinate location is inverted because of the way the board is drawn */
void drawBoard(struct Position * currentPosition)
{
    printf("\n");

    for (int i = 7; i > -1; i--) {
        for(int j = 0; j < 8; j++) {
            drawSquare(currentPosition->board[j][i]);
        }
        printf("\n");
    }

    printf("\n");
}

void drawSquare(int value)
{
    char piece[13];
    piece[WK] = 'K';
    piece[WQ] = 'Q';
    piece[WR] = 'R';
    piece[WB] = 'B';
    piece[WN] = 'N';
    piece[WP] = 'P';
    piece[BK] = 'k';
    piece[BQ] = 'q';
    piece[BR] = 'r';
    piece[BB] = 'b';
    piece[BN] = 'n';
    piece[BP] = 'p';
    piece[0]  = '.';

    printf("%c", piece[value]);
}

/* Standardizes user input to include a `-` between squares even when the user omits it. */
void formatMove(char * userInput)
{
    if (strcmp(userInput, "0-0") == 0 || strcmp(userInput, "0-0-0") == 0) { return; }
    if (*(userInput + 2) != '-') {
        int newLength = strlen(userInput) + 1;

        char * tempString = (char *) malloc(newLength);
        strncpy(tempString, "\0", newLength);
        strncpy(tempString, userInput, 2);
        strncat(tempString, "-", 1);
        strncat(tempString, userInput + 2, 2);
        userInput = (char* ) realloc(userInput, newLength);
        strncpy(userInput, tempString, newLength);
        free(tempString);
    }
}

// TODO: Actually check squares
int isLegalMove(char move[USER_INPUT_LENGTH], struct Position * currentPosition)
{
    printf("Move: %s\n", move);
    printf("Piece at %c%c: %d", move[0], move[1], getSquareOccupant(move, currentPosition));

    return 1;
}

/* Makes moves from dash separated algebraic notation, with no validation. Also understands castling */
int makeMove(char * move, struct Position * currentPosition)
{
    printf("Move: %s\n", move);
    if (isFile(*move)) {
        int * from = getFromSquareCoordinates(move);
        int * to = getToSquareCoordinates(move);
        printf("TO: %d, %d \n", to[0], to[1]);
        printf("FROM: %d, %d \n", from[0], from[1] );
        movePiece(from, to, currentPosition);

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
void movePiece(int from[2], int to[2], struct Position * currentPosition)
{
    currentPosition->board[to[0]][to[1]] = currentPosition->board[from[0]][from[1]];
    currentPosition->board[from[0]][from[1]] = 0;
}

void castleKingSide(struct Position * currentPosition)
{
    if (currentPosition->turn == WHITE) {
        makeMove("e1-g1", currentPosition);
        makeMove("h1-f1", currentPosition);
    } 

    if (currentPosition->turn == BLACK) {
        makeMove("e8-g8", currentPosition);
        makeMove("h8-f8", currentPosition);
    }
}

void castleQueenSide(struct Position * currentPosition)
{
    if (currentPosition->turn == WHITE) {
        makeMove("e1-c1", currentPosition);
        makeMove("a1-d1", currentPosition);
    }

    if (currentPosition->turn == BLACK) {
        makeMove("e8-g8", currentPosition);
        makeMove("a8-d8", currentPosition);
    }
}

int isFile(char character)
{
    return (character >= 'a' && character <='h') ? 1 : 0;
}

int isRank(char character)
{
    return (character >='1' && character <='8') ? 1 : 0;
}

/* Returns occupant of a AN square */
int getSquareOccupant(char * move, struct Position * currentPosition)
{
    int file = (int) (*move - 'a');
    int rank = (int) *(move + 1) - '1';
    printf("file: %d, rank: %d\n", file, rank);
    
    return currentPosition->board[file][rank];
}

/* Prompts the user for a move/command and saves it */
char * getUserInput()
{
    char * input = (char *) calloc(USER_INPUT_LENGTH, sizeof(char));
    strncpy(input, "\0", sizeof(input));
    char * move = trim(fgets(input, USER_INPUT_LENGTH, stdin));
    free(input);

    return move;
}

char * trim(char * string)
{
    char * rtrimmed = rtrim(string);
    char * trimmed = ltrim(rtrimmed);

    free(rtrimmed);

    return trimmed;
}

char * rtrim(char * string)
{
    char * trimmedString;
    int stringSize;
    int endIndex = -1;

    for (int i = 0, len = strlen(string); i < len; ++i) {
        if (*(string + i) == ' ') { continue; }
        if (*(string + i) == '\n') {
            *(string + i) = '\0';
            break;
        }
        endIndex = i;
    }

    stringSize = endIndex + 1;
    trimmedString = (char*) calloc(stringSize, sizeof(char));
    strncpy(trimmedString, string, stringSize);

    return trimmedString;
}

char * ltrim(char * string)
{
    int startIndex = -1;

    for (int i = 0, len = strlen(string); i < len; ++i) {
        if (*(string + i) == ' ') { continue; }
        startIndex = i;
        break;
    }

    char * trimmedString = (char *) calloc(strlen(string + startIndex) + 1, sizeof(char));
    strncpy(trimmedString, (string + startIndex), strlen(string + startIndex)+ 1);

    return trimmedString;
}
