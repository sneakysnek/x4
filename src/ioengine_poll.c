#include <poll.h>
#include <stdlib.h>

#include "ioengine.h"
#include "log.h"

/** Array of active Socket structures, indexed by file descriptor. */
static struct Socket** sockList;
/** Array of poll() active elements. */
static struct pollfd* pollfdList;
/** Number of pollfd elements currently used. */
static unsigned int poll_count;
/** Maximum file descriptor supported, plus one. */
static unsigned int poll_max;

int ioengine_poll_init(int max_conns)
{
    int i;

    log_stdout("core/ioengine/poll", 1,
               "attempting to initialize poll() io engine");

    sockList = (struct Socket**) malloc(sizeof(struct Socket*) * max_conns);
    pollfdList = (struct pollfd*) malloc(sizeof(struct pollfd) * max_conns);

    if ((pollfdList == NULL) || (sockList == NULL))
    {
        log_stderr("core/ioengine/poll", 1,
                   "failed to initialize poll() io engine: unable to allocate memory");
        return -1;
    }

    /* initialize the data */
    for (i = 0; i < max_conns; i++) {
        sockList[i] = 0;
        pollfdList[i].fd = -1;
        pollfdList[i].events = 0;
        pollfdList[i].revents = 0;
    }

    poll_count = 0; /* nothing in set */
    poll_max = max_conns; /* number of sockets allocated */

    return 0;
}

int ioengine_poll_addsock(struct Socket *sock)
{

    return 0;
}

void ioengine_poll_delsock(struct Socket *sock)
{

}

struct IOEngine ioengine_poll = {
    "poll()",
    ioengine_poll_init,
    ioengine_poll_addsock,
    ioengine_poll_delsock
};
