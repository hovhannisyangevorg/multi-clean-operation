#ifndef DATA_H
#define DATA_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct  s_data      t_data;
typedef enum    s_type      t_type;

enum s_type {
    NUMBER      = 1 << 1,
    OPER_ADD    = 1 << 2,
    OPER_SUB    = 1 << 3,
    OPER_MUL    = 1 << 4,
    OPER_DIV    = 1 << 5,
    LEFT_PAREN  = 1 << 6,
    RIGHT_PAREN = 1 << 7,
    UNKNOWN     = 1 << 8
};

struct s_data {
    char*           token;
    long double     value;
    size_t          size;
    t_type          type;
};

t_data* init_data();
t_type  to_type(char ch);
char*   type_to_string(t_type type);
bool is_operator(t_type type);
void clean_up_data(t_data* data);
void free_data(t_data* data, size_t size);
#endif //DATA_H
