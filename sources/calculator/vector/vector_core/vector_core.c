#include "./vector_core.h"

t_vector* init_vector() {
    t_vector* Vector = (t_vector*)calloc(1, sizeof(t_vector));
    if (!Vector)
        return NULL;
    Vector->data = init_data();
    if (!Vector->data)
        return NULL;
    Vector->size        = 0;
    Vector->capacity    = 0;
    return Vector;
};

static size_t calculate_capacity(t_vector* Vector) {
    if (Vector->capacity == 0)
        return 2;
    return (Vector->capacity * 2);
}

static long resize_vector(t_vector* Vector) {
    size_t new_capacity = calculate_capacity(Vector);
    t_data* new_data = (t_data*)realloc(Vector->data, new_capacity * sizeof(t_data));
    if (!new_data) {
        return -1;
    }
    Vector->data = new_data;
    Vector->capacity = new_capacity;
    return 0;
}

void push_back(t_vector* Vector, t_data data) {
    if (!Vector)
        return ;

    if (Vector->size == Vector->capacity) {
        if (resize_vector(Vector) == -1)
            return ;
    }

    Vector->data[Vector->size].token = strdup(data.token);
    Vector->data[Vector->size].size = data.size;
    Vector->data[Vector->size].type = data.type;
    Vector->data[Vector->size].value = data.value;
    ++Vector->size;
    return ;
}

void push_front(t_vector* Vector, t_data data) {
    if (!Vector)
        return;

    if (Vector->size == Vector->capacity) {
        if (resize_vector(Vector) == -1)
            return ;
    }

    memmove(&Vector->data[1], &Vector->data[0], Vector->size * sizeof(t_data));
    Vector->data[0].token = strdup(data.token);
    Vector->data[0].size = data.size;
    Vector->data[0].type = data.type;
    Vector->data[Vector->size].value = data.value;
    Vector->size++;
}

void pop_back(t_vector* Vector) {
    if (!Vector || Vector->size == 0)
        return ;

    free(Vector->data[Vector->size - 1].token);
    Vector->data[Vector->size - 1].type = UNKNOWN;
    Vector->data->size = 0;
    Vector->size--;
}

void pop_front(t_vector* Vector) {
    if (!Vector || Vector->size == 0)
        return ;

    free(Vector->data[0].token);
    Vector->data[0].size = 0;
    Vector->data[0].type = UNKNOWN;
    memmove(&Vector->data[0], &Vector->data[1], (Vector->size - 1) * sizeof(t_data));
    Vector->size--;
}

void free_vector(t_vector** Vector) {
    if (!Vector)
        return ;

    for (size_t i = 0; i < (*Vector)->size; i++) {
        free((*Vector)->data[i].token);
        (*Vector)->data[i].size = 0;
        (*Vector)->data[i].type = UNKNOWN;
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
//        printf("%s,  ", Vector->data[i].token);
        printf("\t Token: |%LF|        |%s|\n", Vector->data[i].value, type_to_string(Vector->data[i].type));
    }
    printf(" ]\n");

}