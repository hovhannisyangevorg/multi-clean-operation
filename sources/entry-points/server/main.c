#include "server.h"
#include "error.h"

int main () {
    t_error*     Error = NULL;

    Error = init_error();
    if (!Error)
        logger(ERROR, "Allocation failed.");

    if (server(Error)->message) {
       Set(Error, format(__func__, ""));
       logger(ERROR, Error->message);
       return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}
