#include "../include/net_common.h"

#define MAX_SIZE_KB (1 << 20)

char data[MAX_SIZE_KB * 1000];

int main(int argc, char* argv[]) {
    if (argc != 5) {
        fprintf(stdout, "Usage: %s hostname port num_iters data_size(KB)\n", argv[0]);
        exit(EXIT_FAILURE);
    } 
    char* hostname = argv[1];
    char* portname = argv[2];
    int num_iters = atoi(argv[3]);
    int data_size = atoi(argv[4]);
    struct addrinfo* addr = rio_resolve(hostname, portname); 
    char cmd = CMD_PEAK;
    for (int i = 0; i != num_iters; ++i) {
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
        rio_rpsend(sockfd, &cmd, 1);
        rio_rpsend(sockfd, (char*)&data_size, sizeof(data_size));
        int remain_size = data_size;
        while (remain_size > 0) {
            int send_size = min(MAX_SIZE_KB, data_size);
            rio_rpsend(sockfd, data, send_size * 1000);
            remain_size -= send_size;
        }
        close(sockfd);
        usleep(1000);
    }
    freeaddrinfo(addr);
    return 0; 
}
