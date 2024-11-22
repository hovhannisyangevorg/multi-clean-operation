#ifndef LOAD_CONFIG_H
#define LOAD_CONFIG_H

#include "utils.h"

typedef struct s_config t_config;

struct s_config {
    const char* host;
    int         port;
};

void    load_config(t_config* config);
void    print_config(t_config config);
char*   getEnvLocal(const char* env, const char* fallback);

#endif // LOAD_CONFIG_H