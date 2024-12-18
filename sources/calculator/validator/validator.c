#include "validator.h"

size_t search_end_brace(t_vector* Vector) {
    for (int i = (Vector->size - 1); i >= 0; --i) {
        if (Vector->data[i].type == RIGHT_PAREN)
            return i;
    }
    return -1;
}

t_error* is_brace_balanced(t_vector* Vector, t_error* Error) {

    size_t is_balance = 0;

    for (size_t i = 0; i < Vector->size; ++i) {
        if (Vector->data[i].type == LEFT_PAREN)
            is_balance++;
        if (Vector->data[i].type == RIGHT_PAREN)
            is_balance--;
    }
    if (is_balance != 0)
        return Set(Error, format(__func__, "(braces is not balanced.)"));
    return Error;
}

t_error* is_valid_expression(t_vector* Vector, t_error* Error) {
    int valid_number = 0;
    int valid_operator = 0;

    for (size_t i = 0; i < Vector->size; ++i)  {
        if (is_operator(Vector->data[i].type))
            valid_operator++;
        if (Vector->data[i].type)
            valid_number++;
    }

    if (valid_operator < 1)
        return Set(Error, format(__func__, "(invalid expression.)"));
    if (valid_number < 2)
        return Set(Error, format(__func__, "(invalid expression.)"));
    return Error;
}

t_error* validator(t_vector* Vector, t_error* Error) {
    const size_t min_expression_size = 3;

    for (size_t i = 1; i < Vector->size; ++i) {
        t_type type = Vector->data[i].type;

        if (Vector->size < min_expression_size)
            return Set(Error, format(__func__, "(invalid expression.)"));

        if (is_brace_balanced(Vector, Error)->message)
            return Set(Error, format(__func__, ""));

        if (is_valid_expression(Vector, Error)->message)
            return Set(Error, format(__func__, ""));

        if (is_operator(Vector->data[i - 1].type) && is_operator(type)) {
            return Set(Error, format(__func__, "(Two operators are next to each other.)"));
        }

        if (type == RIGHT_PAREN && is_operator(Vector->data[i - 1].type)) {
            return Set(Error, format(__func__, "(Before close brace it should be a number.)"));
        }

        size_t end_brace = search_end_brace(Vector);

        if (end_brace != (size_t)(-1)) {
            size_t end_next     = end_brace + 1;
            size_t next_namber  = end_brace  + 2;

            if ((end_next < Vector->size && next_namber < Vector->size) && (is_operator(Vector->data[end_next].type) && Vector->data[next_namber].type != NUMBER && Vector->data[next_namber].type != LEFT_PAREN)) {
                return Set(Error, format(__func__, "(Missing number after operator.)"));
            }
        }
    }
    return Error;
}