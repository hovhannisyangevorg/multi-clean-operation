#ifndef CALCULATOR_EXECUTOR_H
#define CALCULATOR_EXECUTOR_H

#include <math.h>

#include "../../error/error.h"
#include "../../header/header.h"
#include "../tokenizer/tokenizer.h"
#include "../parse/parse.h"
#include "../validator/validator.h"
#include "../calculator_core/calculator_core.h"

t_error* calculator_executor(char* expression, t_header* Header, t_error* Error);

#endif //CALCULATOR_EXECUTOR_H
