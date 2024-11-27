#ifndef ERROR_HPP
#define ERROR_HPP


#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

typedef struct s_error t_error;

struct s_error {
    char*   message;
    void*   value;
};

void        init_error(t_error* error);
char*       format(const char *format, const char *msg);
t_error*    Set(t_error* error, char* new_error);

#endif //ERROR_HPP
