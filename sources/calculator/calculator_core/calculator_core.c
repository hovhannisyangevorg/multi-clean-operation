#include "calculator_core.h"

static int priority(t_type type) {
    if (type == OPER_ADD || type == OPER_SUB)
        return 1;
    if (type == OPER_MUL || type == OPER_DIV)
        return 2;
    return 0;
}

static long double do_operation(long double a, long double b, t_type op) {
    if (op == OPER_ADD)
        return a + b;
    if (op == OPER_SUB)
        return b - a;
    if (op == OPER_MUL)
        return a * b;
    return b / a;
}

static void brace_calculation(t_vector* steak_operator, t_vector* steak_value) {
    while (steak_operator->size != 0 && steak_operator->data[0].type != LEFT_PAREN) {
        long double f_value;

        if (steak_value->size == 0) {
            f_value = 0;
        } else {
            f_value = steak_value->data[0].value;
        }
        pop_front(steak_value);

        long double s_value;

        if (steak_value->size == 0) {
            s_value = 0;
        } else {
            s_value = steak_value->data[0].value;
        }
        pop_front(steak_value);

        char op_value;
        if (steak_operator->size == 0) {
            op_value = 0;
        } else {
            op_value = steak_operator->data[0].type;
        }
        pop_front(steak_operator);
        long double result = do_operation(f_value, s_value, op_value);


        t_data tmp_data = {
            .token = "",
            .value = result,
            .type = NUMBER,
            .size = 0
        };
        push_front(steak_value, &tmp_data);
    }
    if (steak_operator->size != 0) {
        pop_front(steak_operator);
    }
}

static void calculation_with_priority(t_vector* steak_operator, t_vector* steak_value, t_data data) {
    while (steak_operator->size != 0 && (priority(steak_operator->data[0].type) >=  priority(data.type))) {
        long double f_value;

        if (steak_value->size == 0) {
            f_value = 0;
        }
        else {
            f_value = steak_value->data[0].value;
        }
        pop_front(steak_value);

        long double s_value;

        if (steak_value->size == 0) {
            s_value = 0;
        } else {
            s_value = steak_value->data[0].value;
        }
        pop_front(steak_value);

        char op_value;
        if (steak_operator->size == 0) {
            op_value = 0;
        }
        else {
            op_value = steak_operator->data[0].type;
        }
        pop_front(steak_operator);
        long double result = do_operation(f_value, s_value, op_value);
        t_data tmp_data = {
            .token = "",
            .value = result,
            .type = NUMBER,
            .size = 0
        };
        push_front(steak_value, &tmp_data);
    }
}

long double calculator_core(t_vector* tokens) {
    t_vector* steak_operator    = init_vector();
    t_vector* steak_value       = init_vector();

    size_t i = 0;
    while (i < tokens->size) {
        if (tokens->data[i].type == LEFT_PAREN) {
            if ((i+1) < tokens->size && tokens->data[i + 1].type == OPER_SUB) {
                t_data tmp_data = {
                    .token = "",
                    .value = 0,
                    .type = NUMBER,
                    .size = 0
                };
                push_front(steak_value, &tmp_data);
            }
            push_front(steak_operator, &tokens->data[i]);
        }
        else if (tokens->data[i].type == NUMBER) {
            t_data tmp_data = {
                .token = tokens->data[i].token,
                .value = tokens->data[i].value,
                .type = tokens->data[i].type,
                .size = tokens->data[i].size
            };
            push_front(steak_value, &tmp_data);
        }
        else if (tokens->data[i].type == RIGHT_PAREN) {
            brace_calculation(steak_operator, steak_value);
        } else {
            calculation_with_priority(steak_operator, steak_value, tokens->data[i]);
            push_front(steak_operator, &tokens->data[i]);
        }
        ++i;
    }

    while (steak_operator->size != 0) {
        long double f_value;

        if (steak_value->size == 0)
            f_value = 0;
        else
            f_value = steak_value->data[0].value;
        pop_front(steak_value);

        long double s_value;

        if (steak_value->size == 0) {
            s_value = 0;
        } else {
            s_value = steak_value->data[0].value;
        }
        pop_front(steak_value);

        char op_value;
        if (steak_operator->size == 0) {
            op_value = 0;
        }
        else {
            op_value = steak_operator->data[0].type;
        }
        pop_front(steak_operator);
        long double result = do_operation(f_value, s_value, op_value);
        t_data tmp = {"", result, 0, NUMBER};
        push_front(steak_value, &tmp);
    }

    long double result;
    if (steak_value->size == 0) {
        result = 0;
    }
    else {
        result = steak_value->data[0].value;
    }

    free_vector(&steak_value);
    free_vector(&steak_operator);
    return result;
}
