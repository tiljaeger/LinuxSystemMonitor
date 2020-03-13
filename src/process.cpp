#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include "linux_parser.h"
#include "process.h"
#include <iostream>

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) {
     pid_= pid;
     user_ = LinuxParser::User(pid_);
     command_ = LinuxParser::Command(pid_);
     ram_ = LinuxParser::Ram(pid_);
     uptime_ = LinuxParser::UpTime(pid_);
     cpu_util_ = LinuxParser::CpuUtilization(pid_);
}

int Process::Pid() { 
    return pid_; 
}

float Process::CpuUtilization() {
    return cpu_util_; 
}

string Process::Command() { 
    return command_; 
}

string Process::Ram() { 
    return ram_;
}

string Process::User() { 
    return user_; 
}

long int Process::UpTime() { 
    return uptime_; 
}

bool Process::operator<(Process const& a) const { 
    return cpu_util_ > a.cpu_util_; }