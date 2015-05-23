#ifndef _log_h
#define _log_h
#include <stdio.h>

#define LOGFILE    "x4.log"
extern int logFileCreated;

void log_file (char *str, ...);
void log_stdout(char *prefix, int depth, char *str, ...);
void log_stderr(char *prefix, int depth, char *str, ...);

#endif
