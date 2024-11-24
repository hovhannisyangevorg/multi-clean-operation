#ifndef PANIC_HPP
#define PANIC_HPP

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "utils.h"

typedef struct s_error_log t_error_log;

struct s_error_log {
    const char *log_server_path;
    const char *log_cilent_path;
};

void init_log(t_error_log* log);

#endif //PANIC_HPP