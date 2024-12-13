#include "tokenizer.h"

#include "../vector/vector_core/vector_core.h"

static bool is_valid(const char* expression) {
    const char* valid = "0123456789-+*/()\t ";

    for (size_t i = 0; expression[i] != '\0'; i++) {
        if (strchr(valid, expression[i]) == NULL) {
            return false;
        }
    }
    return true;
}

char* duplicate_char(char ch) {
    char* result = (char*)calloc(2, sizeof(char));
    if (!result) {
        return NULL;
    }
    result[0] = ch;
    result[1] = '\0';
    return result;
}

t_error* extract_number(const char* expression, size_t* index, t_error* Error) {
    size_t i            = *index;
    size_t token_len    = 0;

    if (expression[i] == '+' || expression[i] == '-') {
        ++token_len;
        i++;
    }

    char* token = NULL;

    size_t token_index = i;
    while (isdigit(expression[token_index])) {
        token_len++;
        token_index++;
    }

    if (token_len > 0) {
        token = (char*)calloc(token_len + 1, sizeof(char));
        if (!token) {
            return Set(Error, format(__func__, "Invalid character in expression"));
        }
        strncpy(token, expression + i - (expression[i - 1] == '+' || expression[i - 1] == '-' ? 1 : 0), token_len);
        token[token_len] = '\0';
    }
    *index += token_len;
    return Error->value = token, Error;
}



t_error* tokenizer_code(const char* expression, size_t size, t_error* Error) {
    if (!is_valid(expression))
        return Set(Error, format(__func__, "Invalid character in expression"));

    t_vector* Vector = init_vector();
    if (!Vector) {
        return Set(Error, format(__func__, "(Memory allocation failed.)"));
    }

    size_t i = 0;
    while (expression && expression[i] && i < size) {
        if (isspace(expression[i])) {
            i++;
            continue;
        }
        if (extract_number(expression, &i, Error)->message) {
            return Set(Error, format(__func__, ""));
        }
        else if (Error->value) {
            t_data data;
            data.token = (char *)Error->value;
            data.size = err_strlen((char *)Error->value);
            data.type = NUMBER;
            push_back(Vector, data, Error);
            if (Error->message) {
                return Set(Error, format(__func__, ""));
            }
            free((char*)Error->value);
            Error->value = NULL;
        }
        else {
            t_data data;

            data.token = duplicate_char(expression[i]);
            data.size = err_strlen(data.token);
            data.type = to_type(expression[i]);

            push_back(Vector, data, Error);
            if (Error->message) {
                return Set(Error, format(__func__, ""));
            }
            i++;
        }
    }
    return Error->value = Vector, Error;
}
