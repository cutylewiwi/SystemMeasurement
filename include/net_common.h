#ifndef _NET_COMMON_H_
#define _NET_COMMON_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <netdb.h>

#define CMD_RTT 1
#define CMD_PEAK 2
#define CMD_CLOSE 3

typedef unsigned long long microtime_t;

struct addrinfo* rio_resolve(char* hostname, char* portname) {
    struct addrinfo hints;
    memset(&hints,0,sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;
    hints.ai_flags = AI_ADDRCONFIG;
    struct addrinfo* addr = 0;
    int err = getaddrinfo(hostname,portname,&hints,&addr);
    if (err != 0) {
        fprintf(stderr, "failed to resolve remote socket addaddrs (err=%d)", err);
        exit(EXIT_FAILURE);
    }
    return addr;
}

int rio_send(int sock, char* buf, int len) {
    int res = send(sock, buf, len, 0); 
    if (res <= 0) {
        perror("rio_send");
        exit(EXIT_FAILURE);
    }
    return res;
}

int rio_recv(int sock, char* buf, int len) {
    int res = recv(sock, buf, len, 0);
    if (res < 0) {
        perror("rio_recv");
        exit(EXIT_FAILURE);
    }
    return res;
}

void rio_rpsend(int sock, char* buf, int len) {
    while (len > 0) {
        int res = rio_send(sock, buf, len);
        buf += res;
        len -= res;
    }
}

int rio_rprecv(int sock, char* buf, int len) {
    int total = len;
    while (len > 0) { 
        int res = rio_recv(sock, buf, len);
        if (res == 0) {
            break;
        }
        buf += res;
        len -= res;
    }
    return total - len;
}

microtime_t timeval_to_microtime(struct timeval* tv) {
    return tv->tv_sec * 1000000ULL + tv->tv_usec;
}

#endif