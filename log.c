#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"
#include "log.h"
#include "config.h"

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