#ifndef LOAD_CONFIG_H
#define LOAD_CONFIG_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dotenv.h>
#include <limits.h>
#include <errno.h>

#include "error.h"
#include "utils.h"
#include "logger-system.h"

typedef struct s_config t_config;
typedef struct s_error_log t_error_log;

struct s_error_log {
    char *log_server_path;
    char *log_client_path;
};

struct s_config {
    char*       host;
    int         port;
    int         backlog;
    t_error_log log_path;
};

t_error*    init_config(t_error* Error);
t_error*    load_config(t_config* config, t_error* Error);
void        print_config(t_config config);
void        clean_up_config(t_config** config);
#endif // LOAD_CONFIG_H