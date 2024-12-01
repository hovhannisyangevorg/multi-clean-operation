#ifndef SEND_MESSAGE_H
#define SEND_MESSAGE_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "../../error/error.h"
#include "../client_handler.h"
#include <string.h>


typedef struct s_header t_header;

struct s_header{
    uint16_t header_length;
    uint16_t message_type;
    uint32_t message_length;
};

t_header* init_header();

#endif //SEND_MESSAGE_H
