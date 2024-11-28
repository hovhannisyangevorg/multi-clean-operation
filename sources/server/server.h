#ifndef SERVER_HPP
#define SERVER_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "logger-system.h"
#include "load-config.h"
#include "error.h"

typedef struct s_server t_server;
typedef struct sockaddr_in t_ip_socket;
typedef struct sockaddr t_socket_address;

struct s_server {
    int                 socket_fd;
    t_ip_socket         server_addr;
};

t_error* server(t_error* error);

#endif //SERVER_HPP
