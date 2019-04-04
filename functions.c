#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

void drawBoard(int board[8][8])
{
    for (int i = 7; i > -1; i--) {
        for(int j = 0; j < 8; j++) {
            drawSquare(board[i][j]);
        }
        printf("\n");
    }
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

int isLegalMove(char move[USER_INPUT_LENGTH], int board[8][8], int turn) 
{
    return 1;
}

int makeMove(char move[USER_INPUT_LENGTH], int board[8][8], int turn)
{
    int to[2];
    int from[2];

    if (move[0] >= 'a' && move[0] <= 'h') {
        from[0] = (int) (move[0] - 'a');
        from[1] = (int) (move[1] - '0' - 1);
        to[0]   = (int) (move[3] - 'a');
        to[1]   = (int) (move[4] - '0' - 1);
        
        movePiece(from, to, board);
    } else if (move == "0-0") {
        if (turn == WHITE) {
            makeMove("e1-g1", board, WHITE);
            makeMove("h1-f1", board, WHITE);
        } else if (turn == BLACK) {
            makeMove("e8-g8", board, WHITE);
            makeMove("h8-f8", board, WHITE);
        }
    } else {
        return 0;
    }

    return 1;
}

void movePiece(int from[2], int to[2], int board[8][8]) 
{
    board[to[1]][to[0]] = board[from[1]][from[0]];
    board[from[1]][from[0]] = 0;
}

char * getMove(int turn) 
{
    char * input = (char *) malloc(USER_INPUT_LENGTH);
    if (turn) {
        printf("White's move: ");
    } else {
        printf("Black's move: ");
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
        endIndex = i;
    }

    stringSize = endIndex + 1;
    trimmedString = (char*) malloc(stringSize);
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

    char * trimmedString = (char *) malloc(strlen(string + startIndex) + 1);
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
