#include "client_handler.h"

#include "../parsing/reader/reader.h"

#include "load-config.h"
#include "logger-system.h"
#include "error.h"

//static void init() {
//
//}

int main () {
    t_client*    Client = NULL;
    t_error*     Error  = NULL;


    Error = init_error();
    if (!Error) {
        logger(ERROR, "main: (Memory allocation failed.)");
        return (EXIT_FAILURE);
    }

    Error = init_client(Error);
    if (Error->message)
        Set(Error, format(__func__, "")), logger(ERROR, Error->message);
    Client = Error->value;
    Error->value = NULL;

    Error = reader(Error);
    if (Error->message)
        Set(Error, format(__func__, "")), logger(ERROR, Error->message);
    Client->expression = Error->value;
    Error->value = NULL;

     if (client_handler(Client, Error)->message) {
        Set(Error, format(__func__, "")), logger(ERROR, Error->message);
        return (EXIT_FAILURE);
    }

    return (EXIT_SUCCESS);
}
