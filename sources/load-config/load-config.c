#include "load-config.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dotenv.h>

#include "logger-system.h"
#include "panic.h"

static void init() {
    logger(INFO, "Loading environment variables from the specified file ...");
    const char *env_file_path = ".env";

    if (env_load(env_file_path, true) != 0) {
        logger(ERROR, "loading .env file from ...");
        return ;
    }
}

void init_config(t_config* config) {
    config->host = NULL;
    config->port = 0;
    init_log(&config->log_path);
}

char* getEnvLocal(const char* env, const char* fallback) {
    const char* environment = getenv(env);

    if(environment == NULL) {
        logger(ERROR, "MESSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS");
    }

    if (fallback != NULL) {
        return strdup(fallback);
    }
    if (environment != NULL) {
        return strdup(environment);
    }
    return NULL;
}

void load_config(t_config* config) {
    init();

    config->host = getEnvLocal("SERVER_HOST", NULL);
    if (config->host == NULL) {
        config->host = "127.0.0.1";
    }

    char* temp_port = getEnvLocal("SERVER_PORT", NULL);
    if (temp_port != NULL) {
        config->port = atoi(temp_port);
    }

    char* temporary_server = getEnvLocal("SERVER_LOGS_FILE", NULL);
    if (temporary_server != NULL) {
        config->log_path.log_server_path = "/var/log/multi-clean-operation/server-logs.log";
    }

    char* temporary_client = getEnvLocal("CLIENT_LOGS_FILE", NULL);
    if (temporary_client != NULL) {
        config->log_path.log_cilent_path = "/var/log/multi-clean-operation/client-logs.log";
    }
}

void print_config(t_config config) {
    printf("Host: %s%s", config.host, "\n");
    printf("Host: %d%s", config.port, "\n");
    printf("ServerLogsPath: %s%s", config.log_path.log_server_path, "\n");
    printf("ClientLogsPath: %s%s", config.log_path.log_cilent_path, "\n");
}