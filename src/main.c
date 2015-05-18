#include <stdio.h>
#include "init.h"
#include "log.h"

int main(int argc, char* argv[])
{
    int fork = 1;
    log_stdout("core/main","forking",1);
    init(&fork);

    while(1) {
        sleep(1);
        /* TODO: add main daemon loop */
    }
    return 0;
}
