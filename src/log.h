#ifndef LOG_H
#define LOG_H

void logText(char * text);
void logEvent(char * type, char * text);
void logUserError(char * text);
char * getCurrentTimestamp();

#endif