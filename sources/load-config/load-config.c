#include "load-config.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "logger-system.h"
#include <dotenv.h>

static void init() {
    logger(TRACE, "Load environment variables from the specified file ...");
    const char *env_file_path = ".env";

    if (env_load(env_file_path, true) != 0) {
        logger(ERROR, "loading .env file from ...");
        return ;
    }
}

void load_config(t_config* config) {
    init();

    config->host = getEnvLocal("SERVER_HOST", NULL);
    if (config->host == NULL) {
        config->host = "127.0.0.1";
    }

    char* port_str = getEnvLocal("SERVER_PORT", NULL);
    if (port_str != NULL) {
        config->port = atoi(port_str);
    }
}

char* getEnvLocal(const char* env, const char* fallback) {
    const char* environment = getenv(env);

    if (fallback != NULL) {
        return strdup(fallback);
    }
    if (environment != NULL) {
        return strdup(environment);
    }
    return NULL;
}

void print_config(t_config config) {
    printf("Host: %s%s", config.host, "\n");
    printf("Host: %d%s", config.port, "\n");
}