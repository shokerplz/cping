#include <netinet/in.h> 
int send_request_icmp(in_addr_t dst_addr, int *sockfd);
char *getIP(char *dnsname);
bool validate_args(bool *is_dnsname, char **dst_hostname, char **dst_ip, int argc, char *argv[], bool *verbose_output);
int get_reply(int sockfd);
