#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <time.h>
#include "format.h"
#include "time.h"
#include "format.h"

using std::string;

string Format::ElapsedTime(long secs) { 
    time_t seconds(secs);
    tm *p = gmtime(&seconds);

    std::stringstream ss;
    // found somewehre in internet???
    ss << std::setfill('0') << std::setw(2) << p->tm_hour << ":" << std::setfill('0') << std::setw(2) << p->tm_min << ":" << std::setfill('0') << std::setw(2) << p->tm_sec;

    return ss.str(); 
}