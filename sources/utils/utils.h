#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <limits.h>
#include "../error/error.h"

size_t	err_strlen(const char *string);
char*   strjoin(char *s1, const char *s2);
char*   itoa(int n);

#endif //UTILS_H
