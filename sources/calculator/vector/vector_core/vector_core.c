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
        return 7;
    return (Vector->capacity * 2);
}

static bool resize_vector(t_vector* Vector) {
    size_t new_capacity = calculate_capacity(Vector);

    t_data* new_data = (t_data*)calloc(new_capacity, sizeof(t_data));
    if (!new_data) {
        return false;
    }
    for (size_t i = 0; i < Vector->size; ++i) {
        new_data[i].type    = Vector->data[i].type;
        new_data[i].value   = Vector->data[i].value;
        new_data[i].token   = Vector->data[i].token;
        new_data[i].size    = Vector->data[i].size;
    }

    free(Vector->data);
    Vector->data = new_data;
    Vector->capacity = new_capacity;
    return true;
}

void push_back(t_vector* Vector, t_data data) {
    if (!Vector)
        return ;

    if (Vector->size == Vector->capacity) {
        if (!resize_vector(Vector))
            return ;
    }

    Vector->data[Vector->size].token = strdup(data.token);
    Vector->data[Vector->size].size = strlen(data.token);
    Vector->data[Vector->size].type = data.type;
    Vector->data[Vector->size].value = data.value;
    ++Vector->size;
    return ;
}

static t_data* copy_data(t_vector* Vector, size_t start, size_t end) {
    size_t i = start;
    size_t j = 0;

    t_data* new_data = (t_data*)calloc(Vector->capacity,sizeof(t_data));
    if (!new_data) {
        return NULL;
    }

    while (j < end) {
        new_data[i].token   = strdup(Vector->data[j].token);
        new_data[i].value   = Vector->data[j].value;
        new_data[i].size    = strlen(Vector->data[j].token);
        new_data[i].type    = Vector->data[j].type;
        ++i, ++j, ++start;
    }
    return new_data;
}

void  push_front(t_vector* Vector, t_data* data) {
    if (!Vector || !data)
        return;

    if (Vector->size == Vector->capacity) {
        if (!resize_vector(Vector))
            return ;
    }

    t_data* new_data = NULL;
    new_data = copy_data(Vector, 1, Vector->size);
    if (!new_data) {
        return;
    }

    free_data(Vector->data, Vector->size);
    Vector->data = new_data;
    Vector->data[0].token   = strdup(data->token);
    Vector->data[0].value   = data->value;
    Vector->data[0].type    = data->type;
    Vector->data[0].size    = strlen(data->token);
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
    if (!Vector || !*Vector)
        return ;

    for (size_t i = 0; i < (*Vector)->size; i++) {
        if ((*Vector)->data) {
            clean_up_data(&(*Vector)->data[i]);
        }
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
    printf("\n\n[\n\n");
    for (size_t i = 0; i < Vector->size; i++) {
        printf("%s,  ", Vector->data[i].token);
//        printf("\t Token: |%LF|        |%s|\n", Vector->data[i].value, type_to_string(Vector->data[i].type));
    }
    printf("\n\n]\n\n");

}