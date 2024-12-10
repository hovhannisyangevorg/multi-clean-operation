#ifndef TYPES_H
#define TYPES_H

#include <netinet/in.h>

typedef struct s_server     t_server;
typedef struct sockaddr     t_socket_address;
typedef struct sockaddr_in  t_ip_socket;
typedef struct s_client_info t_client_info;

struct s_client_info {
    int                 client_fd;
    t_ip_socket         client_addr;
    socklen_t           client_len;
};

struct s_server {
    int                 socket_fd;
    t_ip_socket         server_addr;
    t_client_info       client_info;
    char*               response;
};

#endif //TYPES_H
