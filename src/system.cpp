#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"


using std::set;
using std::size_t;
using std::string;
using std::vector;
using std::sort;

Processor& System::Cpu() { 
    return cpu_; 
}

vector<Process>& System::Processes() { 
    processes_.clear();
    vector<int> pids = LinuxParser::Pids();
    for (unsigned int i=0; i< pids.size(); i++) {
        int currentPid = pids[i];
        Process process (currentPid);
        processes_.emplace_back(process);
    }
    std::sort(processes_.begin(), processes_.end());
    return processes_; }

string System::Kernel() { 
    return LinuxParser::Kernel(); 
}

float System::MemoryUtilization() {     
    return LinuxParser::MemoryUtilization(); 
}

string System::OperatingSystem() { 
    return LinuxParser::OperatingSystem(); 
}

int System::RunningProcesses() { 
    return LinuxParser::RunningProcesses(); 
}

int System::TotalProcesses() { 
    return LinuxParser::TotalProcesses(); 
}

long int System::UpTime() { 
    return LinuxParser::UpTime(); 
}