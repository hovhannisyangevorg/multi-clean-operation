#include "client.h"

#include "../send_message/send_message.h"

static t_error* init(t_config* ConfigServer, t_error* Error) {
    logger(INFO, "Client Load Configuration started ...");

    if (load_config(ConfigServer, Error)->message)
        return Set(Error, format(__func__, ""));
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

static t_error* create_socket(t_client* Client, t_error* Error) {
    Client->client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (Client->client_fd == -1) {
        return (Set(Error, format(__func__, "(Socket creation failed.)")));
    }
    return Error;
}

static t_error* make_client_addr(t_config* ConfigClient, t_client* Client, t_error* Error) {
    Client->client_addr.sin_family          = AF_INET;
    Client->client_addr.sin_port            = htons(ConfigClient->port);
    Client->client_addr.sin_addr.s_addr     = inet_addr(ConfigClient->host);

    if (Client->client_addr.sin_addr.s_addr == INADDR_NONE) {
        return (close(Client->client_fd), Set(Error, format(__func__, "(Invalid IP address.)")));
    }
    return Error;
}

static t_error* connect_client(t_client* Client, t_error* Error) {
    if (connect(Client->client_fd, (t_socket_address*)&Client->client_addr, sizeof(Client->client_addr)) < 0) {
        return (close(Client->client_fd), Set(Error, format(__func__, "(Connection failed)")));
    }
    return Error;
}

t_error* client_handler(t_config* ConfigClient, t_client* Client, t_error* Error) {
    if (init(ConfigClient, Error)->message) {
        return (Set(Error, format(__func__, "")));
    }

    if (create_socket(Client, Error)->message)
        return (Set(Error, format(__func__, "")));

    if (make_client_addr(ConfigClient, Client, Error)->message)
        return (close(Client->client_fd), Set(Error, format(__func__, "")));

    if (connect_client(Client, Error)->message)
        return (close(Client->client_fd), Set(Error, format(__func__, "")));

    if (send_message(Client, Error)->message)
        return (close(Client->client_fd), Set(Error, format(__func__, "")));

    if (receive_response(Client, Error)->message) {
        return (close(Client->client_fd), Set(Error, format(__func__, "")));
    }
    return (close(Client->client_fd), Error);
}

void clean_up_client(t_client** Client) {
    if (Client && *Client) {
        free((char*)(*Client)->expression);
        (*Client)->expression = NULL;
        free(*Client);
        *Client = NULL;
    }
}