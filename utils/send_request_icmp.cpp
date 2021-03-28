#include "icmp_sendrecv.h"
#include "calc_checksum.h"
#include "internal.h"
struct ping_pkt
{
    struct icmphdr hdr;
    char msg[PING_PKT_S-sizeof(struct icmphdr)];
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
