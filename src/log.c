#include <stdio.h>

void log_stdout(char **prefix, char **str, int depth) {
    printf("(%s)  -  %s\n",*prefix,*str);
}

void log_stderr(char **prefix, char **str, int depth) {
    fprintf(stderr,"(%s)  -  %s\n",*prefix,*str);
}

