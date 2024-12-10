#include "load-config.h"

static t_error* init(t_error* Error) {
    logger(INFO, "Loading environment variables from the specified file ...");
    const char *env_file_path = ".env";

    if (env_load(env_file_path, true) != 0) {
        return Set(Error, format(__func__, "loading .env file from ..."));
    }
    return (Error);
}

static t_error* getEnvLocal(const char* env, const char* fallback, t_error* Error) {
    if (fallback) {
        Error->value = strdup(fallback);
        return (Error);
    }
    const char* environment = getenv(env);
    if (!environment) {
        return (Set(Error, format(__func__, "(Failed to load environment variable from local.)")));
    }
    Error->value = strdup(environment);
    return (Error);
}

static t_error* parse_integer(const char* string, t_error* Error) {
    char *pointer;
    long* result = calloc(1, sizeof(long));

    *result = strtol(string, &pointer, 10);
    errno = 0;
    if (*pointer == '\0' && errno != ERANGE && *result >= INT_MIN && *result <= INT_MAX) {
        return Error->value = result, Error;
    } else {
        return Set(Error, format(__func__, "(Invalid integer or out-of-range value.)"));
    }
}

t_error* init_config(t_error* Error) {
    t_config* server_tmp = NULL;

    server_tmp = (t_config*)calloc(1, sizeof(t_config));
    if (!server_tmp) {
        return (Set(Error, format(__func__, "(Memory allocation failed.)")));
    }
    return (Error->value = server_tmp, Error);
}

t_error* getEnvInteger(const char* env, const char* fallback, t_error* Error) {
    if (getEnvLocal(env, fallback, Error)->message) {
        return Set(Error, format(__func__, ""));
    }

    char* tmp_port = Error->value;
    if (parse_integer(tmp_port, Error)->message) {
        return Set(Error, format(__func__, ""));
    }
    free(tmp_port);
    return Error;
}

t_error* load_config(t_config* config, t_error* Error) {
    if(init(Error)->message) {
        return Set(Error, format(__func__, ""));
    }

    if (getEnvLocal("SERVER_HOST", NULL, Error)->message) {
        return Set(Error, format(__func__, ""));
    }
    config->host = Error->value;

    if (getEnvInteger("SERVER_PORT", NULL, Error)->message) {
        return Set(Error, format(__func__, ""));
    }
    config->port = *((int *)Error->value);
    free((int*)(Error->value));

    if (getEnvInteger("BACK_LOG", NULL, Error)->message) {
        return Set(Error, format(__func__, ""));
    }
    config->backlog = *((int *)Error->value);
    free((int *)Error->value);

    if (getEnvLocal("SERVER_LOGS_FILE", NULL, Error)->message) {
        return Set(Error, format(__func__, ""));
    }
    config->log_path.log_server_path = Error->value;

    if (getEnvLocal("CLIENT_LOGS_FILE", NULL, Error)->message) {
        return Set(Error, format(__func__, ""));
    }
    config->log_path.log_client_path = Error->value;

    return Error->value = config, Error;
}

void print_config(t_config config) {
    printf("Host: %s%s", config.host, "\n");
    printf("Port: %d%s", config.port, "\n");
    printf("Backlog: %d%s", config.backlog, "\n");
    printf("Server Logs Path: %s%s", config.log_path.log_server_path, "\n");
    printf("Client Logs Path: %s%s", config.log_path.log_client_path, "\n");
}

// Function to free memory for the t_error_log struct
void free_error_log(t_error_log* error_log) {
    if (error_log->log_client_path) {
        free(error_log->log_client_path);
    }
    if (error_log->log_server_path) {
        free(error_log->log_server_path);
    }
}

// Function to free memory for the t_config struct
void clean_up_config(t_config** config) {
    if (config && *config) {
        if ((*config)->host) {
            free((*config)->host);
        }
        free_error_log(&(*config)->log_path);
        free(*config);
        *config = NULL;  // Correctly nullifying the caller's pointer
    }
}