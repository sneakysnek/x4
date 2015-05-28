#include <assert.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "ioengine.h"
#include "log.h"

/** Array of active Socket structures, indexed by file descriptor. */
static struct Socket* sockList[FD_SETSIZE];
/* Maximum file descriptor currently used. */
static int highest_fd;
/* Global read event interest bitmap. */
static fd_set global_read_set;
/* Global write event interest bitmap. */
static fd_set global_write_set;

int ioengine_select_init(int max_conns)
{
    int i = 0;

    log_stdout("core/ioengine/select", 1,
               "attempting to initialize select() io engine");

    if (max_conns > FD_SETSIZE)
    {
        log_stderr("core/ioengine/select", 1,
                   "select() engine cannot handle %d sockets (> %d)",
                   max_conns, FD_SETSIZE);
        return -1;
    }

    FD_ZERO(&global_read_set); /* zero the global fd sets */
    FD_ZERO(&global_write_set);

    for (i = 0; i < FD_SETSIZE; i++) /* zero the sockList */
        sockList[i] = 0;

    highest_fd = -1; /* No fds in set */

    return 0;
}

int ioengine_select_addsocket(struct Socket *sock)
{
    if (sock == NULL)
        return -1;

    assert(sockList[sock->fd] == 0);
    assert(sock->fd != 0);

    if (sock->fd >= FD_SETSIZE)
    {
        log_stderr("core/ioengine/select", 1,
                   "attempt to add socket %d (> %d) to io engine",
                   sock->fd, FD_SETSIZE);
        return -1;
    }

    sockList[sock->fd] = sock;

    if (sock->fd >= highest_fd)
        highest_fd = sock->fd;

    if (sock->events & SE_READ)
        FD_SET(sock->fd, &global_read_set);

    if (sock->events & SE_WRITE)
        FD_SET(sock->fd, &global_write_set);

    return 0;
}

void ioengine_select_delsocket(struct Socket *sock)
{
    if (sock == NULL)
        return;

    assert(sockList[sock->fd] != 0);
    assert(sock->fd != 0);

    sockList[sock->fd] = NULL;

    if (FD_ISSET(sock->fd, &global_read_set))
        FD_CLR(sock->fd, &global_read_set);

    if (FD_ISSET(sock->fd, &global_write_set))
        FD_CLR(sock->fd, &global_write_set);

    while (highest_fd > -1 && sockList[highest_fd] == 0)
        highest_fd--;
}

struct IOEngine ioengine_select = {
    "select()",
    ioengine_select_init,
    ioengine_select_addsocket,
    ioengine_select_delsocket
};
