#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <assert.h>
#include <ctype.h>
#include "../header/header.h"
#include "../error/error.h"
#include "../../utils/utils.h"

t_error* calculator(char* expression, t_header* Header, t_error* Error) ;

#endif //CALCULATOR_H
