#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "ioengine.h"
#include "log.h"

/* Maximum file descriptor currently used. */
static int highest_fd;
/* Global read event interest bitmap. */
static fd_set global_read_set;
/* Global write event interest bitmap. */
static fd_set global_write_set;

int ioengine_select_init(int max_conns)
{
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

    highest_fd = -1; /* No fds in set */

    return 0;
}

struct IOEngine ioengine_select = {
    "select()",
    ioengine_select_init
};
