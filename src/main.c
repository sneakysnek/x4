#include <stdio.h>
#include "init.h"

int main(int argc, char* argv[])
{
    init();
    while(1) {
        sleep(1);
        /* TODO: add main daemon loop */
    }
    return 0;
}
