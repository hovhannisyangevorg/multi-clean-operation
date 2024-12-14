#include "calculator.h"

//    NUMBER      = 1 << 1,
//    OPER_ADD    = 1 << 2,
//    OPER_SUB    = 1 << 3,
//    OPER_MUL    = 1 << 4,
//    OPER_DIV    = 1 << 5,
//    LEFT_PAREN  = 1 << 6,
//    RIGHT_PAREN = 1 << 7,
//    REGULAR     = 1 << 8,
//    UNKNOWN     = 1 << 9

int priority(t_type type) {
    if (type == OPER_ADD || type == OPER_SUB)
        return 1;
    if (type == OPER_MUL || type == OPER_DIV)
        return 2;
    return 0;
}

long double do_operation(long double a, long double b, t_type op) {
    if (op == OPER_ADD)
        return a + b;
    if (op == OPER_SUB)
        return a - b;
    if (op == OPER_MUL)
        return a * b;
    return a / b;
}

t_error* brace_calculation(t_vector* steak_operator, t_vector* steak_value, t_error* Error) {
    print_vector(steak_operator);
    while (steak_operator->size != 0 && steak_operator->data[0].type != LEFT_PAREN) {
        long double f_value;

        if (steak_value->size == 0)
            f_value = 0;
        else
            f_value = steak_value->data[0].value;
        pop_front(steak_value);

        long double s_value;

        if (steak_value->size == 0)
            s_value = 0;
        else
            s_value = steak_value->data[0].value;
        pop_front(steak_value);

        char op_value;
        if (steak_operator->size == 0)
            op_value = 0;
        else
            op_value = steak_operator->data[0].type;
        pop_front(steak_operator);
        long double result = do_operation(f_value, s_value, op_value);
        push_front(steak_value, (t_data){"", result, 0, NUMBER});
    }
    if (steak_operator->size != 0) {
        pop_front(steak_operator);
    }
    return Error;
}

t_error* calculation_with_priority(t_vector* steak_operator, t_vector* steak_value, t_data data, t_error* Error) {
//        printf("##################>%s\n", type_to_string(op_value));

    while (steak_operator->size != 0 && (priority(steak_operator->data[0].type) >=  priority(data.type))) {
        long double f_value;

        if (steak_value->size == 0)
            f_value = 0;
        else
            f_value = steak_value->data[0].value;
        pop_front(steak_value);

        long double s_value;

        if (steak_value->size == 0) {
            s_value = 0;
        }
        else {
            s_value = steak_value->data[0].value;
        }
        pop_front(steak_value);

        char op_value;
        if (steak_operator->size == 0)
            op_value = 0;
        else
            op_value = steak_operator->data[0].type;
        pop_front(steak_operator);
        long double result = do_operation(f_value, s_value, op_value);
        push_front(steak_value, (t_data){.token = "", .value = result, .size = 0, .type = NUMBER});
    }
    if (steak_operator->size != 0) {
        pop_front(steak_operator);
    }
    return Error;
}

bool id_operator(t_type type) {
    return type == OPER_MUL || type == OPER_SUB || type == OPER_ADD || type == OPER_DIV || type == LEFT_PAREN;
}

t_error* calculator(t_vector* tokens, t_error* Error) {
    t_vector* steak_operator    = init_vector();
    t_vector* steak_value       = init_vector();

    size_t i = 0;

    print_vector(tokens);
    while (i < tokens->size) {
        if (id_operator(tokens->data[i].type)) {
            push_front(steak_operator, tokens->data[i]);
        }
        else if (tokens->data[i].type == NUMBER) {
            push_front(steak_value, tokens->data[i]);
        }
        else if (tokens->data[i].type == RIGHT_PAREN) {
            brace_calculation(steak_operator, steak_value, Error);
        } else {
            calculation_with_priority(steak_operator, steak_value, tokens->data[i], Error);
        }
        ++i;
//        print_vector(steak_operator);
    }

    while (steak_operator->size != 0) {
        long double f_value;

        if (steak_value->size == 0)
            f_value = 0;
        else
            f_value = steak_value->data[0].value;
        pop_front(steak_value);

        long double s_value;

        if (steak_value->size == 0)
            s_value = 0;
        else
            s_value = steak_value->data[0].value;
        pop_front(steak_value);

        char op_value;
        if (steak_operator->size == 0)
            op_value = 0;
        else
            op_value = steak_operator->data[0].type;
        pop_front(steak_operator);
        long double result = do_operation(f_value, s_value, op_value);
        push_front(steak_value, (t_data){"", result, 0, NUMBER});

//        printf("%LF, %LF, %d\n", f_value, s_value, op_value);
    }

    long double result;
    if (steak_value->size == 0) {
        result = 0;
    }
    else {
        result = steak_value->data[0].value;
    }
    printf("Result: %LF\n", result);
    return Error;
}
