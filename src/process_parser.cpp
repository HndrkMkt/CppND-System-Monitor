#include <algorithm>
#include <iostream>
#include <math.h>
#include <thread>
#include <chrono>
#include <iterator>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cerrno>
#include <cstring>
#include <dirent.h>
#include <time.h>
#include <unistd.h>
#include <constants.h>
#include "process_parser.h"
#include "util.h"
// Reading /proc/[PID]/status for memory status of the specified process

string ProcessParser::getVmSize(string pid) {
    string line;
    // Declaring search attribute for file
    string name = "VmData";
    string value;
    float result;
    // Opening stream for specific file
    ifstream stream = Util::getStream((Path::basePath() + pid + Path::statusPath()));
    while (getline(stream, line)) {
        // Searching line by line
        if (line.compare(0, name.size(), name) == 0) {
            // Slicing string line on ws for values using sstream
            istringstream buf(line);
            istream_iterator<string> beg(buf), end;
            vector<string> values(beg, end);
            // Conversion kB -> GB
            result = (stof(values[1]) / float(1024 * 1024));
            break;
        }
    }
    return to_string(result);
}

string ProcessParser::getCpuPercent(string pid) {
    string line;
    string value;
    float result;
    ifstream stream = Util::getStream((Path::basePath() + pid + "/" + Path::statPath()));
    getline(stream, line);
    string str = line;
    istringstream buf(str);
    istream_iterator<string> beg(buf), end;
    vector<string> values(beg, end); // Done!
    // Acquiring relevant times for calculation of active occupation of CPU for selected process
    float utime = stof(ProcessParser::getProcUpTime(pid));
    float stime = stof(values[14]);
    float cutime = stof(values[15]);
    float cstime = stof(values[16]);
    float starttime = stof(values[21]);
    float uptime = ProcessParser::getSysUpTime();
    float freq = sysconf(_SC_CLK_TCK);
    float total_time = utime + stime + cutime + cstime;
    float seconds = uptime - (starttime / freq);
    result = 100.0 * ((total_time / freq) / seconds);
    return to_string(result);
}

string ProcessParser::getProcUpTime(string pid) {
    string line;
    string value;
    ifstream stream = Util::getStream((Path::basePath() + pid + "/" + Path::statPath()));
    getline(stream, line);
    string str = line;
    istringstream buf(str);
    istream_iterator<string> beg(buf), end;
    vector<string> values(beg, end); // Done!
    // Using sysconf to get clock ticks on the host machine
    return to_string(float(stof(values[13]) / sysconf(_SC_CLK_TCK)));
}

long int ProcessParser::getSysUpTime() {
    string line;
    ifstream stream = Util::getStream((Path::basePath() + Path::upTimePath()));
    getline(stream, line);
    istringstream buf(line);
    istream_iterator<string> beg(buf), end;
    vector<string> values(beg, end);
    return stoi(values[0]);
}