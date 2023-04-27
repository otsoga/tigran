#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"
#include "config.h"
/* Standardizes user input to include a `-` between squares even when the user omits it. */
void formatMove(char * userInput)
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
int makeMove(char * move, struct Position * currentPosition)
{
    // printf("Move: %s\n", move);
    if (isFile(*move)) {
        int * from = getFromSquareCoordinates(move);
        int * to = getToSquareCoordinates(move);
        // printf("TO: %d, %d \n", to[0], to[1]);
        // printf("FROM: %d, %d \n", from[0], from[1] );
        movePiece(from, to, currentPosition);
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

void logText(char * text)
{
    if (!LOG_EVENTS) {
        return;
    }
    FILE * logFile;
    logFile = fopen(LOG_FILE, "a");

    if (logFile == NULL)
    {
        printf("\nUnable to access log file, quitting.\n");   
        exit(1);             
    }

    fprintf(logFile, "%s", text);
    fclose(logFile);
}

void logEvent(char * type, char * text)
{
    char eventText[1024];
    char * now = getCurrentTimestamp();
    sprintf(eventText, "[%s][%s] %s\n", now, type, text);
    logText(eventText);
    free(now);
}

char * getCurrentTimestamp()
{
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  char * now = calloc(20, sizeof(char));
  sprintf(now, "%d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

  return now;
}