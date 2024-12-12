#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../logger-system/logger-system.h"

typedef struct s_vector t_vector;
//typedef struct s_data   t_data;
//
//struct s_data {
//
//};

struct s_vector {
    char    **data;
    size_t  size;
    size_t  capacity;
};

t_vector* init_vector();
size_t calculate_capacity(t_vector* vector);
long resize_vector(t_vector* vector);
void push_back(t_vector* Vector, char* token);
void push_front(t_vector* vector, const char* str);
void pop_back(t_vector* vector);
void pop_front(t_vector* vector);
void free_vector(t_vector** vector);
void print_vector(t_vector* vector);

#endif //VECTOR_H
