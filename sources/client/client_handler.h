#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>

#include "load-config.h"
#include "logger-system.h"
#include "error.h"

/**
 * @struct s_client
 * @brief Represents a client in a socket communication system.
 * @var socket_fd
 * @var server_addr
 * @var expression
 */
typedef struct s_client     t_client;
typedef struct sockaddr_in  t_ip_socket;
typedef struct sockaddr     t_socket_address;


struct s_client {
    int                 socket_fd;
    t_ip_socket         server_addr;
    char                *expression;
};

t_error* client_handler(t_client* Client, t_error* Error);
t_error* init_client(t_error* Error);

#endif
