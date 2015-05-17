#ifndef _init_h
#define _init_h
#include <sys/types.h>

void init(int *fork);
void init_createPid();
int init_checkPid();
void init_sig_handler(int sig);
void init_fork(pid_t *pid);

#endif