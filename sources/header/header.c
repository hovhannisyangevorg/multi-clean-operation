#include "header.h"

t_header* init_header() {
    t_header* Header = (t_header*)calloc(1 , sizeof(t_header));
    if (!Header)
        return (NULL);
    return Header;
}

void clean_up_header(t_header** Header) {
    if (Header && *Header) {
        free(*Header);
        *Header = NULL;
    }
}