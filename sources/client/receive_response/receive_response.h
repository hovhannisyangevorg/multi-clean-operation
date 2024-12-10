#ifndef REPLY_RESPONSE_H
#define REPLY_RESPONSE_H

#include "../../error/error.h"
#include "../../client/client_core/types.h"
#include "../../load-config/load-config.h"
#include "../../logger-system/logger-system.h"
#include "../../header/header.h"

t_error* receive_response(t_client* Client, t_error* Error);

#endif //REPLY_RESPONSE_H