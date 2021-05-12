#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <cstring>
#include <time.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include "errors.h"
#define DEFDATALEN      (64-ICMP_MINLEN)
#define MAXIPLEN        60
#define MAXICMPLEN      76
#define MAXPACKET       (65536 - 60 - ICMP_MINLEN)
#define PING_PKT_S 64
#define DEF_TTL 64
struct ping_pkt
{
    struct icmphdr hdr;
    char msg[PING_PKT_S-sizeof(struct icmphdr)];
};
unsigned short checksum(unsigned short *b, int len) {
        unsigned short *buf = b;
        unsigned int sum = 0;
        unsigned short result;
        for ( sum = 0; len > 1; len -= 2 ) {
                sum += *buf++;
        }
        if ( len == 1 ) {
                sum += *(unsigned char*)buf;
        }
        sum = (sum >> 16) + (sum & 0xFFFF);
        sum += (sum >> 16);
        result = ~sum;
        return result;
};
int create_socket() {
        int sockfd;
        int ttl = DEF_TTL;
        struct timeval timeout;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;
        sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
        if (sockfd < 0)
        {
                printf("%s\n", "Socket file descriptor not received");
                return(FD_NOT_RECEIVED);
        }
        if (setsockopt(sockfd, SOL_IP, IP_TTL, &ttl, sizeof(ttl)) != 0) {
                printf("%s\n", "Can not set TTL socket option");
                return(TTL_NOT_SET);
        }
        if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout)) != 0) {
                printf("%s\n", "Can not set timeout socket option");
                return(TIMEOUT_NOT_SET);
        }
        return(sockfd);
};
int send_request_icmp(in_addr_t dst_addr, int *sockfd) {
	struct sockaddr_in dst_addr_s;
	*sockfd = create_socket();
        struct ping_pkt icmp_pkt;
        memset(&dst_addr_s, 0, sizeof(dst_addr_s));
        dst_addr_s.sin_family = AF_INET;
        dst_addr_s.sin_addr.s_addr = dst_addr;
        int i = 0, msg_count = 0;
        memset(&icmp_pkt, 0, sizeof(icmp_pkt));
        icmp_pkt.hdr.type = ICMP_ECHO;
        icmp_pkt.hdr.un.echo.id = getpid();
        memset(&icmp_pkt.msg, 0, sizeof(icmp_pkt.msg));
        icmp_pkt.msg[i] = 0;
        icmp_pkt.hdr.un.echo.sequence = htons(msg_count++);
        icmp_pkt.hdr.checksum = checksum((unsigned short *)&icmp_pkt.hdr, sizeof(icmp_pkt));
        if (sendto(*sockfd, &icmp_pkt, sizeof(icmp_pkt), 0, (struct sockaddr *) &dst_addr_s, sizeof(dst_addr_s)) <= 0) {
                printf("%s\n", "Sent failed and error is: ");
                perror("");
                return(SENT_FAILED);
        }
        char dst_addr_str[256];
        inet_ntop(AF_INET, &dst_addr, dst_addr_str, sizeof(dst_addr_str));
        printf("%s%s\n", "Successfully sent packet to ", dst_addr_str);
        return 0;
};
