#ifndef TYPES_H
#define TYPES_H

#include <netinet/in.h>

typedef struct s_client     t_client;
typedef struct sockaddr_in  t_ip_socket;
typedef struct sockaddr     t_socket_address;

struct s_client {
    int                 client_fd;
    t_ip_socket         client_addr;
    socklen_t           client_len;
    char*               expression;
};

#endif //TYPES_H
