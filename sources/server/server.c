#include "server.h"

t_config    ConfigServer;

static void init() {
    logger(INFO, "Server configuration loading started...");
    init_config(&ConfigServer);
    load_config(&ConfigServer);
}

static t_error* init_server(t_error* Error) {
    t_server* server_tmp = NULL;

    server_tmp = (t_server*)calloc(1, sizeof(t_server));
    if (server_tmp == NULL) {
        return (Set(Error, format(__func__, "(Memory allocation failed.)")));
    }
    return (Error->value = server_tmp, Error);
}

static t_error* create_socket(t_server* Server, t_error* Error) {
    Server->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (Server->socket_fd == -1) {
        return (Set(Error, format(__func__, "(Socket creation failed.)")));
    }
    return Error;
}

static t_error* make_server_addr(t_server* Server, t_error* Error) {
    Server->server_addr.sin_family          = AF_INET;
    Server->server_addr.sin_port            = htons(ConfigServer.port);
    Server->server_addr.sin_addr.s_addr     = inet_addr(ConfigServer.host);

    if (Server->server_addr.sin_addr.s_addr == INADDR_NONE) {
        return (close(Server->socket_fd), Set(Error, format(__func__, "(Invalid IP address.)")));
    }
    return Error;
}

static t_error* bind_server_addr(t_server* Server, t_error* Error) {
    if (bind(Server->socket_fd, (t_socket_address*)&Server->server_addr, sizeof(Server->server_addr)) < 0) {
        return (close(Server->socket_fd), Set(Error, format(__func__, "(Bind failed)")));
    }
    return Error;
}

static t_error* listen_server(t_server* Server, t_error* Error){
    if (listen(Server->socket_fd, 3) < 0) {
        return (close(Server->socket_fd), Set(Error, format(__func__, "(Listen failed)")));
    }
    printf("Server listening on port %d...\n", ConfigServer.port);
    return Error;
}

static t_error* accept_client(t_server* Server, t_error* Error) {
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int new_socket_fd;

    new_socket_fd = accept(Server->socket_fd, (struct sockaddr*)&client_addr, &client_len);
    if (new_socket_fd < 0) {
        return (close(Server->socket_fd), Set(Error, format(__func__, "(Failed to accept client)")));
    }
    return Error;
}

t_error* server(t_error* Error) {
    logger(INFO, "Server started ...");
    init();

    t_server* Server;

    if (init_server(Error)->message)
        Set(Error, format(__func__, ""));
    Server = Error->value;

    if (create_socket(Server, Error)->message)
        return (Set(Error, format(__func__, "")));

    if (make_server_addr(Server, Error)->message)
        return (Set(Error, format(__func__, "")));

    if (bind_server_addr(Server, Error)->message)
        return (Set(Error, format(__func__, "")));

    if (listen_server(Server, Error)->message) {
        return (Set(Error, format(__func__, "")));
    }

    while (1) {
        logger(INFO, "Waiting for incoming connections...");
        if (accept_client(Server, Error)->message) {
            return close(Server->socket_fd), Set(Error, format(__func__, "Failed to accept client"));
        }
    }
    return close(Server->socket_fd), Error;
}









































































































































//t_error* server(t_error* Error) {
//    logger(INFO, "Server started ...");
//    init();
//
//    int socket_fd;
//    t_ip_socket server_addr;
////    t_ip_socket client_addr;
//    t_socket_address* sa_ptr = (t_socket_address*)&server_addr;
//
//
//    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
//    if (socket_fd == -1) {
//        return (Set(Error, format(__func__, "(Socket creation failed.)")));
//    }
//    memset(&server_addr, 0, sizeof(server_addr));
//
//    server_addr.sin_family          = AF_INET;
//    server_addr.sin_port            = htons(ConfigServer.port);
//    server_addr.sin_addr.s_addr     = inet_addr(ConfigServer.host);
//
//    if (server_addr.sin_addr.s_addr == INADDR_NONE) {
//        return (close(socket_fd), Set(Error, format(__func__, "(Invalid IP address.)")));
//    }
//
//    if (bind(socket_fd, sa_ptr, sizeof(server_addr)) < 0) {
//        return (close(socket_fd), Set(Error, format(__func__, "(Bind failed)")));
//    }
//
//    if (listen(socket_fd, 3) < 0) {
//        return (close(socket_fd), Set(Error, format(__func__, "(Listen failed)")));
//    }
//    printf("Server listening on port %d...\n", ConfigServer.port);
//    return Error;
//}


// Function to create and return a socket descriptor dynamically
//t_error* create_socket(t_error* Error) {
//    int *socket_fd = calloc(1, sizeof(int));
//
//    *socket_fd = socket(AF_INET, SOCK_STREAM, 0);
//    if (*socket_fd == -1) {
//        return (Set(Error, format(__func__, "(Socket creation failed.)")));
//    }
//    return Error->value = socket_fd, Error;
//}
