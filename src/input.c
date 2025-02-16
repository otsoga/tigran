#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "log.h"
#include "input.h"

char * getUserInput()
{
    char * input = (char *) calloc(USER_INPUT_LENGTH, sizeof(char));
    if (!input) return NULL;
    
    if (!fgets(input, USER_INPUT_LENGTH, stdin)) {
        free(input);
        return NULL;
    }
    
    char * trimmedInput = trim(input);
    free(input);
    return trimmedInput;
}

char * trim(char * string)
{
    if (!string) return NULL;
    
    char * rtrimmed = rtrim(string);
    if (!rtrimmed) return NULL;
    
    char * trimmed = ltrim(rtrimmed);
    free(rtrimmed);
    return trimmed;
}

char * rtrim(char * string)
{
    if (!string) return NULL;
    
    int len = strlen(string);
    int endIndex = -1;

    for (int i = 0; i < len; ++i) {
        if (string[i] == '\n' || string[i] == '\r') {
            break;
        }
        if (string[i] != ' ') {
            endIndex = i;
        }
    }

    if (endIndex == -1) return strdup("");

    int newSize = endIndex + 2;  // +1 for last char, +1 for null terminator
    char * trimmedString = (char*) malloc(newSize);
    if (!trimmedString) return NULL;

    strncpy(trimmedString, string, endIndex + 1);
    trimmedString[endIndex + 1] = '\0';

    return trimmedString;
}

char * ltrim(char * string)
{
    if (!string) return NULL;
    
    int len = strlen(string);
    int startIndex = 0;

    while (startIndex < len && string[startIndex] == ' ') {
        startIndex++;
    }

    int newLen = strlen(string + startIndex) + 1;  // +1 for null terminator
    char * trimmedString = (char *) malloc(newLen);
    if (!trimmedString) return NULL;

    strcpy(trimmedString, string + startIndex);
    return trimmedString;
}
