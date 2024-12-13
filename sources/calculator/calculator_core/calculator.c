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

int priority(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
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
        push_back(steak_value, (t_data){"", result, 0, NUMBER}, Error);
    }
    if (steak_operator->size != 0) {
        pop_front(steak_operator);
    }
    return Error;
}

t_error* calculation_with_priority(t_vector* steak_operator, t_vector* steak_value, t_data data, t_error* Error) {

    while (steak_operator->size != 0 && (priority(steak_operator->data[0].type) >=  priority(data.type))) {
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
        push_back(steak_value, (t_data){"", result, 0, NUMBER}, Error);
    }
    if (steak_operator->size != 0) {
        pop_front(steak_operator);
    }
    return Error;
}

t_error* calculator(t_vector* tokens, t_error* Error) {
    t_vector* steak_operator    = init_vector();
    t_vector* steak_value       = init_vector();

    size_t i = 0;

    while (i < tokens->size) {
        if (tokens->data[i].type == LEFT_PAREN) {
            push_back(steak_operator, tokens->data[i], Error);
        }
        else if (tokens->data[i].type == NUMBER) {
            push_back(steak_value, tokens->data[i], Error);
        }
        else if (tokens->data[i].type == RIGHT_PAREN) {
            brace_calculation(steak_operator, steak_value, Error);
        } else {
            calculation_with_priority(steak_operator, steak_value, tokens->data[i], Error);
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
        push_back(steak_value, (t_data){"", result, 0, NUMBER}, Error);
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




































































//int precedence(char op) {
//    if (op == '+' || op == '-') return 1;
//    if (op == '*' || op == '/') return 2;
//    return 0;
//}
//
//int apply_operation(int a, int b, char op, t_error* Error) {
//    switch (op) {
//    case '+': return a + b;
//    case '-': return a - b;
//    case '*': return a * b;
//    case '/':
//        if (b == 0) {
//            Set(Error, format(__func__, "Division by zero error"));
//            return 0;
//        }
//        return a / b;
//    default:
//        Set(Error, format(__func__, "Invalid operator"));
//        return 0;
//    }
//}
//
//char* int_to_string(int num) {
//    int length = snprintf(NULL, 0, "%d", num);
//    char* str = (char*)malloc(length + 1);
//    if (str != NULL) {
//        snprintf(str, length + 1, "%d", num);
//    }
//    return str;
//}
//
//t_error* calculator(char* expression, t_header* Header, t_error* Error) {
//    if (Header->message_length == 0) {
//        return Set(Error, format(__func__, "Empty expression"));
//    }
//
//    int values[Header->message_length];
//    char ops[Header->message_length];
//    int val_top = -1, op_top = -1;
//    int prev_char = 0;
//
//    for (size_t i = 0; i < strlen(expression); i++) {
//        // Skip whitespace
//        if (expression[i] == ' ') continue;
//
//        if (expression[i] == '-' && (i == 0 || strchr("+-*/(", expression[i-1]))) {
//            int value = 0;
//            i++;
//            while (i < strlen(expression) && isdigit(expression[i])) {
//                value = (value * 10) + (expression[i] - '0');
//                i++;
//            }
//            i--;
//            values[++val_top] = -value;
//            prev_char = 2;
//            continue;
//        }
//
//        if (isdigit(expression[i])) {
//            int value = 0;
//            while (i < strlen(expression) && isdigit(expression[i])) {
//                value = (value * 10) + (expression[i] - '0');
//                i++;
//            }
//            i--;
//            values[++val_top] = value;
//            prev_char = 2;
//        }
//        else if (expression[i] == '(') {
//            if (prev_char == 2 || prev_char == 3) {
//                return Set(Error, format(__func__, "Unexpected '(' after a number or closing parenthesis"));
//            }
//            ops[++op_top] = expression[i];
//            prev_char = 3;
//        }
//        else if (expression[i] == ')') {
//            if (prev_char == 1 || prev_char == 0) {
//                return Set(Error, format(__func__, "Unexpected ')' before an operator or at the start"));
//            }
//            while (op_top != -1 && ops[op_top] != '(') {
//                int b = values[val_top--];
//                int a = values[val_top--];
//                char op = ops[op_top--];
//                values[++val_top] = apply_operation(a, b, op, Error);
//            }
//            if (op_top == -1) {
//                return Set(Error, format(__func__, "Mismatched parentheses"));
//            }
//            op_top--;
//            prev_char = 2;
//        }
//        else if (strchr("+-*/", expression[i])) {
//            if (prev_char == 1 || prev_char == 0) {
//                return Set(Error, format(__func__, "Unexpected operator at the start or after another operator"));
//            }
//            while (op_top != -1 && precedence(ops[op_top]) >= precedence(expression[i])) {
//                int b = values[val_top--];
//                int a = values[val_top--];
//                char op = ops[op_top--];
//                values[++val_top] = apply_operation(a, b, op, Error);
//            }
//            ops[++op_top] = expression[i];
//            prev_char = 1;
//        }
//        else {
//            return Set(Error, format(__func__, "Invalid character in expression"));
//        }
//    }
//    if (prev_char == 1 || prev_char == 3) {
//        return Set(Error, format(__func__, "Expression cannot end with an operator or an opening parenthesis"));
//
//    }
//    while (op_top != -1) {
//        int b = values[val_top--];
//        int a = values[val_top--];
//        char op = ops[op_top--];
//        values[++val_top] = apply_operation(a, b, op, Error);
//    }
//    char* result = itoa(values[val_top]);
//    if (result == NULL) {
//        return Set(Error, format(__func__, "Conversion failed."));
//    }
//    return Error->value = result, Error;
//}