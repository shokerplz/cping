#include "create_socket.h"
int create_socket() {
        int sockfd;
        int ttl = DEF_TTL;
        struct timeval timeout;
        timeout.tv_sec = 1;
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
