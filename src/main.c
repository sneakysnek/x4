#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "config.h"
#include "init.h"
#include "log.h"
#include "main.h"
#include "timers.h"
#include "version.h"

int running = 1;

int main(int argc, char* argv[])
{
    int fork = 0; /* We'll default this back to 1 later in development. */

    log_stdout("core/main", 1, "Starting X4 %s+[%s]", version, vcs_version);

    if (fork) {
        log_stdout("core/main", 1, "forking");
    }

    init(&fork);

    while(running) {
        struct TimerInfo *ti = timer_next();
        int delay = 1;

        if (ti != NULL)
            delay = ti->ti_timestamp - time(NULL);

        sleep(delay);
        /* TODO: add main daemon loop */
    }

    deinit();

    return 0;
}

void x4_shutdown(char* message)
{
    if (message != NULL)
        log_stdout("core/main", 1, "Shutting down: %s", message);
    else
        log_stdout("core/main", 1, "Shutting down");
    running = 0;
}
