#include "config.h"
#include "engine.h"
#include "log.h"

int engine_init(int max_connects)
{
    log_stdout("core/engine", 1, "initializing IO engine for a maximum of %d connections", max_connects);

    /* TODO: select apropriate socket event engine and initialize it */

    return 0;
}
