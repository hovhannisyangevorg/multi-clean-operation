//#include <stdio.h>
//#include <arpa/inet.h>
//#include <stdlib.h>
//#include "logger-system.h"
//#include <arpa/inet.h>
#include "server.h"


int main () {
    server();
//    logger(TRACE, "Server started ...");
//
//    int socket_fd;
//    struct sockaddr_in server_addr;
//
//    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
//    if (socket_fd == -1) {
//        logger(ERROR, "Socket creation failed");
//        exit(EXIT_FAILURE);
//    }
//
//
//    server_addr.sin_family = AF_INET;
//    server_addr.sin_addr.s_addr = inet_addr();
}



//// Function to convert IP address from text (dotted-decimal) to binary (unsigned int)
//unsigned int text_to_binary(const char *ip_address) {
//    struct in_addr addr;
//    if (inet_pton(AF_INET, ip_address, &addr) <= 0) {
//        perror("inet_pton failed");
//        exit(EXIT_FAILURE);
//    }
//    return ntohl(addr.s_addr);  // Convert from network byte order to host byte order
//}
//
//// Function to convert IP address from binary (unsigned int) to text (dotted-decimal)
//void binary_to_text(unsigned int ip_address, char *buffer) {
//    struct in_addr addr;
//    addr.s_addr = htonl(ip_address);  // Convert from host byte order to network byte order
//
//    if (inet_ntop(AF_INET, &addr, buffer, INET_ADDRSTRLEN) == NULL) {
//        perror("inet_ntop failed");
//        exit(EXIT_FAILURE);
//    }
//}

//
//int main(int , char** ) {
//    const char *ip_text = "192.168.1.1";
//    unsigned int ip_binary;
//    char ip_str[INET_ADDRSTRLEN];
//
//    // Convert from text to binary
//    ip_binary = text_to_binary(ip_text);
//    printf("IP Address in Binary (unsigned int): %u\n", ip_binary);
//
//    // Convert back from binary to text
//    binary_to_text(ip_binary, ip_str);
//    printf("IP Address in Text (dotted-decimal): %s\n", ip_str);
//}


//convert_ip_to_binary

//
//int main() {
//    const char *ipv4_address = "192.168.1.1";
//
//    struct in_addr addr4;
//
//    int success4 = inet_pton(AF_INET, ipv4_address, addr4);
//}