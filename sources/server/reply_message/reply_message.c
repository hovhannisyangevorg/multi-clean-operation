#include "reply_message.h"

static const size_t BUFFER_SIZE = 1024;

static t_error* init_buffer(size_t size, t_error* Error) {
    char* string = (char *)malloc((size + 1) * sizeof (char));
    if (!string) {
        return (Set(Error, format(__func__, "(Memory allocation failed.)")));
    }
    string[size] = '\0';
    return Error->value = string, Error;
}

static t_error* receive_header(t_server* Server, t_error* Error) {
    t_header*   Header = init_header();
    if (!Header) {
        return Set(Error, format(__func__, "(Memory allocation failed.)"));
    }

    int bytes_header = recv(Server->client_info.client_fd, Header, sizeof(*Header), 0);
    if (bytes_header < 0) {
        return Set(Error, format(__func__, "(Receive failed.)"));
    } else if (bytes_header < (int)sizeof(*Header)) {
        return Set(Error, format(__func__, "(Incomplete struct received.)"));
    }
    return Error->value = Header, Error;
}

static t_error* receive_body(t_server* Server, t_header* Header, char* Buffer, t_error* Error) {
    size_t stream = 0;

    while (stream < Header->message_length) {
        int bytes_to_read = BUFFER_SIZE;

        // Adjust bytes_to_read if remaining bytes are less than BUFFER_SIZE.
        if (Header->message_length - stream < BUFFER_SIZE) {
            bytes_to_read = Header->message_length - stream;
        }

        int bytes_received = recv(Server->client_info.client_fd, Buffer + stream, bytes_to_read, 0);

        if (bytes_received < 0) {
            return Set(Error, format(__func__, "(Receive failed.)"));
        } else if (bytes_received == 0) {
            logger(WARN, "Connection was closed.");
            break;
        }
        stream += bytes_received;
    }

    // Check if the entire message was received.
    if (stream != Header->message_length) {
        return Set(Error, format(__func__, "(Incomplete message received."));
    }

    return Error->value = Buffer, Error;
}

void clean_up_body(t_header** Header, char** Buffer) {
    if (*Header) {
        clean_up_header(Header);
    }
    if ((*Buffer)) {
        free(*Buffer);
        *Buffer = NULL;
    }
}

t_error* send_calculation(t_server* Server, t_header* Header, char* Buffer, t_error* Error) {
    t_error* ParsError = NULL;

    ParsError = init_error();
    if (!ParsError) {
        return Set(Error, format(__func__, "(Parse Error initialize failed.)"));;
    }

    ParsError = calculator(Buffer, Header, ParsError);
    if (ParsError->message) {
        Server->response = ParsError->message;
        if (send_response(Server, Error)->message) {
            clean_up_error(&ParsError);
            Server->response = NULL;
            return Set(Error, format(__func__, ""));
        }
    } else {
        Server->response = (char *)(*ParsError).value;
        if (send_response(Server, Error)->message) {
            free(Server->response);
            Server->response = NULL;
            return Set(Error, format(__func__, ""));
        }
        free(Server->response);
        Server->response = NULL;
    }
    clean_up_error(&ParsError);
    return Error;
}

t_error* reply_message(t_server* Server, t_error* Error) {
    logger(INFO, "Waiting for a connection...");
    char*       Buffer = NULL;
    t_header*   Header = NULL;
    t_sigaction Signal = init_signal();

    if (sigaction(SIGINT, &Signal, NULL) == -1) {
        return Set(Error, format(__func__, "Signal failed."));
    }

    while (true) {
        if ((Server->client_info.client_fd = accept(Server->socket_fd, (t_socket_address*)&Server->client_info.client_addr, &Server->client_info.client_len)) < 0) {
            if (stop_flag) {
                clean_up_body(&Header, &Buffer);
                break ;
            }
            return Set(Error, format(__func__, "(Accept failed.)"));
        }

        if (receive_header(Server, Error)->message) {
            if (Header) {
                clean_up_header(&Header);
            }
            return close(Server->client_info.client_fd), Set(Error, format(__func__, ""));
        }
        Header = Error->value;

        if (init_buffer(Header->message_length, Error)->message) {
            if (Header) {
                clean_up_header(&Header);
            }
            return close(Server->client_info.client_fd), Set(Error, format(__func__, ""));
        }
        Buffer = Error->value;

        if (receive_body(Server, Header, Buffer, Error)->message) {
            clean_up_body(&Header, &Buffer);
            return close(Server->client_info.client_fd), Set(Error, format(__func__, ""));
        }

        if (send_calculation(Server, Header, Buffer, Error)->message) {
            clean_up_body(&Header, &Buffer);
            return close(Server->client_info.client_fd), Set(Error, format(__func__, ""));
        }
        clean_up_body(&Header, &Buffer);
    }

    if (stop_flag) {
        clean_up_body(&Header, &Buffer);
        return Error;
    }

    return close(Server->client_info.client_fd), Error;
}
