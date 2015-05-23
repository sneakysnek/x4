#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "init.h"
#include "log.h"
#include "timers.h"
#include "config.h"
#include "version.h"

int main(int argc, char* argv[])
{
    int fork = 1;
    char startmsg[512];

    snprintf(startmsg, 512, "Starting X4 %s+[%s]", version, cvs_version);

    log_stdout("core/main", startmsg, 1);
    log_stdout("core/main", "forking", 1);
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
