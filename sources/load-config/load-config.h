#ifndef LOAD_CONFIG_H
#define LOAD_CONFIG_H

#include "utils.h"

typedef struct s_config t_config;
typedef struct s_error_log t_error_log;

struct s_error_log {
    const char *log_server_path;
    const char *log_client_path;
};

struct s_config {
    const char* host;
    int         port;
    t_error_log log_path;
};

void    init_log(t_error_log* log);
void    init_config(t_config* config);
void    load_config(t_config* config);
void    print_config(t_config config);
char*   getEnvLocal(const char* env, const char* fallback);

#endif // LOAD_CONFIG_H