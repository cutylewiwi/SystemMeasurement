#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/param.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>

#ifndef ICMP_FILTER
#define ICMP_FILTER	1
struct icmp_filter {
    int data;
};
#endif


unsigned short checksum(void *b, int len)
{
    unsigned short *buf = b;
    unsigned int sum=0;
    unsigned short result;

    for ( sum = 0; len > 1; len -= 2 )
        sum += *buf++;
    if ( len == 1 )
        sum += *(unsigned char*)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stdout, "Usage: %s hostname num_iters\n", argv[0]);
        exit(0);
    }
    setuid(getuid());
    int pid = getpid();
    char* hostname = argv[1];
    int num_iters = atoi(argv[2]);
    struct hostent * record = gethostbyname(hostname);
    if(record == NULL) {
        fprintf(stderr, "%s is unavailable\n", hostname);
        exit(1);
    }
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if(sock < 0) {
        fprintf(stderr, "Failed to create socket! Need root privilege\n");
        close(sock);
        exit(1);
    }
    struct sockaddr_in pingaddr;
    memset(&pingaddr, 0, sizeof(struct sockaddr_in));
    pingaddr.sin_family = AF_INET;
    memcpy(&pingaddr.sin_addr, record->h_addr, sizeof(pingaddr.sin_addr));
    // Only want to receive the following messages
    struct icmp_filter filter;
    filter.data = ~(1<<ICMP_ECHOREPLY);
    if(setsockopt(sock, SOL_RAW, ICMP_FILTER, (char *)&filter, sizeof(filter)) < 0) {
        fprintf(stderr, "setsockopt(ICMP_FILTER)");
        exit(1);
    }
    // set up ping packet
    char packet[sizeof(struct icmphdr)];
    memset(packet, 0, sizeof(packet));
    struct icmphdr *pkt = (struct icmphdr *)packet;
    pkt->type = ICMP_ECHO;
    pkt->code = 0;
    pkt->checksum = 0;
    pkt->un.echo.id = htons(pid & 0xFFFF);
    pkt->checksum = checksum(pkt, sizeof(packet));
    int i = 0;
    for (i = 0; i < num_iters; ++i) {
        pkt->un.echo.sequence = i;
        struct timeval start;
        gettimeofday(&start, NULL);
        int bytes = sendto(sock, packet, sizeof(packet), 0, (struct sockaddr *)&pingaddr, sizeof(struct sockaddr_in));
        if(bytes != sizeof(packet)) {
            fprintf(stderr, "Failed to send to receiver\n");
            close(sock);
            exit(1);
        }
        char inbuf[128];
        memset(inbuf, 0, sizeof(inbuf));
        int addrlen = sizeof(struct sockaddr_in);
        bytes = recvfrom(sock, inbuf, sizeof(inbuf), 0, (struct sockaddr*)&pingaddr, (socklen_t*)&addrlen);
        struct timeval end;
        gettimeofday(&end, NULL);
        if (bytes != sizeof(struct iphdr) + sizeof(struct icmphdr)) {
            fprintf(stderr, "Icmp failed to received");
        } else {
	    struct iphdr* iph = (struct iphdr*)inbuf;
            int hlen = (iph->ihl << 2);
            bytes -= hlen;
            pkt = (struct icmphdr*)(inbuf + hlen);
            int id = ntohs(pkt->un.echo.id);
            if (pkt->type == ICMP_ECHOREPLY && id == pid) {
                fprintf(stdout, "%d\n", (int)(end.tv_sec * 1000000 + end.tv_usec - start.tv_sec * 1000000 - start.tv_usec));
            }
	}
    }
    return 0; 
}
