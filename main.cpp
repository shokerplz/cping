#include "utils/errors.h"
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include "utils/utils.h"
#include <arpa/inet.h>
#include "utils/validate_ip.h"
int main (int argc, char *argv[]) {
        bool is_dnsname = false; // Boolean for check if dns name promted or ip address
        bool valid_args = true; // Boolean for check if args are valid
        struct sockaddr_in sa;   // Stuct which holds ip address. More in netinet/in.h. https://www.gta.ufrj.br/ensino/eel878/sockets/sockaddr_inman.html
        struct hostent *he;	 // Stuct which holds ip info from gethostbyname. More in netdb.h. https://www.gta.ufrj.br/ensino/eel878/sockets/gethostbynameman.html
        int sockfd;
        in_addr_t dst_addr;
        printf("%s\n", "Ping starts");
        if (argc < 2) {
                printf("%s\n", "You have not specified address to send ICMP packet");
                exit(NO_ADDR);
        }
        printf("%s\n", "Validate other args");
        // valid_args = validate_args();
        if (!valid_args) {
                printf("%s\n", "Args are not valid. More complex output will be in validate_args function. Program will exit now!");
                exit(ARGS_NOT_VALID);
        }
        printf("%s\n", "Check if next arg is dns name or ip address");
        // is_dnsname = check_arg();
        if (is_dnsname) {
                he = gethostbyname(argv[1]);
        }
        if (validateIP(argv[1])) {
                printf("%s\n", "IP address is valid. Continuing");
        } else {
                printf("%s\n", "IP address is invalid. Program will exit now");
                exit(IP_NOT_VALID);
        }
        dst_addr = inet_addr(argv[1]);
        sockfd = create_socket();
        int result = sendrecv_icmp(dst_addr, sockfd);
        // Next will be inet_pton(AF_INET, "1.1.1.1", &(sa.sin_addr));
        return 0;
}
