#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stdbool.h"

#include "calculator/vector/vector_core/vector_core.h"
#include "calculator/vector/data/data.h"
#include "../../error/error.h"


t_error* tokenizer_code(const char* expression, size_t size, t_error* Error);

#endif //TOKENIZER_H
