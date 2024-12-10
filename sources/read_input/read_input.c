#include "read_input.h"

t_error*   reader(t_error* Error) {
    logger(INFO, "Enter an operator (+, -, *, /): \b");
    char*   line;
    const char* et = "$> ";

    line = readline(et);
    if (!line)
        Set(Error, format(__func__, "(Input ended or an error occurred.)"));
    Error->value = line;
    return (Error);
}