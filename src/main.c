#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>
#include "init.h"

int main(int argc, char* argv[])
{
    if (!init_checkPid()) {
        pid_t pid = 0;
        pid_t sid = 0;

        /* Create child process */
        pid = (pid_t) fork();

        /* Fork failed */
        if (pid < 0)
        {
            printf("Error: fork failed\n");
            // Return failure in exit status
            exit(1);
        }

        /* kIll parent process */
        if (pid > 0)
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

        /* Init */
        init();

        /* Load config */

        /* Bind */

        while(1) {
            sleep(1);
            /* TODO: add main daemon loop */
        }
    } else {
        printf("Error: process already running.\n");
        exit(0);
    }
    return 0;
}
