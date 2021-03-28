#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <cstring>
struct hostent *he;
struct in_addr **addr_list;
struct in_addr addr;
