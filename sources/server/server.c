#include <stdlib.h>
#include <arpa/inet.h>
#include "logger-system.h"
#include <arpa/inet.h>

#include "server.h"
#include "logger-system.h"

t_config ConfigServer;

static void init() {
    logger(INFO, "Server configuration loading started...");
    init_config(&ConfigServer);
    load_config(&ConfigServer);
    print_config(ConfigServer);
}

void server() {
    logger(INFO, "Server started ...");
    init();

//    int socket_fd;
//    struct sockaddr_in server_addr;
//
//    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
//    if (socket_fd == -1) {
//        logger(ERROR, "Socket creation failed");
//        exit(EXIT_FAILURE);
//    }
//
//    server_addr.sin_family = AF_INET;
//    server_addr.sin_port = htons(ConfigServer.port);
//    server_addr.sin_addr.s_addr = inet_addr(ConfigServer.host);
//
//    if (server_addr.sin_addr.s_addr == INADDR_NONE) {
//        logger(ERROR, "Invalid IP address");
//        exit(EXIT_FAILURE);
//    }

//    printf("Server logs path: %s\n", SERVER_LOGS);
//    printf("Client logs path: %s\n", CLIENT_LOGS);
}
