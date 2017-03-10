#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "../include/net_common.h"

#define DATA_SIZE 1 << 30

char data[DATA_SIZE];

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stdout, "Usage: %s port\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int port = atoi(argv[1]);
    struct sockaddr_in addr;
    int sock;

    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        fprintf(stderr, "Failed creating socket.\n");
        exit(EXIT_FAILURE);
    }
    int yes = 1;
    if (setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof yes) == -1) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock, (struct sockaddr *) &addr, sizeof(addr))) {
        close(sock);
        fprintf(stderr, "Failed binding socket at port %d.\n", port);
        exit(EXIT_FAILURE);
    }

    if (listen(sock, 5)) {
        close(sock);
        fprintf(stderr, "Error listening on socket.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "----- Benchmark Server -----\n");
    while (1) {
        struct sockaddr_in cli_addr;
        socklen_t cli_size;
        int sockfd = accept(sock, (struct sockaddr *) &cli_addr, &cli_size);
        if (sockfd < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        while (1) {
            char cmd;
            if (rio_rprecv(sockfd, &cmd, 1) == 0) {
                break;
            }
            switch (cmd) {
                case CMD_RTT: {
                    char ch = ' ';
                    rio_rpsend(sockfd, &ch, 1);
                    break;
                }
                case CMD_PEAK: {
                    int data_size;
                    if (rio_rprecv(sockfd, (char*)&data_size, sizeof(data_size)) < sizeof(data_size)) {
                        break;
                    }
                    rio_rpsend(sockfd, data, data_size);
                    break;
                }
            }
        }
        close(sockfd);
    }
    return 0;
}
