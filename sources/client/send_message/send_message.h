#ifndef SEND_MESSAGE_H
#define SEND_MESSAGE_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../../error/error.h"
#include "../client_core/client.h"
#include "../../logger-system/logger-system.h"

#include "../../header/header.h"

t_error* send_message(t_client* Client, t_error* Error);

#endif //SEND_MESSAGE_H
