#include <stdio.h>
#include <stdlib.h>
#include "log.h"

void log_stdout(char **prefix, char **str, int depth) {
    printf("(%s)  -  %s\n",*prefix,*str);
}

void log_stderr(char **prefix, char **str, int depth) {
    fprintf(stderr,"(%s)  -  %s\n",*prefix,*str);
}

int logFileCreated = 0;

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
