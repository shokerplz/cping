#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include "errors.h"
#include <cstring>
struct hostent *he;
struct in_addr **addr_list;
struct in_addr addr;
extern int h_errno;
int getIP(char *dnsname, char *dst_ip) {
        he = gethostbyname(dnsname);
        if (he == NULL) {
                switch(h_errno) {
                        case HOST_NOT_FOUND:
				return NO_HOST_FOUND;
                                break;
                        case NO_ADDRESS:
				return NO_ADDRESS_FOUND;
                                break;
                        case NO_RECOVERY:
				return NO_RECOVERY_PSB;
                                break;
                        case TRY_AGAIN:
				return TRY_AGAIN_LTR; 
                                break;
                }
                return DNS_SRV_ERR;
        }
        strcpy(dst_ip, inet_ntoa(*(struct in_addr *) he->h_addr));
        return 0;
}
