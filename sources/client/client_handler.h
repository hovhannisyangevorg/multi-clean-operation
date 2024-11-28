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

typedef struct s_client     t_client;
typedef struct sockaddr_in  t_ip_socket;
typedef struct sockaddr     t_socket_address;

struct s_client {
    int                 socket_fd;
    t_ip_socket         server_addr;
};

t_error* client_handler(t_error* Error);

#endif
