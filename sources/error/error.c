#include "error.h"

t_error* init_error(){
    t_error* Error;

    Error = malloc(1 * sizeof(t_error));
    if (Error == NULL)
        return (NULL);
    return (Error);
}

char	*format(const char *format, const char *msg) {
    char	*res;

    res = NULL;
    res = strjoin(res, format);
    if (*res)
        res = strjoin(res, ": ");
    res = strjoin(res, msg);
    return (res);
}

t_error* Set(t_error* error, char* new_error) {
    char	*string = NULL;

    if (!error)
        return (NULL);

    string = strjoin(new_error, error->message);
    free(error->message);
    error->message = NULL;
    error->message = string;
    return (error);
}

