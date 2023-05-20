#ifndef PGN_H
#define PGN_H
#define MAX_EVENT_LENGTH 50

struct PgnGame {
    char event[50];
    char site[50];
    char date[50];
    char round[20];
    char white[50];
    char black[50];
    char result[90];
    char moves[1000];
    char moveList[600][6];
    int moveIndex;
};

struct PgnGame * initPgnGame();
void addMoveToPgnGame(struct PgnGame * record, char * move);

#endif