#include <string>
#include <iostream>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds[[maybe_unused]]) { 
    int min = seconds / 60;
    int hours = min / 60;
    int sec = seconds % 60;
    std::string result = std::to_string(hours)+ ":" + std::to_string(min) + ":" + std::to_string(sec);
    return result; 
}