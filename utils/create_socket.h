#include <stdio.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h> 
#include <cstring>
#include <time.h>
#include "errors.h"
#define DEF_TTL 64
int create_socket();
