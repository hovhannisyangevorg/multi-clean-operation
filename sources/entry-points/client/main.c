#include "client_handler.h"

int main () {
    t_error     Error;
    init_error(&Error);

    if (client_handler(&Error)->message) {
        Set(&Error, format(__func__, ""));
        logger(ERROR, Error.message);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}
