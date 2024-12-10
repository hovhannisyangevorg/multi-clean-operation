#ifndef SERVER_SIGNALS_H
#define SERVER_SIGNALS_H


#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <stdio.h>
#include <signal.h>
#include "../logger-system/logger-system.h"

typedef struct sigaction t_sigaction;


extern volatile sig_atomic_t stop_flag;

t_sigaction init_signal();


#endif // SERVER_SIGNALS_H
