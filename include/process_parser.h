#ifndef PROCESS_PARSER_H
#define PROCESS_PARSER_H

#include <string>
#include <vector>

class ProcessParser {
public:
    static std::string getCmd(std::string pid);

    static std::vector <std::string> getPidList();

    static std::string getVmSize(std::string pid);

    static std::string getCpuPercent(std::string pid);

    static long int getSysUpTime();

    static std::string getProcUpTime(std::string pid);

    static std::string getProcUser(std::string pid);

    static std::vector <std::string> getSysCpuPercent(std::string coreNumber = "");

    static std::string getSysRamPercent();

    static std::string getSysKernelVersion();

    static std::string getTotalThreads();

    static std::string getTotalNumberOfProcesses();

    static std::string getNumberOfRunningProcesses();

    static string getOsName();

    static std::string printCpuStats(std::vector <std::string> values1, std::vector <std::string> values2);
};

#endif