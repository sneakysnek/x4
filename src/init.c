#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>
#include "config.h"
#include "ioengine.h"
#include "init.h"
#include "log.h"
#include "main.h"

/**
* Function: init
* Starts initialization process
*/
void init(int *fork)
{
    log_stdout("core/init", 1, "Entering init");

    /* We cannot add a handler for SIGKILL(9) as it cannot be caught or ignored. */
    signal(SIGTERM, init_sig_handler);
    signal(SIGINT, init_sig_handler);
    signal(SIGHUP, init_sig_handler);

    if (!init_checkPid())
    {
        pid_t pid = 0;
        if (*fork) {
            init_fork(&pid);
        }

        /* Create pid file */
        init_createPid();
    }
    else
    {
        log_stderr("core/init", 1, "Error: process already running.\n");
        exit(-1);
    }

    if (ioengine_init(MAXCONNECTIONS) != 0)
    {
        log_stderr("core/init", 1, "Unable to initialize IO engine");
        exit(-1);
    }

    log_stdout("core/init", 1, "Initialization complete");
}

/**
* Function deinit
* Performs any necesary shutdown procedures
*/
void deinit()
{
    int status = remove("x4.pid");

    if (status == 0)
    {
        log_stdout("core/init/pid", 1, "Pid deleted successfully");
    }
    else
    {
        log_stderr("core/init/pid", 1, "Error: unable to delete pid");
    }
}

/**
* Function: init_sig_handler
* Called when kill signal is detected. Removes pid file and performs any needed cleanup
*/
void init_sig_handler(int signal) {
    log_stdout("core/init/signal", 1, "Received signal %s", strsignal(signal));

    switch (signal)
    {
        case SIGINT:
            x4_shutdown("Received SIGINT signal");
            break;
        case SIGTERM:
            x4_shutdown("Received SIGTERM signal");
            break;
        case SIGHUP:
            /* This is where we reload configuration, etc... */
            break;
    }
}

/**
* Function: init_createPid
* Create pid file
*/
void init_createPid()
{
    FILE *fp = NULL;
    /* Open a pid file in write mode. */
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
    if (access( "x4.pid", F_OK ) != -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
* Function: init_fork
* @param pid_t *pid The process id
* Forks and enters main loop
*/
void init_fork(pid_t *pid)
{
    pid_t sid = 0;

    /* Create child process */
    *pid = (pid_t) fork();

    /* Fork failed */
    if (*pid < 0)
    {
        printf("Error: fork failed\n");
        /* Return failure in exit status */
        exit(1);
    }

    /* kIll parent process */
    if (*pid > 0)
    {
        printf("Starting x4 in the background \n");
        /* return success in exit status */
        exit(0);
    }

    /* unmask the file mode */
    umask(0);
    /* set new session */
    sid = setsid();
    if(sid < 0)
    {
        /* Return failure */
        exit(1);
    }

    /* Close stdin. stdout and stderr */
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}
