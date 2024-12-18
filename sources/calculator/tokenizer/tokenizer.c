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

static void symbolize(t_vector* Vector) {
    for (size_t i = 0; i < Vector->size; ++i) {
        char ch = Vector->data[i].token[0];
        Vector->data[i].type = to_type(ch);
        if (Vector->data[i].type == UNKNOWN) {
            Vector->data[i].type = NUMBER;
        }
    }
}

char* clone_substring(const char* start, const char* end) {
    size_t length = end - start;

    char* clone = (char*)malloc(length + 1);
    if (!clone) {
        return NULL;
    }
    strncpy(clone, start, length);
    clone[length] = '\0';
    return clone;
}

t_error* tokenizer_code(const char* expression, size_t size, t_error* Error) {
    const char* delimiters = "-+*/()\t ";

    if (!is_valid(expression))
        return Set(Error, format(__func__, "Invalid character in expression"));

    t_vector *Vector = init_vector();
    if (!Vector) {
        return Set(Error, format(__func__, "(Memory allocation failed.)"));
    }

    const char *start = expression;
    const char *end = expression;

    while ((size_t) (start - expression) < size) {

        while ((size_t)(start - expression) < size && strchr(delimiters, *start) != NULL) {
            if (isspace(*start)) {
                start++;
                continue;
            }
            char *token = clone_substring(start, start + 1);
            if (!token) {
                free_vector(&Vector);
                return Set(Error, format(__func__, "(Memory allocation failed.)"));
            }

            t_data data = {
                .token = token,
                .size = err_strlen(token),
                .type = UNKNOWN,
                .value = 0
            };

            push_back(Vector, data);
            free(token);
            start++;
        }

        end = start;
        while ((size_t) (end - expression) < size && strchr(delimiters, *end) == NULL) {
            end++;
        }

        if (start < end) {
            char *token = clone_substring(start, end);
            if (!token) {
                free_vector(&Vector);
                return Set(Error, format(__func__, "(Memory allocation failed.)"));
            }
            t_data data = {
                .token = token,
                .size = err_strlen(token),
                .type = UNKNOWN,
                .value = 0
            };

            push_back(Vector, data);
            free(token);
            start = end;
        }
        else {
            start++;
        }
    }

    symbolize(Vector);
    return Error->value = Vector, Error;
}
