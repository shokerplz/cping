#include "validate_args.h"
bool cNumber(const std::string& str){
   return !str.empty() &&
   (str.find_first_not_of("[0123456789]") == std::string::npos);
}

std::vector<std::string> split2(const std::string& str, char delim){
   int i = 0;
   std::vector<std::string> list;
   int pos = str.find(delim);
   while (pos != std::string::npos){
      list.push_back(str.substr(i, pos - i));
      i = ++pos;
      pos = str.find(delim, pos);
   }
   list.push_back(str.substr(i, str.length()));
   return list;
}

bool check_hostname(char *dns){
    const std::regex pattern("^(?!-)[A-Za-z0-9-]+([\\-\\.]{1}[a-z0-9]+)*\\.[A-Za-z]{2,6}$");
    std::string s = std::string(dns);

    if(std::regex_match(s, pattern))
    {
        return true;
    }
    else
    {
        return false;
    } 

}

bool check_ip(char *ip){

   std::vector<std::string> slist = split2(ip, '.');

   if (slist.size() != 4)
      return false;
   for (std::string str : slist){

      if (!cNumber(str) || std::stoi(str) < 0 || std::stoi(str) > 255)
         return false;
   }
   return true;

}

bool validate_args(bool *is_dnsname, char **dst_hostname, char **dst_ip, int argc, char *argv[], bool *verbose_output){
    
    if (std::string(argv[1]) == "-v"){
        *verbose_output = true;
        if (argc != 3){
            printf("%s\n", "[validate_args] Error: Wrong number of input parameters");
            return false;
        }
        if (check_hostname(argv[2])){
            *dst_hostname = argv[2];            
            *is_dnsname = true;
            return true;

        }else if(check_ip(argv[2])){
            *dst_ip = argv[2];
            printf("%s\n",*dst_ip);
            return true;

        }else{
            printf("%s\n", "[validate_args] Error: Invalid ip or hostname");
            return false;
        }
    }
    else if (argc != 2){
        return false;
    } else {
        if (check_hostname(argv[1])){
            *dst_hostname = argv[1];
            *is_dnsname = true;
            return true;
        } else if(check_ip(argv[1])){  
            *dst_ip = argv[1];
            return true;
        } else {
            printf("%s\n", "[validate_args] Error: Invalid ip or hostname");
            return false;
        }
    }
    return true;
};
