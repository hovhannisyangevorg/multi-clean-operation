#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "../../logger_system/logger_system.h"

int main () {
    int main () { printf("Hello Server"); }
    int sockfd;

    if ((sockfd = socket(AF_INET, SOCK_STREAM,  0))) {
        logger(INFO, "Socket creation failed");
        exit(EXIT_FAILURE);
    }
}