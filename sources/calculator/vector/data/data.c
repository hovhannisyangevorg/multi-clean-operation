#include "data.h"

t_data* init_data() {
    t_data* date = calloc(1, sizeof(t_data));
    if (!date)
        return NULL;
    return date;
}

t_type to_type(char ch) {
    switch (ch) {
    case '+':
        return OPER_ADD;
    case '-':
        return OPER_SUB;
    case '/':
        return OPER_DIV;
    case '*':
        return OPER_MUL;
    case ')':
        return RIGHT_PAREN;
    case '(':
        return LEFT_PAREN;
    default:
        return UNKNOWN;
    }
}

char* type_to_string(t_type type) {
    switch (type) {
    case NUMBER:return strdup("NUMBER");

    case OPER_ADD:return strdup("OPER_ADD");

    case OPER_SUB:return strdup("OPER_SUB");

    case OPER_MUL:return strdup("OPER_MUL");

    case OPER_DIV:return strdup("OPER_DIV");

    case LEFT_PAREN:return strdup("LEFT_PAREN");

    case RIGHT_PAREN:return strdup("RIGHT_PAREN");

    case UNKNOWN:return strdup("UNKNOWN");
    default:return strdup("REGULAR");
    }
}

#include <stdio.h>

bool is_operator(t_type type) {
    return type == OPER_MUL || type == OPER_SUB || type == OPER_ADD || type == OPER_DIV;
}

void clean_up_data(t_data* data) {
    if (data == NULL) {
        return;
    }

    if (data->token != NULL) {
        free(data->token);
        data->token = NULL;
        data->size = 0;
    }
}


void free_data(t_data* data, size_t size) {
    if (data == NULL) {
        return;
    }

    for (size_t i = 0; i < size; ++i) {
        clean_up_data(&data[i]);
    }
    free(data);
}