#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include "utils/errors.h"
#include <arpa/inet.h>
#include "main.h"
int main(int argc, char* argv[])
{
    	// Validating input arguments
    switch(validate_args(&is_dnsname, &dst_hostname, &dst_ip, argc, argv, &verbose_output)) {
    case true:
        // Arguments are valid
        break;
    case false:
        //Arguments are not valid
        diag(ARGS_NOT_VALID);
        return(ARGS_NOT_VALID);
    }

    	// Creating log file
    //switch (create_log(&log_fd)) {
    //case 0:
    	// Log successfully created
    //    break;
    //case 1:
    	// No free space on drive
    //    diag(150);
    //    return(151);
    //    break;
    //}
    switch(is_dnsname) {
    case true:
        // DNS name passed
        dst_ip=(char*)malloc(NI_MAXHOST*sizeof(char));
        switch(getIP(&(*dst_hostname), dst_ip)) {
        case 0:
        // Successfully resolved DNS name
            break;
        case 1:
        // Can not resolve DNS name
            //switch (log(logfd, "Can not resolve DNS name")) {
            //case 0:
        // Successfully logged error
            //    break;
            //case 1:
        // Unsuccessfully logged error
            //    diag(161);
            //    break;
            //}
            return(DNS_SRV_ERR);
            break;
        }
        break;
    case false:
        // IPv4 address passed => no need to resolve it
        break;
    }
    dst_addr = inet_addr(dst_ip);
    switch(dst_addr) {
    case INADDR_NONE:
        //switch (log(logfd, "Can not get IPv4 address from string")) {
        //case 0:
        // Successfully logged error
        //    break;
        //case 1:
        // Unsuccessfully logged error
        //    diag(150);
        //    break;
        //}
        return(IP_NOT_VALID);
        break;
    default:
        // Successfully resolved IPv4 address
        break;
    }
    	// Sending ICMP-echo request
    switch(send_request_icmp(dst_addr, &sockfd)) {
    case 0:
        // Successfully sent ICMP request
        break;
    case SENT_FAILED:
        // Error occurred while sending ICMP request
        //switch (log(logfd, "Error sending ICMP request")) {
        //case 0:
        // Successfully logged error
        //    break;
        //case 1:
        // Unsuccessfully logged error
        //    diag(200);
        //    break;
        //}
	diag(SENT_FAILED);
        return SENT_FAILED;
        break;
    }
    	// Receiving ICMP-echo response
    switch(get_reply(sockfd)) {
    case 0:
        // Successfully received ICMP-echo response
        break;
    case RCV_FAILED:
        // Timeout receiving ICMP-echo response
        //switch (log(logfd, "Error happend while receiving ICMP request")) {
        //case 0:
        // Successfully logged error
        //    break;
        //case 1:
        // Unsuccessfully logged error
        //    diag(201);
        //    break;
        //}
	diag(RCV_FAILED);
        return RCV_FAILED;
        break;
    case -1:
        // Error allocating memory for ICMP-echo reply
        //switch (log(logfd, "Error happend while allocating memory for ICMP socket")) {
        //case 0:
        // Successfully logged error
        //    break;
        //case 1:
        // Unsuccessfully logged error
        //    diag(202);
        //    break;
        //}
	diag(ALL_MEM_ERR);
        return ALL_MEM_ERR;
        break;
    }
    	// Program executed successfully
    return 0;
}
