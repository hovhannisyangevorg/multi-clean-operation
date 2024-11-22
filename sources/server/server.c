#include "server.h"

t_config ConfigServer;

static void init() {
    load_config(&ConfigServer);
    print_config(ConfigServer);
}

void server() {
    init();
}
