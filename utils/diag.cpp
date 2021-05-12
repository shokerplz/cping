#include <stdio.h>
#include "errors.h"
void diag(int error_code) {
	switch (error_code) {
		case FD_NOT_RECEIVED:
			printf("%s\n", "File descriptor not received");
			break;
		case TTL_NOT_SET:
			printf("%s\n", "Failed setting TTL for socket");
			break;
		case TIMEOUT_NOT_SET:
			printf("%s\n", "Failed setting timeout for socket");
			break;
		case SENT_FAILED:
			printf("%s\n", "Failed sending icmp packet");
			break;
		case RCV_FAILED:
			printf("%s\n", "Failed receiving icmp echo response");
			break;
		case NO_ADDR:
			printf("%s\n", "Address was not specified");
			break;
		case ARGS_NOT_VALID:
			printf("%s\n", "Argumnets are not valid");
			break;
		case IP_NOT_VALID:
			printf("%s\n", "IP address is not valid");
			break;
		case NO_HOST_FOUND:
			printf("%s\n", "No A entry found in DNS record");
			break;
		case NO_ADDRESS_FOUND:
			printf("%s\n", "No address found in DNS record");
			break;
		case NO_RECOVERY_PSB:
			printf("%s\n", "No DNS recovery");
			break;
		case TRY_AGAIN_LTR:
                        printf("%s\n", "DNS server response: Try again later");
                        break;
		case DNS_SRV_ERR:
                        printf("%s\n", "DNS server error");
                        break;
		case ALL_MEM_ERR:
			printf("%s\n", "Error happend while allocating memory for ICMP socket");
                        break;
		case UNKNOWN_ERROR:
			printf("%s\n", "Unknown error happend");
			break;
	}
}
