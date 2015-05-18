#ifndef _log_h
#define _log_h
#include <stdio.h>

#define LOGFILE	"x4.log"
extern int logFileCreated;

void log_file (char *message);
void log_stdout(char *prefix, char *str, int depth);
void log_stderr(char *prefix, char *str, int depth);

#endif
