#include "signals.h"

volatile sig_atomic_t stop_flag = 0;

void signal_handler(int signo) {
    printf("\n");
    logger(WARN, "Received SIGINT, cleaning up and exiting...");
    if (signo == SIGINT) {
        stop_flag = 1;
    }
}

t_sigaction init_signal() {
    t_sigaction action;
    action.sa_handler = signal_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    return action;
}
