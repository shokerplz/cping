#include "icmp_sendrecv.h"
#include "string"
#include <sstream>
int create_log(FILE*& log_fd){
    if( (log_fd  = fopen( LOG_PATH, "a+" )) == NULL ) return 1;
    else return 0;
}

int64_t getFileSize(FILE* log_fd){
	int64_t file_size;
    int64_t current_pos;
    current_pos = ftell(log_fd);
    fseek(log_fd, 0, SEEK_END);
    file_size = ftell(log_fd);
    fseek(log_fd,0,current_pos);
	return file_size;
}

int overflow(FILE*& log_fd, int message_len) { 
	int owerflow_flag = 0;
    int64_t file_size;
    file_size = getFileSize(log_fd);
    int64_t file_size_after_write = file_size  + message_len;
	if (file_size_after_write >= MAX_LOG_SIZE) owerflow_flag = 1; else owerflow_flag = 0;
	if (owerflow_flag)
	{
		fclose(log_fd);
        if( (log_fd  = fopen( LOG_PATH, "w+" )) == NULL ){
            return 1;
        } 
        else return 0;
	}
	return 0;
}

int log(FILE*& log_fd, char* message)
{

    struct tm* u;
    std::stringstream ss;
    char buf[256];
	time_t It;
	It = time(NULL);
	u = localtime(&It);	
	strftime(buf, sizeof(buf), "[ %d-%m-%Y %H:%M:%S ] ", u);
	ss << buf << "\t" << message << "\n";
    std::string write_message = ss.str();
    int write_message_len = write_message.length();
	switch (overflow(log_fd, write_message_len)){
        case 0:
            break;
        case 1:
            return 1;
    }
    if (fprintf(log_fd,ss.str().data()))
    {
        return 1;
    }
    return 0;

}


void close_log(FILE*& log_fd, int error_code){
    char* message;
    	switch (error_code) {
		case FD_NOT_RECEIVED:
			message = "File descriptor not received";
			break;
		case TTL_NOT_SET:
			message = "Failed setting TTL for socket";
			break;
		case TIMEOUT_NOT_SET:
			message = "Failed setting timeout for socket";
			break;
		case SENT_FAILED:
			message = "Failed sending icmp packet";
			break;
		case RCV_FAILED:
			message = "Failed receiving icmp echo response";
			break;
		case NO_ADDR:
			message = "Address was not specified";
			break;
		case ARGS_NOT_VALID:
			message = "Argumnets are not valid";
			break;
		case IP_NOT_VALID:
			message = "IP address is not valid";
			break;
		case NO_HOST_FOUND:
			message = "No A entry found in DNS record";
			break;
		case NO_ADDRESS_FOUND:
			message = "No address found in DNS record";
			break;
		case NO_RECOVERY_PSB:
			message = "No DNS recovery";
			break;
		case TRY_AGAIN_LTR:
                        message = "DNS server response: Try again later";
                        break;
		case DNS_SRV_ERR:
                        message = "DNS server error";
                        break;
		case ALL_MEM_ERR:
			message = "Error happend while allocating memory for ICMP socket";
                        break;
		case UNKNOWN_ERROR:
			message = "Unknown error happend";
			break;
        case 0:
            message = "Successfully end";
            break;
	}
    log(log_fd,message);
    log(log_fd,"End logging\n");
    fclose(log_fd);
}