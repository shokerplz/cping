#include <stdio.h> 
#include <sys/types.h>
#include <errno.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <netdb.h> 
#include <unistd.h> 
#include <string.h> 
#include <stdlib.h> 
#include <netinet/ip_icmp.h> 
#include <time.h> 
#include <fcntl.h> 
#include <signal.h> 
#include "errors.h"
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#define DEFDATALEN      (64-ICMP_MINLEN)
#define MAXIPLEN        60
#define MAXICMPLEN      76
#define MAXPACKET       (65536 - 60 - ICMP_MINLEN)
#define PING_PKT_S 64
#define MAX_LOG_SIZE 8388806
#define LOG_PATH "..LOG.txt"
