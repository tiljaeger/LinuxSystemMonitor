#include "processor.h"
#include "linux_parser.h"
#include <vector>
#include <string>
#include <iostream>


using std::string;
using std::vector;

float Processor::Utilization() { 
    vector<string> cpuInfo = LinuxParser::CpuUtilization();
    double user, nice, system, idle, iowait, irq, softirq, steal;
 
     user = stod(cpuInfo[0]);
     nice = stod(cpuInfo[1]);
     system = stod(cpuInfo[2]);
     idle = stod(cpuInfo[3]);
     iowait = stod(cpuInfo[4]);
     irq = stod(cpuInfo[5]);
     softirq = stod(cpuInfo[6]);
     steal = stod(cpuInfo[7]);

    double PrevIdle = prevIdle_ + prevIoWait_;
    double Idle = idle + iowait;

    double PrevNonIdle = prevUser_ + prevNice_ + prevSystem_ + prevIrq_ + prevSoftIrq_ + prevSteal_;
    double NonIdle = user + nice + system +irq + softirq + steal;

    double PrevTotal = PrevIdle + PrevNonIdle;
    double Total = Idle + NonIdle;

    // differentiate current value minus previous value
    double totalDiff = Total - PrevTotal;
    double idleDiff = Idle - PrevIdle;

    float result = (totalDiff - idleDiff) / totalDiff;

    assignPreviousValues(idle, iowait, user, nice, system, irq, softirq, steal);


    return result;
}

void Processor::assignPreviousValues(double idle, double iowait, double user, double nice, double system, double irq, double softirq, double steal) {
    prevIdle_ = idle;
    prevIoWait_ = iowait;
    prevUser_ = user;
    prevNice_ = nice;
    prevSystem_ = system;
    prevIrq_ = irq;
    prevSoftIrq_ = softirq;
    prevSteal_ = steal;
}