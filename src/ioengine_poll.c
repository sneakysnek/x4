#include <assert.h>
#include <poll.h>
#include <stdlib.h>

#include "ioengine.h"
#include "log.h"

/* Figure out what bits to set for read */
#if defined(POLLMSG) && defined(POLLIN) && defined(POLLRDNORM)
#  define POLLREADFLAGS (POLLMSG|POLLIN|POLLRDNORM)
#elif defined(POLLIN) && defined(POLLRDNORM)
#  define POLLREADFLAGS (POLLIN|POLLRDNORM)
#elif defined(POLLIN)
#  define POLLREADFLAGS POLLIN
#elif defined(POLLRDNORM)
#  define POLLREADFLAGS POLLRDNORM
#endif

/* Figure out what bits to set for write */
#if defined(POLLOUT) && defined(POLLWRNORM)
#  define POLLWRITEFLAGS (POLLOUT|POLLWRNORM)
#elif defined(POLLOUT)
#  define POLLWRITEFLAGS POLLOUT
#elif defined(POLLWRNORM)
#  define POLLWRITEFLAGS POLLWRNORM
#endif

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
    int i = 0;

    if (sock == NULL)
        return -1;

    assert(sock->fd != 0);

    /* Find a free slot */
    for (i=0; sockList[i] && i < poll_count; i++)
        ;

    if (i >= poll_count) {
        if (poll_count >= poll_max) {
            log_stderr("core/ioengine/poll", 1,
                       "attempt to add socket %d in slot %d (> %d) to io engine poll failed",
                       sock->fd, i, poll_max);
            return -1;
        }
        i = poll_count++;
    }

    sock->ed = i;
    sockList[i] = sock;
    pollfdList[i].fd = sock->fd;

    if (sock->events & SE_READ)
        pollfdList[i].events |= POLLREADFLAGS;

    if (sock->events & SE_WRITE)
        pollfdList[i].events |= POLLWRITEFLAGS;

    return 0;
}

void ioengine_poll_delsock(struct Socket *sock)
{
    if (sock == NULL)
        return;

    assert(sock == sockList[sock->ed]);
    assert(sock->fd == pollfdList[sock->ed].fd);

    pollfdList[sock->ed].fd = -1;
    pollfdList[sock->ed].events = 0;
    pollfdList[sock->ed].revents = 0;

    sockList[sock->ed] = 0;

    while (poll_count > 0 && sockList[poll_count - 1] == 0)
        poll_count--;
}

struct IOEngine ioengine_poll = {
    "poll()",
    ioengine_poll_init,
    ioengine_poll_addsock,
    ioengine_poll_delsock
};
