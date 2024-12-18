#ifndef CALCULATOR_CORE_H
#define CALCULATOR_CORE_H

#include <math.h>
#include <assert.h>
#include <ctype.h>
#include "../../header/header.h"
#include "../../error/error.h"
#include "../../utils/utils.h"
#include "../vector/vector_core/vector_core.h"

long double calculator_core(t_vector* tokens);

#endif //CALCULATOR_CORE_H
