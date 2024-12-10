#ifndef SEND_RESPONSE_H
#define SEND_RESPONSE_H

#include "../../error/error.h"
#include "../../header/header.h"
#include "../server_core/types.h"
#include "../../logger-system/logger-system.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>

t_error* send_response(t_server* Server, t_error* Error);

#endif //SEND_RESPONSE_H
