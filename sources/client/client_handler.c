#include "client_handler.h"

#include "load-config.h"
#include "logger-system.h"

t_config ConfigClient;

void init() {
    logger(INFO, "Client Load Configuration started ...");
    init_config(&ConfigClient);
    load_config(&ConfigClient);
    print_config(ConfigClient);
}

void client_handler() {
    init();
}