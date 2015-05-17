#ifndef _init_h
#define _init_h
#include <sys/types.h>

void init();
void init_createPid();
int init_checkPid();
void init_sig_handler(int sig);

#endif