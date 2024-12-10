#include "send_message.h"

const size_t BUFFER_SIZE = 1024;

static t_error* make_header(t_client* Client, t_error* Error) {
    t_header* Header = init_header();
    if (!Header)
        return Set(Error, format(__func__, "(Failed to initialize header.)"));

    Header->message_length = err_strlen(Client->expression);
    if (!Header->message_length) {
        clean_up_header(&Header);
        return Set(Error, format(__func__, "(Failed to calculate body length; 'expression' is empty or invalid.)"));
    }
    return Error->value = Header, Error;
}

static t_error* send_header(t_client* Client, t_header* Header, t_error* Error) {
    ssize_t bytes_sent_header = send(Client->client_fd, Header, sizeof(*Header), 0);
    if (bytes_sent_header == -1) {
        return Set(Error, format(__func__, "(send failed.)"));
    }
    return Error;
}

static t_error* send_body(t_client* Client, t_header* Header, t_error* Error) {
    size_t stream = 0;

    while (stream < Header->message_length) {
        int bytes_to_send = BUFFER_SIZE;

        if (Header->message_length - stream < BUFFER_SIZE) {
            bytes_to_send = Header->message_length - stream;
        }
        int bytes_sent = send(Client->client_fd, Client->expression + stream, bytes_to_send, 0);

        if (bytes_sent < 0) {
            return Set(Error, format(__func__, "(Send failed.)"));
        } else if (bytes_sent == 0) {
            logger(WARN, "Connection was closed."); break;
        }
        stream += bytes_sent;
    }

    if (stream != Header->message_length) {
        return Set(Error, format(__func__, "(Incomplete message sent.)"));
    }

    return Error;
}

t_error* send_message(t_client* Client, t_error* Error) {
    t_header* Header;

    if (make_header(Client, Error)->message) {
        return Set(Error, format(__func__, ""));
    }
    Header = Error->value;

    if (send_header(Client, Header, Error)->message) {
        clean_up_header(&Header);
        return Set(Error, format(__func__, ""));
    }

    if (send_body(Client, Header, Error)->message) {
        clean_up_header(&Header);
        return Set(Error, format(__func__, ""));
    }

    return clean_up_header(&Header), Error;
}
