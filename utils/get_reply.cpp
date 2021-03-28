#include "icmp_sendrecv.h"
extern int errno;
u_char *packet, outpack[MAXPACKET];
int get_reply(int sockfd) {
	int packlen, datalen = DEFDATALEN;
	struct ip *ip;
	struct sockaddr_in r_addr;
	char dst_addr_str[256];
	socklen_t sock_len = sizeof(r_addr);
	packlen = datalen + MAXIPLEN + MAXICMPLEN;
	if ( (packet = (u_char *)malloc((u_int)packlen)) == NULL)
	{
		return -1;
	};
        if (recvfrom(sockfd, (char *)packet, packlen, 0, (struct sockaddr *) &r_addr, &sock_len) < 0) {
                if (errno == EAGAIN) {
                        printf("%s\n", "Receive timeout exceeded");
                }
                return(RCV_FAILED);
        }
	ip = (struct ip *)((char*)packet);
        inet_ntop(AF_INET, &ip->ip_src, dst_addr_str, sizeof(dst_addr_str));
        printf("%s%s\n", "Successfully received packet from ", dst_addr_str);
	return 0;
}
