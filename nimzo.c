#include <stdio.h>

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

int main(void)
{
    int to[2];
    int from[2];
    int board[8][8] = {
        {WR, WN, WB, WQ, WK, WB, WN, WR},
        {WP, WP, WP, WP, WP, WP, WP, WP},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {BP, BP, BP, BP, BP, BP, BP, BP},
        {BR, BN, BB, BQ, BK, BB, BN, BR}
    };
    
    makeMove("e2-e4", board, WHITE);
    makeMove("e7-e5", board, BLACK);
    makeMove("g1-f3", board, WHITE);
    makeMove("b8-c6", board, BLACK);
    makeMove("f1-b5", board, WHITE);
    makeMove("d7-d6", board, BLACK);
    makeMove("0-0", board, WHITE);
    makeMove("f8-e7", board, BLACK);
    makeMove("f1-e1", board, WHITE);
    makeMove("g8-f6", board, BLACK);
    makeMove("c2-c3", board, WHITE);
    makeMove("0-0", board, BLACK);

    drawBoard(board);

    return 0;
}

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



int makeMove(char move[5], int board[8][8], int turn)
{
    int to[2];
    int from[2];

    if (move[0] >= 'a' && move[0] <= 'h') {
//        from[1] = (int) (move[0] - 'a');
//        from[0] = (int) (move[1] - '0' - 1);
//        to[1] = (int) (move[3] - 'a');
//        to[0] = (int) (move[4] - '0' - 1);

//        movePiece(from, to, board);
        movePiece(from, to, board);
    } else if (move == "0-0") {
        if (turn == WHITE) {
            makeMove("e1-g1", board, WHITE);
            makeMove("h1-f1", board, WHITE);
        } else if (turn == BLACK) {
            makeMove("e8-g8", board, WHITE);
            makeMove("h8-f8", board, WHITE);
        }
    }

    return 1;
}

void movePiece(int from[2], int to[2], int board[8][8]) {
    board[to[0]][to[1]] = board[from[0]][from[1]];
    board[from[0]][from[1]] = 0;
}
