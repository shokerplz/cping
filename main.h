															// INCLUDE LIBS
#include <netdb.h>													
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include "utils/errors.h"
#include <arpa/inet.h>
			 												// VARIABLES DECLARATION
bool is_dnsname = false; 												// Boolean for check if dns name promted or ip address
bool valid_args = true;  												// Boolean for check if args are valid
struct sockaddr_in sa;   												// Struct which holds ip address. 
int sockfd;              												// File descriptor for socket
FILE* logfd;               												// File struct for log file
in_addr_t dst_addr;      												// Variable which holds IPv4 destination address
char *dst_hostname;      												// Variable which holds hostname in string format
char *dst_ip;            												// Variable which holds IPv4 in string format
bool verbose_output;     												// Boolean for verbose output { true => verbose, false => not verbose}
			 
			 												// FUNCTION DECLARATION
int getIP(char *dst_hostname, char *dst_ip);  										// Get ip from hostname;
int validate_args(bool *is_dnsname, char **dst_hostname, char **dst_ip, int argc, char *argv[], bool *verbose_output);  // Validate arguments
void diag(int error_code); 												// Diagnostics
int create_log(FILE *log_fd); 												// Log creation
int log(FILE*logfd, char* log_str); 											// Log function
int validateIP(char *ip); 												// IPv4 validation
int send_request_icmp(in_addr_t dst_addr, int *sockfd); 								// Send ICMP request to IPv4 addr
int get_reply(int sockfd); 												// Get reply from socket
