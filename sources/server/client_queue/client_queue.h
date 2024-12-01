#ifndef CLIENT_QUEUE_H
#define CLIENT_QUEUE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct s_client_queue   t_client_queue;
typedef struct s_node_queue     t_node_queue;
typedef struct s_client_data    t_client_data;
//typedef void (*t_queue_handler)(t_client_data data);

struct s_client_data {
    int client_sfd;
};

struct s_node_queue {
    t_client_data client_data;
    t_node_queue* next;
};

struct s_client_queue {
    t_node_queue* front;
    t_node_queue* rear;
    size_t size;
};

//void    for_each(t_client_queue* queue, t_queue_handler handler);
void    dequeue(t_client_queue* queue);
void    enqueue(t_client_queue* queue, t_client_data data);
bool    isEmpty(t_client_queue* queue);
t_client_queue* init_client_queue();
t_node_queue* init_node_queue(t_client_data data);

#endif //CLIENT_QUEUE_H
