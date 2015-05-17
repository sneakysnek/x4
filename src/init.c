#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "init.h"

/**
* Function: init
* Starts initialization process
*/
void init()
{
    signal(SIGKILL, init_sig_handler);
    init_createPid();
}

/**
* Function: init_sig_handler
* Called when kill signal is detected. Removes pid file and performs any needed cleanup
*/
void init_sig_handler(int signal) {
    /* TODO: remove pid file */
}

/**
* Function: init_createPid
* Create pid file
*/
void init_createPid()
{
    FILE *fp = NULL;
    /* Open a log file in write mode. */
    fp = fopen ("x4.pid", "w+");
    fprintf(fp,"%i\n", (int)getpid());
    fflush(fp);
    fclose(fp);
}

/**
* Function: init_checkPid
* Checks whether the pid file exists
*/
int init_checkPid()
{
    if( access( "x4.pid", F_OK ) != -1 ) {
        return 1;
    } else {
        return 0;
    }
}
