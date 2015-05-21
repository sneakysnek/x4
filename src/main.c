#include <stdio.h>
#include <time.h>
#include "init.h"
#include "log.h"
#include "timers.h"

int main(int argc, char* argv[])
{
    int fork = 1;
    log_stdout("core/main","forking",1);
    init(&fork);

    while(1) {
        struct TimerInfo *ti = timer_next();
        int delay = 1;

        if (ti != NULL)
            delay = ti->ti_timestamp - time(NULL);

        sleep(delay);
        /* TODO: add main daemon loop */
    }
    return 0;
}
