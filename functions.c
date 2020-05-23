#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

/* Board coordinate location is inverted because of the way the board is drawn */
void drawBoard(int board[FILES][RANKS])
{
    printf("\n");

    for (int i = 7; i > -1; i--) {
        for(int j = 0; j < 8; j++) {
            drawSquare(board[j][i]);
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
void formatMove(char * move)
{
    if (strcmp(move, "0-0") == 0 || strcmp(move, "0-0-0") == 0) { return; }
    if (*(move + 2) != '-') {
        int newLength = strlen(move) + 1;

        char * tempString = (char *) malloc(newLength);
        strncpy(tempString, "\0", newLength);
        strncpy(tempString, move, 2);
        strncat(tempString, "-", 1);
        strncat(tempString, move + 2, 2);
        move = (char* ) realloc(move, newLength);
        strncpy(move, tempString, newLength);
        free(tempString);
    }
}

// TODO: Actually check squares
int isLegalMove(char move[USER_INPUT_LENGTH], int board[8][8], int turn)
{
    printf("Move: %s\n", move);
    printf("Piece at %c%c: %d", move[0], move[1], getSquareOccupant(move, board));

    return 1;
}

/* Makes moves from dash separated algebraic notation, with no validation. Also understands castling */
int makeMove(char * move, int board[8][8], int turn)
{
    if (isFile(*move)) {
        int * from = getFromSquareLocation(move);
        int * to = getToSquareLocation(move);
        movePiece(from, to, board);

        return 1;
    }

    if (strcmp(move, "0-0") == 0) {
        castleKingSide(board, turn);
        return 1;
    } 

    if (strcmp(move, "0-0-0") == 0) {
        castleQueenSide(board, turn);
        return 1;
    }

    return 0;
}

void castleKingSide(int board[8][8], int turn)
{
    if (turn == WHITE) {
        makeMove("e1-g1", board, WHITE);
        makeMove("h1-f1", board, WHITE);
    } 

    if (turn == BLACK) {
        makeMove("e8-g8", board, BLACK);
        makeMove("h8-f8", board, BLACK);
    }
}

void castleQueenSide(int board[8][8], int turn)
{
    if (turn == WHITE) {
        makeMove("e1-c1", board, WHITE);
        makeMove("a1-d1", board, WHITE);
    }

    if (turn == BLACK) {
        makeMove("e8-g8", board, BLACK);
        makeMove("a8-d8", board, BLACK);
    }
}

int * getToSquareLocation(char * move)
{
  int * square = (int *) malloc(sizeof(int) * 2);
  square[0] = (int) (*(move + 3) - 'a');
  square[1] = (int) (*(move + 4) - '0' - 1);

  return square;
}

int * getFromSquareLocation(char * move)
{
  int * square = (int *) malloc(sizeof(int) * 2);
  square[0] =(int) (*move - 'a');
  square[1] = (int) (*(move + 1) - '0' - 1);

  return square;
}

/* Moves piece from one part of the board array to another. Only understands ints */
void movePiece(int from[2], int to[2], int board[8][8])
{
    board[to[0]][to[1]] = board[from[0]][from[1]];
    board[from[0]][from[1]] = 0;
}

/* Prompts the user for a move/command and saves it */
char * getMove(int turn)
{
    char * input = (char *) calloc(USER_INPUT_LENGTH, sizeof(char));
    strncpy(input, "\0", sizeof(input));
    if (turn) {
        printf("Black's move: ");
    } else {
        printf("White's move: ");
    }

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

int isFile(char character)
{
    return (character >= 'a' && character <='h') ? 1 : 0;
}

int isRank(char character)
{
    return (character >='1' && character <='8') ? 1 : 0;
}

/* Returns occupant of a AN square */
int getSquareOccupant(char * move, int board[8][8])
{
    int file = (int) (*move - 'a');
    int rank = (int) *(move + 1) - '1';
    printf("file: %d, rank: %d\n", file, rank);
    return board[rank][file];
}
