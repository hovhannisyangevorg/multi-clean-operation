#include "receive_response.h"

static const size_t BUFFER_SIZE = 1024;

static t_error* init_buffer(size_t size, t_error* Error) {
    char* string = (char *)malloc((size + 1) * sizeof (char));
    if (!string) {
        return (Set(Error, format(__func__, "(Memory allocation failed.)")));
    }
    string[size] = '\0';
    return Error->value = string, Error;
}

static t_error* receive_header(t_client* Client, t_error* Error) {
    t_header*   Header = init_header();
    if (!Header) {
        return Set(Error, format(__func__, "(Memory allocation failed.)"));
    }

    int bytes_header = recv(Client->client_fd, Header, sizeof(*Header), 0);
    if (bytes_header < 0) {
        return Set(Error, format(__func__, "(Receive failed.)"));
    } else if (bytes_header < (int)sizeof(*Header)) {
        return Set(Error, format(__func__, "(Incomplete struct received.)"));
    }
    return Error->value = Header, Error;
}

static t_error* receive_body(t_client* Client, t_header* Header, char* Buffer, t_error* Error) {
    size_t stream = 0;

    while (stream < Header->message_length) {
        int bytes_to_read = BUFFER_SIZE;

        if (Header->message_length - stream < BUFFER_SIZE) {
            bytes_to_read = Header->message_length - stream;
        }

        int bytes_received = recv(Client->client_fd, Buffer + stream, bytes_to_read, 0);

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

t_error* receive_response(t_client* Client, t_error* Error) {
    char*       Buffer = NULL;
    t_header*   Header = NULL;

    if (receive_header(Client, Error)->message) {
        if (Header) {
            clean_up_header(&Header);
        }
        return Set(Error, format(__func__, ""));
    }
    Header = Error->value;

    if (init_buffer(Header->message_length, Error)->message) {
        clean_up_header(&Header);
        return Set(Error, format(__func__, ""));
    }
    Buffer = Error->value;

    if (receive_body(Client, Header, Buffer, Error)->message) {
        clean_up_body(&Header, &Buffer);
        free(Buffer);
        return Set(Error, format(__func__, ""));
    }
    logger(INFO, Buffer);
    clean_up_body(&Header, &Buffer);
    free(Buffer);
    return Error;
}

