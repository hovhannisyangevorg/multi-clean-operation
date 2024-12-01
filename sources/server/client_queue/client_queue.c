#include "client_queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

t_node_queue* init_node_queue(t_client_data data) {
    t_node_queue* node;

    node = (t_node_queue*)calloc(1, sizeof(t_node_queue));
    if (!node)
        return (NULL);
    node->client_data = data;
    return (node);
}

t_client_queue* init_client_queue() {
    t_client_queue* clients;

    clients = (t_client_queue*)calloc(1, sizeof(t_client_queue));
    if (!clients)
        return (NULL);
    return (clients);
}

bool isEmpty(t_client_queue* queue) {
    return queue->size == 0;
}

void    enqueue(t_client_queue* queue, t_client_data data) {
    t_node_queue* new_node;

    if (!queue)
        return;

    new_node = init_node_queue(data);
    if (!new_node)
        return ;

    if (!queue->size) {
        queue->rear = new_node;
        queue->front = new_node;
    }
    else {
        new_node->next = queue->front;
        queue->front = new_node;
    }
    ++queue->size;
}

void    dequeue(t_client_queue* queue) {
    t_node_queue* temporary;

    if (queue->size == 0)
        return ;
    if (queue->size == 1) {
        free(queue->front);
        queue->front = NULL;
        queue->rear = NULL;
        --queue->size;
        return;
    }

    temporary = queue->front;
    while (temporary->next != queue->rear) {
        temporary = temporary->next;
    }
    free(queue->rear);
    temporary->next = NULL;
    queue->rear = temporary;
    --queue->size;
}

//void for_each(t_client_queue* queue,  t_queue_handler handler) {
//    t_node_queue* tmp = queue->front;
//    if (!handler) return ;
//    while (tmp) {
//        handler(tmp->client_data);
//        tmp = tmp->next;
//    }
//}