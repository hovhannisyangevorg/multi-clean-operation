#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>

#include "./types.h"
#include "../../error/error.h"
#include "../../logger-system/logger-system.h"
#include "../../load-config/load-config.h"
#include "../../header/header.h"
#include "../reply_message/reply_message.h"

t_error*    server(t_config* ConfigServer, t_server* Server, t_error* Error);
t_error*    init_server(t_error* Error);
void clean_up_server(t_server** Server);

#endif //SERVER_H
