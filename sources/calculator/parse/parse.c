#include "parse.h"


t_error* parse(t_vector* Vector, t_error* Error) {
    size_t i = 0;

    while(i < Vector->size) {
        if (Vector->data[i].type == NUMBER) {
            char* pEnd = NULL;
            Vector->data[i].value = strtold(Vector->data[i].token, &pEnd);
            if (!pEnd) {
                return Set(Error, format(__func__, "Invalid character in expression"));
            }
        }
        ++i;
    }
    return Error;
}