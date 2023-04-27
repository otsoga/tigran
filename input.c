#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

char * getUserInput()
{
    char * input = (char *) calloc(USER_INPUT_LENGTH, sizeof(char));
    strncpy(input, "\0", sizeof(input));
    char * move = trim(fgets(input, USER_INPUT_LENGTH, stdin));
    logEvent("trimmed input", move);

    free(input);

    return move;
}

char * trim(char * string)
{
    logEvent("raw input", string);
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
        if (string[i] == ' ') { continue; }
        if (string[i] == '\n') {
            string[i] = '\0';
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
        if (string[i] == ' ') { continue; }
        startIndex = i;
        break;
    }

    char * trimmedString = (char *) calloc(strlen(string + startIndex) + 1, sizeof(char));
    strncpy(trimmedString, (string + startIndex), strlen(string + startIndex)+ 1);

    return trimmedString;
}
