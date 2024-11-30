#include "reader.h"

t_error*   reader(t_error* Error) {
    char*   line;
    const char* et = "Enter an operator (+, -, *, /): ";

    line = readline(et);
    if (!line)
        Set(Error, format(__func__, "(Input ended or an error occurred.)"));
    Error->value = line;
    return (Error);
}