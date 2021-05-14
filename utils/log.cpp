#include "icmp_sendrecv.h"
#include "string"
#include <sstream>
int create_log(FILE* log_fd){
    if( (log_fd  = fopen( LOG_PATH, "a+" )) == NULL ) return 1;
    else return 0;
}

int64_t getFileSize(FILE* log_fd){
	int64_t file_size;
    int64_t current_pos;
    current_pos = ftell(log_fd);
    fseek(log_fd, 0, SEEK_END);
    file_size = ftell(log_fd);
	return file_size;
}

int overflow(FILE* log_fd, int message_len) { 
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

int log(FILE* log_fd, std::string message)
{
    struct tm* u;
    std::stringstream ss;
    char buf[256];
	time_t It;
	It = time(NULL);
	u = localtime(&It);	
	strftime(buf, sizeof(buf), "[ %d-%m-%Y %H:%M:%S ] ", u);
	ss << buf << "\t" << message << "\n";
    message = ss.str();
    int message_len = message.length();
	switch (overflow(log_fd, message_len)){
        case 0:
            break;
        case 1:
            return 1;
    }
    if (fwrite(message.data(), sizeof(char), message_len, log_fd) != message_len)
    {
        return 1;
    }
    return 0;

}