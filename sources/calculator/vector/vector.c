#include "vector.h"

t_vector* init_vector() {
    t_vector* Vector = (t_vector*)calloc(1, sizeof(t_vector));
    if (!Vector)
        return NULL;
    Vector->size = 0;
    Vector->capacity = 0;
    return Vector;
};

size_t calculate_capacity(t_vector* Vector) {
    if (Vector->capacity == 0)
        return 2;
    return (Vector->capacity * 2);
}

long resize_vector(t_vector* Vector) {
    size_t new_capacity = calculate_capacity(Vector);
    char** new_data = (char**)realloc(Vector->data, new_capacity * sizeof(char*));
    if (!new_data) {
        return -1;
    }

    Vector->data = new_data;
    Vector->capacity = new_capacity;
    return 0;
}

void push_back(t_vector* Vector, char* token)  {
    if (!Vector || !token)
        return ;

    if (Vector->size == Vector->capacity) {
        if (resize_vector(Vector) == -1)
            return ;
    }
    Vector->data[Vector->size] = strdup(token);
    Vector->data[Vector->size + 1] = NULL;
    ++Vector->size;
}

void push_front(t_vector* Vector, const char* token) {
    if (!Vector || !token)
        return;

    if (Vector->size == Vector->capacity) {
        if (resize_vector(Vector) == -1)
            return;
    }

    memmove(&Vector->data[1], &Vector->data[0], Vector->size * sizeof(char *));
    Vector->data[0] = strdup(token); // Duplicate the string at the front
    Vector->data[Vector->size + 1] = NULL;
    Vector->size++;
}

void pop_back(t_vector* Vector) {
    if (!Vector || Vector->size == 0)
        return ;

    free(Vector->data[Vector->size - 1]);
    Vector->data[Vector->size - 1] = NULL;
    Vector->size--;
}

void pop_front(t_vector* Vector) {
    if (!Vector || Vector->size == 0)
        return ;

    free(Vector->data[0]);
    memmove(&Vector->data[0], &Vector->data[1], (Vector->size - 1) * sizeof(char*));
    Vector->data[Vector->size - 1] = NULL;
    Vector->size--;
}

void free_vector(t_vector** Vector) {
    if (!Vector)
        return ;

    for (size_t i = 0; i < (*Vector)->size; i++) {
        free((*Vector)->data[i]);
    }

    free((*Vector)->data);
    free(*Vector);
    *Vector = NULL;
}

void print_vector(t_vector* Vector) {
    if (!Vector || Vector->size == 0) {
        return ;
    }

    logger(TRACE, "Vector contents: ");
    printf("[ ");
    for (size_t i = 0; i < Vector->size; i++) {
        printf("%s,  ", Vector->data[i]);
    }
    printf(" ]\n");
}