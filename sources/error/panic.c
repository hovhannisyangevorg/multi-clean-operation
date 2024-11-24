#include "panic.h"

void init_log(t_error_log* log) {
    if (!log)
        return;
    log->log_server_path = NULL;
    log->log_cilent_path = NULL;
}
