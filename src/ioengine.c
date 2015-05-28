#include <assert.h>

#include "config.h"
#include "ioengine.h"
#include "log.h"

#ifdef USE_POLL
extern struct IOEngine ioengine_poll;
#define IOENGINE_POLL &ioengine_poll,
#else
#define IOENGINE_POLL
#endif /* USE_POLL */

extern struct IOEngine ioengine_select;

static const struct IOEngine *ioengines[] = {
    IOENGINE_POLL
    &ioengine_select,
    0
};

int ioengine_init(int max_connects)
{
    int i = 0;

    log_stdout("core/ioengine", 1, "initializing IO engine for a maximum of %d connections", max_connects);

    /* TODO: select apropriate socket event engine and initialize it */

    for (i = 0; ioengines[i]; i++)
    {
        assert(0 != ioengines[i]->eng_name);
        assert(0 != ioengines[i]->eng_init);

        if ((*ioengines[i]->eng_init)(max_connects) == 0)
            break; /* Found an engine that'll work */
    }

    if (ioengines[i] == 0)
    {
        log_stderr("core/ioengine", 1, "failed to initialize a working io engine");
        return -1;
    }

    log_stdout("core/ioengine", 1, "successfully initialized %s io engine", ioengines[i]->eng_name);

    return 0;
}
