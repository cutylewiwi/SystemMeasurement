#include "../include/net_common.h"

double peak;
double acc;
microtime_t current;
microtime_t gap;

double max(double a, double b) {
    return a > b ? a : b;
}

void update(microtime_t l, microtime_t r, int size) {
    double rate = size / (r - l + 1);
    // current < l
    if (current + gap - 1 < l) {
        peak = max(peak, acc);
        acc = 0;
        current = l / gap * gap;
    }
    // current <= l && current + gap - 1 >= l
    if (current + gap - 1 < r) {
        acc += (current + gap - l) * rate; 
        peak = max(peak, acc);
        acc = 0;
        current = current + gap;
        // current > l
        if (current + gap - 1 < r) {
            peak = max(peak, gap * rate);
            current = r / gap * gap;
        }
    }
    // current <= r && current + gap - 1 >= r 
    acc += (r - current + 1) * rate;
}

int main(int argc, char* argv[]) {
    if (argc != 6) {
        fprintf(stdout, "Usage: %s hostname port num_iters data_size gap(millisecond)\n", argv[0]);
        exit(EXIT_FAILURE);
    } 
    char* hostname = argv[1];
    char* portname = argv[2];
    int num_iters = atoi(argv[3]);
    int data_size = atoi(argv[4]);
    gap = atoi(argv[5]) * 1000;
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
    char cmd = CMD_PEAK;
    struct timeval start;
    struct timeval end;
    char* data = malloc(data_size);
    for (int i = 0; i != num_iters; ++i) {
        peak = acc = 0;
        current = 0ULL;
        rio_rpsend(sockfd, &cmd, 1);
        rio_rpsend(sockfd, (char*)&data_size, sizeof(data_size));
        char* buf = data;
        int len = data_size;
        while (len > 0) {
            gettimeofday(&start, NULL);
            int res = rio_recv(sockfd, data, len);
            gettimeofday(&end, NULL);
            update(timeval_to_microtime(&start), timeval_to_microtime(&end), res);
            buf += res;
            len -= res;
        }
        peak = max(peak, acc);
        fprintf(stdout, "%.lf\n", peak);
    }
    free(data);
    close(sockfd);
    return 0; 
}
