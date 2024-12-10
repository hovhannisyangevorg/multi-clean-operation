#include "../../sources/client/client_core/client.h"

int main () {
    t_client*   Client = NULL;
    t_error*    Error = NULL;
    t_config*   ConfigClient = NULL;

    Error = init_error();
    if (!Error) {
        return logger(ERROR, "main: (Memory allocation failed.)"), EXIT_FAILURE;
    }

    if (init_client(Error)->message) {
        Set(Error, format(__func__, ""));
        logger(ERROR, Error->message);
        clean_up_error(&Error);
        return EXIT_FAILURE;
    }
    Client = Error->value;

    if (init_config(Error)->message) {
        Set(Error, format(__func__, ""));
        logger(ERROR, Error->message);
        clean_up_error(&Error);
        clean_up_client(&Client);
        return EXIT_FAILURE;
    }
    ConfigClient = Error->value;

    if (reader(Error)->message){
        Set(Error, format(__func__, ""));
        logger(ERROR, Error->message);
        clean_up_error(&Error);
        clean_up_client(&Client);
        clean_up_config(&ConfigClient);
        return EXIT_FAILURE;
    }
    Client->expression = Error->value;

    if (client_handler(ConfigClient, Client, Error)->message) {
        Set(Error, format(__func__, ""));
        logger(ERROR, Error->message);
        clean_up_error(&Error);
        clean_up_client(&Client);
        clean_up_config(&ConfigClient);
        return EXIT_FAILURE;
    }

    clean_up_error(&Error);
    clean_up_client(&Client);
    clean_up_config(&ConfigClient);
    return (EXIT_SUCCESS);
}

