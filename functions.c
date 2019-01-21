#include <stdio.h>
#include <string.h>
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

int makeMove(char move[20], int board[8][8], int turn)
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

void movePiece(int from[2], int to[2], int board[8][8]) {
    board[to[1]][to[0]] = board[from[1]][from[0]];
    board[from[1]][from[0]] = 0;
}

char * getMove(int turn) 
{
    char input[10];
    if (turn) {
        printf("White's move: ");
    } else {
        printf("Black's move: ");
    }

    return fgets(input, 10, stdin);
}
