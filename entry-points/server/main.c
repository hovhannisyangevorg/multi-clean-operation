#include "../../sources/server/server_core/server.h"

int main () {
    t_error*    Error = NULL;
    t_server*   Server = NULL;
    t_config*   ConfigServer = NULL;

    Error = init_error();
    if (!Error) {
        return logger(ERROR, "main: Allocation failed."), EXIT_FAILURE;
    }

    if (init_server(Error)->message) {
        Set(Error, format(__func__, ""));
        logger(ERROR, Error->message);
        clean_up_error(&Error);
        return EXIT_FAILURE;
    }
    Server = Error->value;

    if (init_config(Error)->message) {
        Set(Error, format(__func__, ""));
        logger(ERROR, Error->message);
        clean_up_error(&Error);
        clean_up_server(&Server);
        return EXIT_FAILURE;
    }
    ConfigServer = Error->value;

    if (server(ConfigServer, Server, Error)->message) {
        Set(Error, format(__func__, ""));
        logger(ERROR, Error->message);
        clean_up_error(&Error);
        clean_up_server(&Server);
        clean_up_config(&ConfigServer);
        return EXIT_FAILURE;
    }
    clean_up_error(&Error);
    clean_up_server(&Server);
    clean_up_config(&ConfigServer);

    return (EXIT_SUCCESS);
}
