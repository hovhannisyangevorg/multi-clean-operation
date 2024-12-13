#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <assert.h>
#include <ctype.h>
#include "../../header/header.h"
#include "../../error/error.h"
#include "../../utils/utils.h"
#include "../vector/vector_core/vector_core.h"

t_error* calculator(t_vector* tokens, t_error* Error);

#endif //CALCULATOR_H
