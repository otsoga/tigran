#include <stdlib.h>
#include <string.h>
#include "pgn.h"
#include "log.h"

struct PgnGame * initPgnGame() 
{
    struct PgnGame * record = calloc(1, sizeof(struct PgnGame));
    strncpy(record->event, "Victor's Experiment", MAX_EVENT_LENGTH);
    strncpy(record->white, "Victor", MAX_EVENT_LENGTH);
    strncpy(record->black, "Manuel", MAX_EVENT_LENGTH);
    record->moveIndex = 0;

    return record;
}

void addMoveToPgnGame(struct PgnGame * record, char * move)
{
    strncpy(record->moveList[record->moveIndex], move, 6);
    record->moveIndex++;
    logEvent("Move added to PGN", move);
}