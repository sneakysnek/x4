#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>
#include "init.h"

/**
* Function: init
* Starts initialization process
*/
void init()
{
    signal(SIGKILL, init_sig_handler);
    // Fork
    if (!init_checkPid()) {
        pid_t pid = 0;
        init_fork(&pid);
    } else {
        printf("Error: process already running.\n");
        exit(0);
    }
    // Load conf
    // Bind

}

/**
* Function: init_sig_handler
* Called when kill signal is detected. Removes pid file and performs any needed cleanup
*/
void init_sig_handler(int signal) {
    // TODO: remove pid file
}

/**
* Function: init_createPid
* Create pid file
*/
void init_createPid()
{
    FILE *fp = NULL;
    // Open a log file in write mode.
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

/**
* Function: init_fork
* @param pid_t *pid The process id
* Forks and enters main loop
*/
void init_fork(pid_t *pid)
{
    pid_t sid = 0;

    // Create child process
    *pid = (pid_t) fork();

    // Fork failed
    if (*pid < 0)
    {
        printf("Error: fork failed\n");
        // Return failure in exit status
        exit(1);
    }

    // kIll parent process
    if (*pid > 0)
    {
        printf("Starting x4 in the background \n");
        // return success in exit status
        exit(0);
    }

    //unmask the file mode
    umask(0);
    //set new session
    sid = setsid();
    if(sid < 0)
    {
        // Return failure
        exit(1);
    }

    // Close stdin. stdout and stderr
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // Create pid file
    init_createPid();

    while(1) {
        sleep(1);
        // TODO: add main daemon loop
    }
}
