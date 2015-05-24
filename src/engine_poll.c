#include <poll.h>
#include <stdlib.h>

#include "engines.h"
#include "log.h"

/** Array of poll() active elements. */
static struct pollfd* pollfdList;
/** Number of pollfd elements currently used. */
static unsigned int poll_count;
/** Maximum file descriptor supported, plus one. */
static unsigned int poll_max;

int engine_poll_init(int max_conns)
{
    int i;

    log_stdout("core/engine/poll", 1,
               "attempting to initialize poll() io engine");

    pollfdList = (struct pollfd*) malloc(sizeof(struct pollfd) * max_conns);

    /* initialize the data */
    for (i = 0; i < max_conns; i++) {
        pollfdList[i].fd = -1;
        pollfdList[i].events = 0;
        pollfdList[i].revents = 0;
    }

    poll_count = 0; /* nothing in set */
    poll_max = max_conns; /* number of sockets allocated */

    return 0;
}

struct Engine engine_poll = {
    "poll()",
    engine_poll_init
};
