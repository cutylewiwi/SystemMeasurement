#include "../include/net_common.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        fprintf(stdout, "Usage: %s hostname port num_iters\n", argv[0]);
        exit(EXIT_FAILURE);
    } 
    char* hostname = argv[1];
    char* portname = argv[2];
    int num_iters = atoi(argv[3]);
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
    char cmd = CMD_RTT;
    char ch;
    struct timeval start;
    struct timeval end;
    for (int i = 0; i!= num_iters; ++i) {
        gettimeofday(&start, NULL);
        rio_send(sockfd, &cmd, 1);
        rio_recv(sockfd, &ch, 1);
        gettimeofday(&end, NULL);
        // microsecond
        fprintf(stdout, "%llu\n", timeval_to_microtime(&end) - timeval_to_microtime(&start));
    }
    close(sockfd);
    return 0; 
}
