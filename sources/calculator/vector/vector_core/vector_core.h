#ifndef VECTOR_CORE_H
#define VECTOR_CORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../logger-system/logger-system.h"
#include "../data/data.h"
#include "../../../utils/utils.h"

typedef struct  s_vector    t_vector;

struct s_vector {
    t_data  *data;
    size_t  size;
    size_t  capacity;
};

t_vector* init_vector();
void push_front(t_vector* Vector, t_data data);
void push_back(t_vector* Vector, t_data data);
void pop_back(t_vector* Vector);
void pop_front(t_vector* Vector);
void free_vector(t_vector** Vector);
void print_vector(t_vector* Vector);

#endif //VECTOR_CORE_H
