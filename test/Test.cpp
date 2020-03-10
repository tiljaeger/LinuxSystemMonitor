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
  std::string memtotal, memfree, memavail, membufs;
  float fmemtotal, fmemfree, fmemavail, fmembufs;
  float result = 0.0;
  std::string key, value;
  std::string line;
  std::ifstream stream("/proc/meminfo");
  if (stream.is_open()) {
      while (std::getline(stream, line)) {
    std::istringstream linestream(line);
     while (linestream >> key >> value) {
        if (key == "MemTotal:") {
          fmemtotal = std::stof(value);
          std::cout << "MemTotal" <<fmemtotal << "\n";
        } else if (key == "MemFree:") {
          fmemfree = std::stof(value);
          std::cout << "MemFree" << fmemfree << "\n";
        } else if (key == "MemAvailable:") {
          fmemavail = std::stof(value);
          std::cout << "MemAvailable" << fmemavail << "\n";
        } else if (key == "Buffers:") {
          fmembufs = std::stof(value);
          std::cout << "Buffers" <<fmembufs << "\n";
        }
     }
  }
  result = (fmemtotal - fmemfree) / fmemtotal;
  }
  return result; 
}