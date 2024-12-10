#include "error.h"

t_error* init_error(){
    t_error* Error;

    Error = (t_error*)calloc(1, sizeof(t_error));
    if (Error == NULL)
        return (NULL);
    return (Error);
}

char	*format(const char *format, const char *msg) {
    char*   res = NULL;

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

void clean_up_error(t_error** Error) {
    if (Error && *Error){
        if ((*Error)->message) {
            free((*Error)->message);
        }
        free(*Error);
        *Error = NULL;
    }
}

