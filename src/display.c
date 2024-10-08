#include <stdio.h>
#include <string.h>
#include "functions.h"
#include "rules.h"
#include "position.h"
#include "pgn.h"
#include "log.h"
#include "display.h"

void displayInterface(struct Position * currentPosition, struct PgnGame * record)
{
    displayPgnGame(record);
    drawBoard(currentPosition);
    displayLegalMoves(currentPosition);

    char turn[6];
    strncpy(turn, currentPosition->turn  == TURN_BLACK ? "Black" : "White", 6);
    printf("%s's move: ", turn);
}

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

/* Draws the board I would prefer to have */
// void drawBoard(struct Position * currentPosition)
// {
//     printf("\n");

//     for (int i = 7; i > -1; i--) {
//         for(int j = 0; j < 8; j++) {
//             drawSquare(currentPosition->board[i][j]);
//         }
//         printf("\n");
//     }

//     printf("\n");
// }

void displayPgnGame(struct PgnGame * record)
{
    int isWhitesTurn;
    printf("[Event \"%s\"]\n\n", record->event);
    for (int i = 0; i < record->moveIndex; i++) {
        isWhitesTurn = i % 2 == 0;

        if (isWhitesTurn) {
            printf("%d. ", i / 2 + 1);
        }
        printf("%s ", record->moveList[i]);
        
        if ((i + 1) % (2 * PGN_MOVES_PER_LINE) == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

void displayLegalMoves(struct Position * currentPosition)
{
    printf("Legal moves: \n\n");
    // struct CandidateMoveList * move = getLegalMoves(currentPosition);
    // printf("Moves: %s", move->move );
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