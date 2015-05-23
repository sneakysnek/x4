#include "config.h"
#include "engines.h"
#include "log.h"

extern struct Engine engine_select;

static const struct Engine *engines[] = {
    &engine_select,
    0
};

int engines_init(int max_connects)
{
    log_stdout("core/engine", 1, "initializing IO engine for a maximum of %d connections", max_connects);

    /* TODO: select apropriate socket event engine and initialize it */

    return 0;
}
