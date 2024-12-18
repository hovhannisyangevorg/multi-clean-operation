#ifndef CALCULATOR_EXECUTOR_TEST_H
#define CALCULATOR_EXECUTOR_TEST_H

#include <stddef.h>
#include <string.h>
#include <assert.h>


#include "../../error/error.h"
#include "../tokenizer/tokenizer.h"
#include "../parse/parse.h"
#include "../validator/validator.h"
#include "../calculator_core/calculator_core.h"

typedef struct s_tests t_tests;

struct s_tests {
    char        *expression;
    long double expected;
};


t_error* calculator_executor_test(t_error* Error);

#endif //CALCULATOR_EXECUTOR_TEST_H
