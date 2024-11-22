#include "client_handler.h"

#include "load-config.h"

t_config ConfigClient;

void init() {
    load_config(&ConfigClient);
    print_config(ConfigClient);
}

void client_handler() {
    init();
}