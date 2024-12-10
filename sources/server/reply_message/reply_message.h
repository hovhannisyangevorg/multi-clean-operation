#ifndef SERVER_RESPONSE_H
#define SERVER_RESPONSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>

#include "../../error/error.h"
#include "../../logger-system/logger-system.h"
#include "../../load-config/load-config.h"
#include "../../header/header.h"
#include "../server_core/types.h"
#include "calculator/calculator.h"
#include "../../signals/signals.h"
#include "../../calculator/calculator.h"
#include "../send_response/send_response.h"

t_error* reply_message(t_server* Server, t_error* Error);

#endif //SERVER_RESPONSE_H
