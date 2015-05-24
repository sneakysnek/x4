#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "log.h"

/**
* Function log_stdout
* Log messages to stdout
* @param char * prefix the module prefix
* @param char * str the message string
* @param int depth the depth of the message (e.g. INFO, ERROR,FATAL).
*/
void log_stdout(char *prefix, int depth, char *str, ...) {
    int n = 0;
    char line[512];
    va_list ap;

    va_start(ap, str);
    n = vsnprintf((char *)&line, 512, str, ap);
    va_end(ap);

    if (n >= 1)
        printf("(%s) - %s\n", prefix, line);
}

/**
* Function: log_stderr
* Log errors to stderr
* @param char * prefix the module prefix
* @param char * str the message string
* @param int depth the depth of the message (e.g. INFO, ERROR,FATAL).
*/
void log_stderr(char *prefix, int depth, char *str, ...) {
    int n = 0;
    char line[512];
    va_list ap;

    va_start(ap, str);
    n = vsnprintf((char *)&line, 512, str, ap);
    va_end(ap);

    if (n >= 1)
        fprintf(stderr, "(%s) - %s\n", prefix, line);
}

int logFileCreated = 0;

/**
* Function log_file
* Log messages to LOGFILE
* @param char *message the message to log to LOGFILE
*/
void log_file (char *prefix, int depth, char *str, ...)
{
    FILE *file;
    int n = 0;
    char line[512];
    va_list ap;

    va_start(ap, str);
    n = vsnprintf((char *)&line, 512, str, ap);
    va_end(ap);

    if (n <= 0)
        return;

    if (!logFileCreated) {
        file = fopen(LOGFILE, "w");
        logFileCreated = 1;
    }
    else
        file = fopen(LOGFILE, "a");

    if (file == NULL) {
        if (logFileCreated)
            logFileCreated = 0;
            return;
    }
    else
    {
        fprintf(file, "(%s) - %s\n", prefix, line);
        fclose(file);
    }

    if (file)
        fclose(file);
}
