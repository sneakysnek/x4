#include "engines.h"

int engine_init(int max_conns)
{
    return 0;
}

struct Engine engine_select = {
    "select()",
    engine_init
};
