#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"


using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { 
    vector<string> cpu_utilization = LinuxParser::CpuUtilization();
    Processor processor{};    
    return cpu_; 
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { return processes_; }

std::string System::Kernel() { 
    return LinuxParser::Kernel(); 
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() {     
    return LinuxParser::MemoryUtilization(); 
}

std::string System::OperatingSystem() { 
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