#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "linux_parser.h"
#include "unistd.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;
using std::stoi;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

float LinuxParser::MemoryUtilization() { 
  std::string memtotal, memfree, memavail, membufs;
  float fmemtotal, fmemfree;
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
        } else if (key == "MemFree:") {
          fmemfree = std::stof(value);
        } 
     }
    }
    result = (fmemtotal - fmemfree) / fmemtotal;
  }
  return result; 
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

vector<string> LinuxParser::CpuUtilization() { 
  string line;
  string key;
  string value0, value1, value2, value3, value4, value5, value6, value7, value8, value9;
  vector<string> result{};
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value0 >> value1 >> value2 >> value3 >> value4 >> value5 >> value6 >> value7 >> value8 >> value9;
        if (key == "cpu") {
          result.emplace_back(value0);
          result.emplace_back(value1);
          result.emplace_back(value2);
          result.emplace_back(value3);
          result.emplace_back(value4);
          result.emplace_back(value5);
          result.emplace_back(value6);
          result.emplace_back(value7);
          result.emplace_back(value8);
          result.emplace_back(value9);
        }
    }
  } 
  return result;
}

int LinuxParser::TotalProcesses() { 
  string line;
  string key;
  string value;
  int result = 0;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
        if (key == "processes") {
          result = stoi(value);
        }
    }
  } 
  return result;
}

int LinuxParser::RunningProcesses() { 
  string line;
  string key;
  string value;
  int result = 0;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
        if (key == "procs_running") {
          result = stoi(value);
        }
    }
  } 
  return result;
}

string LinuxParser::Command(int pid) { 
  string cmd;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, cmd);
  }
  return cmd;
}

string LinuxParser::Ram(int pid) { 
  string line, key, value, result;
  float memFloat1, memFloat2;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) +  kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
        if (key == "VmSize:") {
          memFloat1 = stof(value);
          memFloat2 = memFloat1/1024;
        }
    }
  } 
  result = to_string(memFloat2);
  int pos = result.find(".");
  result = result.substr(0,pos);
  return result;
 }

string LinuxParser::Uid(int pid) { 
  string line, key, value, result;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) +  kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
        if (key == "Uid:") {
          result = value;
        }
    }
  } 
  return result;

}

string LinuxParser::User(int pid) { 
  string line, user, x, result;
  string key;
  string uid = LinuxParser::Uid(pid);
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> user >> x >> key;
        if (key == uid) {
          result = user;
        }
    }
  } 
  return result;
 }

long LinuxParser::UpTime(int pid) { 

  string line;
  vector<string> tokens; 
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    string token;
    while(linestream >> token) tokens.push_back(token);
  }

  long secs = stol(tokens[21]);
  long hertz = sysconf(_SC_CLK_TCK);
  return secs / hertz;
}

long LinuxParser::UpTime() { 
  long system_time;
  long idle_time;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> system_time >> idle_time;
  }
  return system_time; 
}

float LinuxParser::CpuUtilization(int pid) { 

  string line;
  vector<string> tokens; 
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    string token;
    while(linestream >> token) tokens.push_back(token);
  }

  long hertz = sysconf(_SC_CLK_TCK);
  long utime = stol(tokens[13]);
  long stime = stol(tokens[14]);
  long cutime = stol(tokens[15]);
  long cstime = stol(tokens[16]);
  long starttime = stol(tokens[21]);
  long uptime = UpTime();

  long total_time = utime + stime;
  total_time = total_time + cutime + cstime;
  float seconds = uptime - (starttime / hertz);
  float cpu_usage = ((total_time / hertz) / seconds);
  return cpu_usage;
}