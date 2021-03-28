#include <string>
#include <vector>
bool chkNumber(const std::string& str){
   return !str.empty() &&
   (str.find_first_not_of("[0123456789]") == std::string::npos);
}
// Function to split string str using given delimiter
std::vector<std::string> split(const std::string& str, char delim){
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
// Function to validate an IP address
bool validateIP(char *ip){
   // split the string into tokens
   std::vector<std::string> slist = split(ip, '.');
   // if token size is not equal to four
   if (slist.size() != 4)
      return false;
   for (std::string str : slist){
      // check that string is number, positive, and range
      if (!chkNumber(str) || std::stoi(str) < 0 || std::stoi(str) > 255)
         return false;
   }
   return true;
}
