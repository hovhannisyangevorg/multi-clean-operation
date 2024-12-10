#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>

#include "logger-system.h"
#include "error.h"
#include "../../read_input/read_input.h"
#include "logger-system.h"
#include "./types.h"
#include "../../load-config/load-config.h"
#include "../../logger-system/logger-system.h"
#include "../receive_response/receive_response.h"

t_error* client_handler(t_config* ConfigClient, t_client* Client, t_error* Error);
t_error* init_client(t_error* Error);
void clean_up_client(t_client** Client);

#endif
