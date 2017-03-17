#include "../include/net_common.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stdout, "Usage: %s hostname port\n", argv[0]);
        exit(EXIT_FAILURE);
    } 
    char* hostname = argv[1];
    char* portname = argv[2];
    struct addrinfo* addr = rio_resolve(hostname, portname); 
    int sockfd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    if (sockfd == -1) {
        fprintf(stderr, "failed to create socket");
        exit(EXIT_FAILURE);
    }
    if (connect(sockfd, addr->ai_addr, addr->ai_addrlen) == -1) {
        fprintf(stderr, "failed to connect server");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    freeaddrinfo(addr); 
    char cmd = CMD_CLOSE;
    rio_send(sockfd, &cmd, 1);
    close(sockfd);
    return 0; 
}
