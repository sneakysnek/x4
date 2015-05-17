#include <stdio.h>

void log_stdout(char **prefix, char **str, int depth) {
    printf("(%s)  -  %s\n",*prefix,*str);
}