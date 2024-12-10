#ifndef HEADER_H
#define HEADER_H

#include <stdint.h>
#include <stdlib.h>

typedef struct s_header t_header;

struct s_header{
    uint32_t message_length;
};

t_header* init_header();
void clean_up_header(t_header** Header);

#endif //HEADER_H
