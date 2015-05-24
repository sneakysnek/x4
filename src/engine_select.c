#include "engines.h"
#include "log.h"

int engine_select_init(int max_conns)
{
    log_stdout("core/engine/select", 1, "attempting to initialize select() io engine");

    return 0;
}

struct Engine engine_select = {
    "select()",
    engine_select_init
};
