#include "send_message.h"

t_header* init_header() {
    t_header* Header = (t_header*)calloc(1 , sizeof(t_header));
    if (!Header)
        return (NULL);
    return Header;
}

t_error* send_message(t_client* Client, t_error* Error) {
    (void )Error;
    send(Client->socket_fd, Client->expression, strlen(Client->expression), 0);
    return (Error);
}