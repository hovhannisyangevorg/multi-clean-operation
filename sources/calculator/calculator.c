#include "calculator.h"

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

int apply_operation(int a, int b, char op, t_error* Error) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/':
        if (b == 0) {
            Set(Error, format(__func__, "Division by zero error"));
            return 0;  // Return a placeholder value for division by zero
        }
        return a / b;
    default:
        Set(Error, format(__func__, "Invalid operator"));
        return 0;
    }
}

char* int_to_string(int num) {
    int length = snprintf(NULL, 0, "%d", num);
    char* str = (char*)malloc(length + 1);
    if (str != NULL) {
        snprintf(str, length + 1, "%d", num);
    }
    return str;
}

t_error* calculator(char* expression, t_header* Header, t_error* Error) {
    if (Header->message_length == 0) {
        return Set(Error, format(__func__, "Empty expression"));
    }

    int values[Header->message_length];  // Stack for numbers
    char ops[Header->message_length];    // Stack for operators
    int val_top = -1, op_top = -1;      // Stack pointers
    int prev_char = 0; // 0 = none, 1 = operator, 2 = number, 3 = parenthesis

    for (size_t i = 0; i < strlen(expression); i++) {
        // Skip whitespace
        if (expression[i] == ' ') continue;

        // Check if the current character is the start of a negative number
        if (expression[i] == '-' && (i == 0 || strchr("+-*/(", expression[i-1]))) {
            int value = 0;
            i++; // Skip the '-' sign
            while (i < strlen(expression) && isdigit(expression[i])) {
                value = (value * 10) + (expression[i] - '0');
                i++;
            }
            i--; // Adjust for loop increment
            values[++val_top] = -value;  // Store the negative value
            prev_char = 2;  // This was a number
            continue;
        }

        // Push numbers to the values stack
        if (isdigit(expression[i])) {
            int value = 0;
            while (i < strlen(expression) && isdigit(expression[i])) {
                value = (value * 10) + (expression[i] - '0');
                i++;
            }
            i--; // Adjust for loop increment
            values[++val_top] = value;
            prev_char = 2;  // This was a number
        }
        // Push '(' to the ops stack
        else if (expression[i] == '(') {
            if (prev_char == 2 || prev_char == 3) {
                return Set(Error, format(__func__, "Unexpected '(' after a number or closing parenthesis"));
            }
            ops[++op_top] = expression[i];
            prev_char = 3;  // This was a parenthesis
        }
        // Evaluate everything inside parentheses
        else if (expression[i] == ')') {
            if (prev_char == 1 || prev_char == 0) {
                return Set(Error, format(__func__, "Unexpected ')' before an operator or at the start"));
            }
            while (op_top != -1 && ops[op_top] != '(') {
                int b = values[val_top--];
                int a = values[val_top--];
                char op = ops[op_top--];
                values[++val_top] = apply_operation(a, b, op, Error);
            }
            if (op_top == -1) {
                return Set(Error, format(__func__, "Mismatched parentheses"));
            }
            op_top--; // Pop '('
            prev_char = 2;  // This was a number
        }
            // Push operators to the ops stack
        else if (strchr("+-*/", expression[i])) {
            if (prev_char == 1 || prev_char == 0) {
                return Set(Error, format(__func__, "Unexpected operator at the start or after another operator"));
            }
            while (op_top != -1 && precedence(ops[op_top]) >= precedence(expression[i])) {
                int b = values[val_top--];
                int a = values[val_top--];
                char op = ops[op_top--];
                values[++val_top] = apply_operation(a, b, op, Error);
            }
            ops[++op_top] = expression[i];
            prev_char = 1;  // This was an operator
        }
        else {
            return Set(Error, format(__func__, "Invalid character in expression"));
        }
    }

    // Ensure the expression does not end with an operator or opening parenthesis
    if (prev_char == 1 || prev_char == 3) {
        return Set(Error, format(__func__, "Expression cannot end with an operator or an opening parenthesis"));

    }

    // Evaluate remaining operators
    while (op_top != -1) {
        int b = values[val_top--];
        int a = values[val_top--];
        char op = ops[op_top--];
        values[++val_top] = apply_operation(a, b, op, Error);
    }

    char* result = itoa(values[val_top]);
    if (result == NULL) {
        return Set(Error, format(__func__, "Conversion failed."));
    }
    return Error->value = result, Error;
}