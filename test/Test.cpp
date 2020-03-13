#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>

using std::stof;
using std::string;
using std::to_string;
using std::vector;
using std::stoi;


int main () {
 string line, key, value0, value1, value2, value3, result, user, x;
  // std::ifstream filestream("/proc/3330/status");
  // if (filestream.is_open()) {
  //   while (std::getline(filestream, line)) {
  //     std::istringstream linestream(line);
  //     linestream >> key >> value0 >> value1 >> value2 >> value3;
  //       if (key == "Uid:") {
  //         result = value0;
  //         std::cout << "line " << line << "\n";
  //         std::cout << "result " << result << "\n";
  //       }
  //   }
  // }


  std::ifstream filestream("/etc/passwd");
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> user >> x >> key;
        if (key == to_string(0)) {
          result = user;
           std::cout << "line " << line << "\n";
          std::cout << "result " << result << "\n";
        }
    }
  } 

}