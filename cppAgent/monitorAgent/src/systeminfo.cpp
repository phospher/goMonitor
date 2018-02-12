#include <string>
#include <fstream>
#include <iostream>
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <map>
#include <sys/types.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <stdexcept>
#include "systeminfo.h"
#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include "utils/config.h"
#include <ctime>
#include <unistd.h>
#include <memory>
#include "processinfo.h"
#include "utils.h"

using namespace std;

CPUTime LAST_SYSTEM_CPU_TIME(-1, -1);

string *ip_address = NULL;
string *mac_address = NULL;

map<string, CPUTime *> LAST_PROCESS_CPU_TIME;

int32_t SYSTEM_WORK_TIME_DIFF = -1;

log4cpp::Category &logger = log4cpp::Category::getRoot();

vector<string> *split_string_by_whitspace(const string &str)
{
    vector<string> *result = new vector<string>;
    char *pch = strtok((char *)str.c_str(), " \t\n");
    while (pch != NULL)
    {
        result->push_back(string(pch));
        pch = strtok(NULL, " \t\n");
    }
    return result;
}

string get_system_cpu_stat()
{
    string result;
    ifstream fs("/proc/stat");
    getline(fs, result);
    fs.close();
    return result;
}

percent_t get_system_cpu_usage()
{
    string cpu_result = get_system_cpu_stat();
    vector<string> *cpu_result_list = split_string_by_whitspace(cpu_result);
    int32_t work_time = 0;
    int32_t total_time = 0;
    for (int32_t i = 1; i <= 3; i++)
    {
        work_time += stoi((*cpu_result_list)[i]);
    }
    for (int32_t i = 1; i < cpu_result_list->size(); i++)
    {
        total_time += stoi((*cpu_result_list)[i]);
    }
    delete cpu_result_list;

    if (LAST_SYSTEM_CPU_TIME.get_work_time() > 0 && LAST_SYSTEM_CPU_TIME.get_total_time() > 0)
    {
        SYSTEM_WORK_TIME_DIFF = work_time - LAST_SYSTEM_CPU_TIME.get_work_time();
        return ((percent_t)(work_time - LAST_SYSTEM_CPU_TIME.get_work_time())) / (total_time - LAST_SYSTEM_CPU_TIME.get_total_time());
    }

    LAST_SYSTEM_CPU_TIME.set_work_time(work_time);
    LAST_SYSTEM_CPU_TIME.set_total_time(total_time);

    return -1;
}

void get_system_mem_info(int32_t *total_mem, int32_t *available_mem)
{
    string total_result;
    ifstream fs("/proc/meminfo");
    getline(fs, total_result);
    vector<string> *total_result_list = split_string_by_whitspace(total_result);
    *total_mem = stoi((*total_result_list)[1]);

    getline(fs, total_result);

    string available_result;
    getline(fs, available_result);
    vector<string> *available_result_list = split_string_by_whitspace(available_result);
    *available_mem = stoi((*available_result_list)[1]);
    fs.close();
}

percent_t get_system_mem_usage()
{
    int32_t total_mem = 0;
    int32_t available_mem = 0;
    get_system_mem_info(&total_mem, &available_mem);
    return 1 - ((percent_t)available_mem) / total_mem;
}

ProcessInfo *get_process_info(string &process_name)
{
    // int32_t total_mem = 0;
    // int32_t available_mem = 0;
    // get_system_mem_info(&total_mem, &available_mem);
    // return ProcessInfoProvider(process_name, total_mem, available_mem, SYSTEM_WORK_TIME_DIFF).get_process_info();
    return NULL;
}

void init_mac_address(const char *net_name)
{
    if (mac_address == NULL)
    {
        struct ifreq s;
        int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
        if (fd < 0)
        {
            runtime_error ex(strerror(errno));
            throw ex;
        }

        stringstream stream;

        strcpy(s.ifr_name, net_name);
        if (0 == ioctl(fd, SIOCGIFHWADDR, &s))
        {
            int i;
            for (i = 0; i < 6; ++i)
            {
                char buf[10];
                sprintf(buf, "%02x", (unsigned char)s.ifr_addr.sa_data[i]);
                stream << buf;
                if (i < 5)
                {
                    stream << ":";
                }
            }
        }
        else
        {
            runtime_error ex(strerror(errno));
            throw ex;
        }
        mac_address = new string(stream.str());
    }
}

string *get_ip_address()
{
    if (ip_address == NULL)
    {
        logger.debug("get ip address");
        struct ifaddrs *ifAddrStruct = NULL;
        struct ifaddrs *ifa = NULL;
        void *tmpAddrPtr = NULL;
        int ret = getifaddrs(&ifAddrStruct);
        if (ret < 0)
        {
            runtime_error ex(strerror(errno));
            throw ex;
        }
        for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next)
        {
            if (!ifa->ifa_addr)
            {
                continue;
            }
            if (ifa->ifa_addr->sa_family == AF_INET && strcmp(ifa->ifa_name, "lo") != 0)
            {
                tmpAddrPtr = &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
                char address_buffer[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, tmpAddrPtr, address_buffer, INET_ADDRSTRLEN);
                ip_address = new string(address_buffer);
                init_mac_address(ifa->ifa_name);
                break;
            }
        }
        if (ifAddrStruct != NULL)
        {
            freeifaddrs(ifAddrStruct);
        }
    }
    return ip_address;
}

string *get_mac_address()
{
    return mac_address;
}

void split_string(const string &str, std::vector<std::string> &result, const string &sep)
{
    std::string::size_type pos1, pos2;
    pos2 = str.find(sep);
    pos1 = 0;
    while (std::string::npos != pos2)
    {
        result.push_back(str.substr(pos1, pos2 - pos1));

        pos1 = pos2 + sep.size();
        pos2 = str.find(sep, pos1);
    }
    if (pos1 != str.length())
        result.push_back(str.substr(pos1));
}

shared_ptr<SystemInfo> get_system_info()
{
    SystemInfo *result = new SystemInfo;
    result->set_ip_address(*get_ip_address());
    result->set_mac_address(*get_mac_address());
    result->set_cpu_usage(get_system_cpu_usage());
    result->set_memory_usage(get_system_mem_usage());
    result->set_time(time(NULL));
    string process_names_str = CURRENT_CONFIG_PROVIDER->get_config_value("System", "ConcernedProcesses");
    vector<string> process_names;
    split_string(process_names_str, process_names, ",");
    for (string item : process_names)
    {
        ProcessInfo *process_info = get_process_info(item);
        if (process_info != NULL)
        {
            result->get_process_infoes().push_back(process_info);
        }
    }
    logger << log4cpp::Priority::DEBUG << "sucess get system info";
    return shared_ptr<SystemInfo>(result);
}