#ifndef ERROR_H
#define ERROR_H


#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/utils.h"

typedef struct s_error t_error;

struct s_error {
    char*   message;
    void*   value;
};

t_error*    init_error();
char*       format(const char *format, const char *msg);
t_error*    Set(t_error* error, char* new_error);
void        clean_up_error(t_error** Error);

#endif //ERROR_H
