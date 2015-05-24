#include <assert.h>

#include "config.h"
#include "engines.h"
#include "log.h"

#ifdef USE_POLL
extern struct Engine engine_poll;
#define ENGINE_POLL &engine_poll,
#else
#define ENGINE_POLL
#endif /* USE_POLL */

extern struct Engine engine_select;

static const struct Engine *engines[] = {
    ENGINE_POLL
    &engine_select,
    0
};

int engines_init(int max_connects)
{
    int i = 0;

    log_stdout("core/engine", 1, "initializing IO engine for a maximum of %d connections", max_connects);

    /* TODO: select apropriate socket event engine and initialize it */

    for (i = 0; engines[i]; i++)
    {
        assert(0 != engines[i]->eng_name);
        assert(0 != engines[i]->eng_init);

        if ((*engines[i]->eng_init)(max_connects) == 0)
            break; /* Found an engine that'll work */
    }

    if (engines[i] == 0)
    {
        log_stderr("core/engine", 1, "failed to initialize a working io engine");
        return -1;
    }

    log_stdout("core/engine", 1, "successfully initialized %s io engine", engines[i]->eng_name);

    return 0;
}
