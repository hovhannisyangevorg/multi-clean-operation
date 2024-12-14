#include "../../sources/server/server_core/server.h"

//int main () {
//    t_error*    Error = NULL;
//    t_server*   Server = NULL;
//    t_config*   ConfigServer = NULL;
//
//    Error = init_error();
//    if (!Error) {
//        return logger(ERROR, "main: Allocation failed."), EXIT_FAILURE;
//    }
//
//    if (init_server(Error)->message) {
//        Set(Error, format(__func__, ""));
//        logger(ERROR, Error->message);
//        clean_up_error(&Error);
//        return EXIT_FAILURE;
//    }
//    Server = Error->value;
//
//    if (init_config(Error)->message) {
//        Set(Error, format(__func__, ""));
//        logger(ERROR, Error->message);
//        clean_up_error(&Error);
//        clean_up_server(&Server);
//        return EXIT_FAILURE;
//    }
//    ConfigServer = Error->value;
//
//    if (server(ConfigServer, Server, Error)->message) {
//        Set(Error, format(__func__, ""));
//        logger(ERROR, Error->message);
//        clean_up_error(&Error);
//        clean_up_server(&Server);
//        clean_up_config(&ConfigServer);
//        return EXIT_FAILURE;
//    }
//    clean_up_error(&Error);
//    clean_up_server(&Server);
//    clean_up_config(&ConfigServer);
//
//    return (EXIT_SUCCESS);
//}

#include "calculator/tokenizer/tokenizer.h"
#include "calculator/calculator_core/calculator.h"
#include "../../calculator/parse/parse.h"

int main() {
    t_error*    Error = NULL;

    Error = init_error();
    if (!Error) {
        return logger(ERROR, "main: Allocation failed."), EXIT_FAILURE;
    }
    char* expression = strdup("( (3 * 2) + (5 / 1) )");
    size_t size = strlen(expression);

    if (tokenizer_code(expression, size, Error)->message) {
        logger(ERROR, Error->message);
    }
    if (parse(Error->value, Error)->message) {
        logger(ERROR, Error->message);
    }

//    pop_front(Error->value);
//    print_vector(Error->value);

    calculator(Error->value, Error);

    return 0;
}



//
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <ctype.h>
//
//// Function to check if a string is a number
//int is_number(const char* str) {
//    if (*str == '-' || *str == '+')
//        str++;
//
//    while (*str) {
//        if (!isdigit(*str))
//            return 0;
//        str++;
//    }
//    return 1;
//}
//
//// Function to define operator precedence
//int precedence(char op) {
//    if (op == '+' || op == '-')
//        return 1;
//    if (op == '*' || op == '/')
//        return 2;
//    return 0;
//}
//
//// Function to perform a basic calculation between two numbers
//double apply_operator(double a, double b, char op) {
//    switch(op) {
//    case '+': return a + b;
//    case '-': return a - b;
//    case '*': return a * b;
//    case '/':
//        if (b == 0) {
//            printf("Error: Division by zero\n");
//            exit(EXIT_FAILURE);
//        }
//        return a / b;
//    default:
//        return 0;
//    }
//}
//// Function to evaluate the expression
//double evaluate(t_vector* tokens) {
//    t_vector* values = init_vector();
//    t_vector* ops = init_vector();
//
//    for (size_t i = 0; i < tokens->size; i++) {
//        char* token = tokens->data[i];
//
//        // If token is a number, push it to values stack
//        if (is_number(token)) {
//            push_back(values, token);
//        }
//            // If token is an operator
//        else if (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/') {
//            while (ops->size > 0 && precedence(ops->data[ops->size - 1][0]) >= precedence(token[0])) {
//                char op = ops->data[ops->size - 1][0];
//                ops->size--;
//
//                double val2 = atof(values->data[values->size - 1]);
//                values->size--;
//                double val1 = atof(values->data[values->size - 1]);
//                values->size--;
//
//                double result = apply_operator(val1, val2, op);
//                char result_str[20];
//                sprintf(result_str, "%lf", result);
//                push_back(values, result_str);
//            }
//            push_back(ops, token);
//        }
//            // If token is left parenthesis, push it to ops stack
//        else if (token[0] == '(') {
//            push_back(ops, token);
//        }
//            // If token is right parenthesis, solve the sub-expression
//        else if (token[0] == ')') {
//            while (ops->size > 0 && ops->data[ops->size - 1][0] != '(') {
//                char op = ops->data[ops->size - 1][0];
//                ops->size--;
//
//                double val2 = atof(values->data[values->size - 1]);
//                values->size--;
//                double val1 = atof(values->data[values->size - 1]);
//                values->size--;
//
//                double result = apply_operator(val1, val2, op);
//                char result_str[20];
//                sprintf(result_str, "%lf", result);
//                push_back(values, result_str);
//            }
//            ops->size--; // Pop the '('
//        }
//    }
//
//    // Process all remaining operators
//    while (ops->size > 0) {
//        char op = ops->data[ops->size - 1][0];
//        ops->size--;
//
//        double val2 = atof(values->data[values->size - 1]);
//        values->size--;
//        double val1 = atof(values->data[values->size - 1]);
//        values->size--;
//
//        double result = apply_operator(val1, val2, op);
//        char result_str[20];
//        sprintf(result_str, "%lf", result);
//        push_back(values, result_str);
//    }
//
//    double final_result = atof(values->data[values->size - 1]);
//    return final_result;
//}
//
// Main function to parse the input expression and evaluate it
//int main() {
//    char* expression = "3 + (4 * 2) - 7 / 2";
//
//    t_vector* tokens = init_vector();
//    // You need to implement tokenizing the input string into tokens (numbers, operators, parentheses).
//    // Example tokens: ["3", "+", "(", "4", "*", "2", ")", "-", "7", "/", "2"]
//
//    // Sample hardcoded tokens for simplicity
//    push_back(tokens, "3");
//    push_back(tokens, "+");
//    push_back(tokens, "(");
//    push_back(tokens, "4");
//    push_back(tokens, "*");
//    push_back(tokens, "-2");
//    push_back(tokens, ")");
//    push_back(tokens, "-");
//    push_back(tokens, "7");
//    push_back(tokens, "/");
//    push_back(tokens, "2");
//
//    t_error*    Error = NULL;
//
//    Error = init_error();
//    if (!Error) {
//        return logger(ERROR, "main: Allocation failed."), EXIT_FAILURE;
//    }
//    char* expression = strdup("       *   -15255    -      5 ))) + 5 5          + 1 5 6   235 -7 12 +8");
//    size_t size = strlen(expression);
//
//    if (tokenizer_code(expression, size, Error)->message) {
//        logger(ERROR, Error->message);
//    }
//
//    double result = evaluate(Error->value);
//    printf("Result: %lf\n", result);
//
//    free_vector(&Error->value);
//    return 0;
//}
