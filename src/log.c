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
void log_stdout(char *prefix, char *str, int depth) {
    printf("(%s)  -  %s\n",prefix,str);
}

/**
* Function: log_stderr
* Log errors to stderr
* @param char * prefix the module prefix
* @param char * str the message string
* @param int depth the depth of the message (e.g. INFO, ERROR,FATAL).
*/
void log_stderr(char *prefix, char *str, int depth) {
    fprintf(stderr,"(%s)  -  %s\n",prefix,str);
}

int logFileCreated = 0;

/**
* Function log_file
* Log messages to LOGFILE
* @param char *message the message to log to LOGFILE
*/
void log_file (char *message)
{
    FILE *file;
 
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
	fputs(message, file);
	(file);
    }
 
    if (file)
	fclose(file);
}
