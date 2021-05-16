/*                  ---main function---
*   main function is entry point of program. All program functions will be executed from here
*   Main argumets are passed through argc and argv variables. argc is int32 variable which indicates lenght of argv array.
*   User can pass or -v as argv[1] and DNS name or IPv4 address as argv[2] or only dns name or IPv4 address as argv[1].
*   All other combination of argumets will lead to exception and program will be terminated with error code 212
*   Example of program execution: ping <IPv4 OR DNS name>
*               First example:
*               ping my.mail.ru
*               argv[0] = ping
*               argv[1] = my.mail.ru
*
*               Second example:
*               ping -v my.mail.ru
*               argv[0] = ping
*               argv[1] = -v
*               argv[2] = my.mail.ru
*
* Exit codes:
* 0   - Success
* LOG related errors:
* 150 - No space for LOG file
* 151 - Can not write to LOG file
* Validation errors:
* 211 - IPv4 address or DNS name were not passed
* 213 - IPv4 address is not valid
* 212 - DNS name is not valid
* 255 - Unknown validation error
* Resolving errors:
* 110 - No DNS record found
* 111 - No A record in DNS record found
* 112 - Can not get DNS record
* 113 - DNS server response: try again later
* 114 - DNS server error
* Socket creation errors:
*-100 - File descriptor was not received
*-102 - Timeout setting error
*-101 - TTL setting error
* Sending/Receiving errors:
* 200 - Sending error
* 201 - Receiving error
* 202 - Error allocating memory for ICMP-echo reply
*/
#include "main.h"
int main(int argc, char* argv[])
{
    FILE* log_fd;
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
    switch (create_log(log_fd)) {
    case 0:
        switch (log(log_fd, "Logging started")) {
            case 0:
                break;
            case 1:
                diag(LOG_ERROR);
                break;
        }

        //Log successfully created
        break;
    case 1:
        //No free space on drive
        diag(NO_FREE_SPACE);
        return(NO_FREE_SPACE);
        break;
    }
    switch(is_dnsname) {
    case true:
        // DNS name passed
        dst_ip=(char*)malloc(NI_MAXHOST*sizeof(char));
        switch(getIP(&(*dst_hostname), dst_ip)) {
        case 0:
        // Successfully resolved DNS name
            switch (log(log_fd, "Successfully resolved DNS name")) {
            case 0:
                break;
	    case 1:
		diag(LOG_ERROR);
		break;
            }
            break;
        case 1:
        // Can not resolve DNS name
            switch (log(log_fd, "Can not resolve DNS name")) {
            case 0:
        //Successfully logged error
                break;
            case 1:
        //Unsuccessfully logged error
                diag(DNS_SRV_ERR);
                break;
            }
            close_log(log_fd,DNS_SRV_ERR);
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
        switch (log(log_fd, "Can not get IPv4 address from string")) {
        case 0:
        //Successfully logged error
            break;
        case 1:
        //Unsuccessfully logged error
            diag(IP_NOT_VALID);
            break;
        }
        close_log(log_fd,IP_NOT_VALID);
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
        switch (log(log_fd, "Successfully sent ICMP request")) {
            case 0:
                break;
            case 1:
                diag(LOG_ERROR);
                break;
        }
        break;
    case SENT_FAILED:
        //Error occurred while sending ICMP request
        switch (log(log_fd, "Error sending ICMP request")) {
        case 0:
        //Successfully logged error
            break;
        case 1:
        //Unsuccessfully logged error
            diag(SENT_FAILED);
            break;
        }
        diag(SENT_FAILED);
        close_log(log_fd,SENT_FAILED);
        return SENT_FAILED;
        break;
    }
        // Receiving ICMP-echo response
    switch(get_reply(sockfd)) {
    case 0:
        // Successfully received ICMP-echo response
        switch (log(log_fd, "Successfully received ICMP-echo response")) {
            case 0:
                break;
            case 1:
                diag(LOG_ERROR);
                break;
        }
        break;
    case RCV_FAILED:
        //Timeout receiving ICMP-echo response
        switch (log(log_fd, "Error happend while receiving ICMP request")) {
        case 0:
         //Successfully logged error
            break;
        case 1:
         //Unsuccessfully logged error
            diag(RCV_FAILED);
            break;
        }
        diag(RCV_FAILED);
        close_log(log_fd,RCV_FAILED);
        return RCV_FAILED;
        break;
    case -1:
        //Error allocating memory for ICMP-echo reply
        switch (log(log_fd, "Error happend while allocating memory for ICMP socket")) {
        case 0:
         //Successfully logged error
            break;
        case 1:
         //Unsuccessfully logged error
            diag(ALL_MEM_ERR);
            break;
        }
    diag(ALL_MEM_ERR);
        close_log(log_fd,ALL_MEM_ERR);
        return ALL_MEM_ERR;
        break;
    }
        // Program executed successfully
    
    close_log(log_fd,0);
    return 0;
}
