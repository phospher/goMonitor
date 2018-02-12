#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <memory>
#include "systeminfo2.h"
#include "utils/data.h"
#include "utils.h"
#include <sys/types.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <stdexcept>
#include <string>
#include <cstring>
#include <fstream>
#include "processinfo.h"
#include "utils/config.h"

using namespace std;

log4cpp::Category &SystemInfoProvider::LOGGER = log4cpp::Category::getRoot();

SystemInfoProvider::SystemInfoProvider() : CurrentSystemInfo(new SystemInfo()), LastSystemCPUTime(-1, -1),
                                           SystemWorkTimeDiff(-1)
{
    const string &mac_address = this->init_ip_address();
    this->init_mac_address(mac_address);

    string process_names_str = CURRENT_CONFIG_PROVIDER->get_config_value("System", "ConcernedProcesses");
    vector<string> process_names;
    split_string2(process_names_str, process_names, ",");
    for (string item : process_names)
    {
        this->ProcessInfoProviders.push_back(new ProcessInfoProvider(item));
    }
    this->CurrentSystemInfo->get_process_infoes().resize(this->ProcessInfoProviders.size());
}

shared_ptr<SystemInfo> SystemInfoProvider::get_system_info()
{
    this->CurrentSystemInfo->set_cpu_usage(this->get_system_cpu_usage());
    this->CurrentSystemInfo->set_memory_usage(this->get_system_mem_usage());
    this->CurrentSystemInfo->set_time(time(NULL));
    int32_t total_mem = 0;
    int32_t available_mem = 0;
    this->get_system_mem_info(&total_mem, &available_mem);
    for (int i = 0; i < this->ProcessInfoProviders.size(); i++)
    {
        this->CurrentSystemInfo->get_process_infoes()[i] =
            this->ProcessInfoProviders[i]->get_process_info(total_mem, available_mem, this->SystemWorkTimeDiff);
    }
    LOGGER << log4cpp::Priority::DEBUG << "sucess get system info";
    return this->CurrentSystemInfo;
}

string SystemInfoProvider::init_ip_address() const
{
    LOGGER.debug("get ip address");
    struct ifaddrs *ifAddrStruct = NULL;
    struct ifaddrs *ifa = NULL;
    void *tmpAddrPtr = NULL;
    int ret = getifaddrs(&ifAddrStruct);
    string ifa_name;
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
            string ip_address(address_buffer);
            this->CurrentSystemInfo->set_ip_address(ip_address);
            ifa_name = ifa->ifa_name;
            break;
        }
    }
    if (ifAddrStruct != NULL)
    {
        freeifaddrs(ifAddrStruct);
    }

    return ifa_name;
}

void SystemInfoProvider::init_mac_address(const string &net_name)
{
    struct ifreq s;
    int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (fd < 0)
    {
        runtime_error ex(strerror(errno));
        throw ex;
    }

    stringstream stream;

    strcpy(s.ifr_name, net_name.c_str());
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
    this->CurrentSystemInfo->set_mac_address(stream.str());
}

percent_t SystemInfoProvider::get_system_cpu_usage()
{
    string cpu_result = this->get_system_cpu_stat();
    shared_ptr<vector<string>> cpu_result_list = split_string_by_whitspace2(cpu_result);
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

    if (this->LastSystemCPUTime.get_work_time() > 0 && this->LastSystemCPUTime.get_total_time() > 0)
    {
        this->SystemWorkTimeDiff = work_time - this->LastSystemCPUTime.get_work_time();
        return ((percent_t)(work_time - this->LastSystemCPUTime.get_work_time())) / (total_time - this->LastSystemCPUTime.get_total_time());
    }

    this->LastSystemCPUTime.set_work_time(work_time);
    this->LastSystemCPUTime.set_total_time(total_time);

    return -1;
}

string SystemInfoProvider::get_system_cpu_stat()
{
    string result;
    ifstream fs("/proc/stat");
    getline(fs, result);
    fs.close();
    return result;
}

percent_t SystemInfoProvider::get_system_mem_usage()
{
    int32_t total_mem = 0;
    int32_t available_mem = 0;
    this->get_system_mem_info(&total_mem, &available_mem);
    return 1 - ((percent_t)available_mem) / total_mem;
}

void SystemInfoProvider::get_system_mem_info(int32_t *total_mem, int32_t *available_mem)
{
    string total_result;
    ifstream fs("/proc/meminfo");
    getline(fs, total_result);
    shared_ptr<vector<string>> total_result_list = split_string_by_whitspace2(total_result);
    *total_mem = stoi((*total_result_list)[1]);

    getline(fs, total_result);

    string available_result;
    getline(fs, available_result);
    shared_ptr<vector<string>> available_result_list = split_string_by_whitspace2(available_result);
    *available_mem = stoi((*available_result_list)[1]);
    fs.close();
}

// ProcessInfo *SystemInfoProvider::get_process_info(string &process_name)
// {
//     int32_t total_mem = 0;
//     int32_t available_mem = 0;
//     this->get_system_mem_info(&total_mem, &available_mem);
//     return ProcessInfoProvider(process_name, total_mem, available_mem, this->SystemWorkTimeDiff).get_process_info();
// }