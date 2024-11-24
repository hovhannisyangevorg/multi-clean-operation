#ifndef LOAD_CONFIG_H
#define LOAD_CONFIG_H

#include "utils.h"
#include "panic.h"

typedef struct s_config t_config;

struct s_config {
    const char* host;
    int         port;
    t_error_log log_path;
};


void    init_config(t_config* config);
void    load_config(t_config* config);
void    print_config(t_config config);
char*   getEnvLocal(const char* env, const char* fallback);

#endif // LOAD_CONFIG_H