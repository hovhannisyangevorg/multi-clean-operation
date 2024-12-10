#include "server.h"

static t_error* init(t_config* ConfigServer, t_error* Error) {
    logger(INFO, "Server configuration loading started...");

    if (load_config(ConfigServer, Error)->message) {
        return Set(Error, format(__func__, ""));
    }
    ConfigServer = Error->value;
    return (Error);
}

t_error* init_server(t_error* Error) {
    t_server* server_tmp = NULL;

    server_tmp = (t_server*)calloc(1, sizeof(t_server));
    if (server_tmp == NULL) {
        return (Set(Error, format(__func__, "(Memory allocation failed.)")));
    }
    server_tmp->client_info.client_len = sizeof(server_tmp->client_info.client_addr);
    return (Error->value = server_tmp, Error);
}

static t_error* create_socket(t_server* Server, t_error* Error) {
    Server->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (Server->socket_fd == -1) {
        return (Set(Error, format(__func__, "(Socket creation failed.)")));
    }
    return Error;
}

static t_error* make_server_addr(t_config* ConfigServer, t_server* Server, t_error* Error) {
    Server->server_addr.sin_family          = AF_INET;
    Server->server_addr.sin_port            = htons(ConfigServer->port);
    Server->server_addr.sin_addr.s_addr     = inet_addr(ConfigServer->host);

    if (Server->server_addr.sin_addr.s_addr == INADDR_NONE) {
        return (Set(Error, format(__func__, "(Invalid IP address.)")));
    }
    return Error;
}

static t_error* bind_server_addr(t_server* Server, t_error* Error) {
    if (bind(Server->socket_fd, (t_socket_address*)&Server->server_addr, sizeof(Server->server_addr)) < 0) {
        return (Set(Error, format(__func__, "(Bind failed)")));
    }
    return Error;
}

static t_error* listen_server(t_config* ConfigServer, t_server* Server, t_error* Error){
    if (listen(Server->socket_fd, ConfigServer->backlog) < 0) {
        return (Set(Error, format(__func__, "(Listen failed)")));
    }
    char buff[256];
    sprintf(buff,"Server listening on port %d...", ConfigServer->port);
    logger(INFO, buff);
    return Error;
}

t_error* server(t_config* ConfigServer, t_server* Server, t_error* Error) {
    logger(INFO, "Server started ...");

    if (init(ConfigServer, Error)->message) {
        return Set(Error, format(__func__, ""));
    }

    if (create_socket(Server, Error)->message) {
        return (Set(Error, format(__func__, "")));
    }

    if (make_server_addr(ConfigServer, Server, Error)->message) {
        return (close(Server->socket_fd), Set(Error, format(__func__, "")));
    }

    if (bind_server_addr(Server, Error)->message) {
        return (close(Server->socket_fd), Set(Error, format(__func__, "")));
    }

    if (listen_server(ConfigServer, Server, Error)->message) {
        return (close(Server->socket_fd), Set(Error, format(__func__, "")));
    }

    if (reply_message(Server, Error)->message) {
        return (close(Server->socket_fd), Set(Error, format(__func__, "")));
    }

    return close(Server->socket_fd), Error;
}

void clean_up_server(t_server** Server) {
    if (Server && *Server) {
        free(*Server);
        Server = NULL;
    }
}