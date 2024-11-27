#include "server.h"

typedef struct s_server t_server;

t_config    ConfigServer;

static void init() {
    logger(INFO, "Server configuration loading started...");
    init_config(&ConfigServer);
    load_config(&ConfigServer);
    print_config(ConfigServer);
}

t_error* server(t_error* Error) {
    logger(INFO, "Server started ...");
    init();

    int socket_fd;
    struct sockaddr_in server_addr;

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        return (Set(Error, format(__func__, "(Socket creation failed.)")));
    }

    server_addr.sin_family          = AF_INET;
    server_addr.sin_port            = htons(ConfigServer.port);
    server_addr.sin_addr.s_addr     = inet_addr(ConfigServer.host);

    if (server_addr.sin_addr.s_addr == INADDR_NONE) {
        close(socket_fd);
        return (Set(Error, format(__func__, "(Invalid IP address.)")));
    }

    if (bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        close(socket_fd);
        return (Set(Error, format(__func__, "(Bind failed)")));
    }

    if (listen(socket_fd, 3) < 0) {
        close(socket_fd);
        return (Set(Error, format(__func__, "(Listen failed)")));
    }

    printf("Server listening on port %d...\n", ConfigServer.port);
    return Error;
}


//struct sockaddr_in {
//    short            sin_family;   // Address family (e.g., AF_INET for IPv4)
//    unsigned short   sin_port;     // Port number (in network byte order)
//    struct in_addr   sin_addr;     // IP address (in network byte order)
//    char             sin_zero[8]; // Padding to match `struct sockaddr` size
//};