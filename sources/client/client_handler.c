#include "client_handler.h"

t_config ConfigClient;

static void init() {
    logger(INFO, "Client Load Configuration started ...");
    init_config(&ConfigClient);
    load_config(&ConfigClient);
}

static t_error* create_socket(t_client* Client, t_error* Error) {
    Client->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (Client->socket_fd == -1) {
        return (Set(Error, format(__func__, "(Socket creation failed.)")));
    }
    return Error;
}

static t_error* make_client_addr(t_client* Client, t_error* Error) {
    Client->server_addr.sin_family          = AF_INET;
    Client->server_addr.sin_port            = htons(ConfigClient.port);
    Client->server_addr.sin_addr.s_addr     = inet_addr(ConfigClient.host);

    if (Client->server_addr.sin_addr.s_addr == INADDR_NONE) {
        return (close(Client->socket_fd), Set(Error, format(__func__, "(Invalid IP address.)")));
    }
    return Error;
}

static t_error* connect_client(t_client* Client, t_error* Error) {
    if (connect(Client->socket_fd, (t_socket_address*)&Client->server_addr, sizeof(Client->server_addr)) < 0) {
        return (close(Client->socket_fd), Set(Error, format(__func__, "Connection failed")));
    }
    return Error;
}

static t_error* send_expression(t_client* Client, t_error* Error) {
    (void )Error;
    int mtu;
    socklen_t len = sizeof(mtu);
    if (getsockopt(Client->socket_fd, IPPROTO_IP, IP_MTU, &mtu, &len))
        logger(TRACE, "FFFFFFFFFFFFFAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
//    logger(TRACE, "");
//    printf("MTU of the network interface is: %d\n", mtu);

//    send(Client->socket_fd, Client->expression, strlen(Client->expression), 0);
    return (Error);
}

t_error* init_client(t_error* Error) {
    t_client * client_tmp = NULL;

    client_tmp = (t_client *)calloc(1, sizeof(t_client));
    if (client_tmp == NULL) {
        return (Set(Error, format(__func__, "(Memory allocation failed.)")));
    }
    return (Error->value = client_tmp, Error);
}

t_error* client_handler(t_client* Client, t_error* Error) {
    init();

    if (create_socket(Client, Error)->message)
        return (Set(Error, format(__func__, "")));

    if (make_client_addr(Client, Error)->message)
        return (Set(Error, format(__func__, "")));

    if (connect_client(Client, Error)->message)
        return (Set(Error, format(__func__, "")));

    if (send_expression(Client, Error)->message)
        return (Set(Error, format(__func__, "")));

    return close(Client->socket_fd), Error;
}