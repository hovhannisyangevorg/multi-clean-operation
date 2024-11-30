#include "client_handler.h"

#include "../parsing/reader/reader.h"


int main () {
    t_error*     Error = NULL;

    Error = init_error();
    if (!Error)
        logger(ERROR, "Allocation failed.");

    Error = reader(Error);
    if (Error->message)
        Set(Error, format(__func__, ""));

    logger(TRACE, Error->value);
//     if (client_handler(&Error)->message) {
//        Set(&Error, format(__func__, ""));
//        logger(ERROR, Error.message);
//        return (EXIT_FAILURE);
//    }
//    return (EXIT_SUCCESS);
}
