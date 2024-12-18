#include "calculator_executor.h"

t_error* calculator_executor(char* expression, t_header* Header, t_error* Error) {
    t_vector* Vector = NULL;

    if (tokenizer_code(expression, Header->message_length, Error)->message) {
        return free_vector(&Vector), Set(Error, format(__func__, ""));
    }
    Vector = Error->value;

    if (parse(Vector, Error)->message) {
        return free_vector(&Vector), Set(Error, format(__func__, ""));
    }

    if (validator(Vector, Error)->message)
        return free_vector(&Vector), Set(Error, format(__func__, ""));

    long double result = calculator_core(Vector);
    if (Error->message) {
        return free_vector(&Vector), Set(Error, format(__func__, ""));
    }
    Error->value = itoa(round(result));
    free_vector(&Vector);
    return Error;
}