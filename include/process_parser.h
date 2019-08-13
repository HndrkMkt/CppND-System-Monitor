#ifndef PROCESS_PARSER_H
#define PROCESS_PARSER_H

#include <string>
#include <vector>

class ProcessParser {
public:
    static string getCmd(string pid);

    static vector<string> getPidList();

    static string getVmSize(string pid);

    static string getCpuPercent(string pid);

    static long int getSysUpTime();

    static string getProcUpTime(string pid);

    static string getProcUser(string pid);

    static vector<string> getSysCpuPercent(string coreNumber = "");

    static string getSysRamPercent();

    static string getSysKernelVersion();

    static string getTotalThreads();

    static string getTotalNumberOfProcesses();

    static string getNumberOfRunningProcesses();

    static string getOsName();

    static string printCpuStats(vector <string> values1, vector <string> values2);
};

#endif