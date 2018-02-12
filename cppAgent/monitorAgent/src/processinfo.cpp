#include "utils.h"
#include "processinfo.h"
#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <string>
#include <memory>
#include <cstdio>
#include <fstream>
#include <unistd.h>

using namespace std;

log4cpp::Category &ProcessInfoProvider::LOGGER = log4cpp::Category::getRoot();

ProcessInfoProvider::ProcessInfoProvider(const string &process_name) : ProcessName(process_name) {}

ProcessInfoProvider::~ProcessInfoProvider()
{
    if (this->LastCPUTime != NULL)
    {
        delete this->LastCPUTime;
    }
}

ProcessInfo *ProcessInfoProvider::get_process_info(const int32_t total_mem, const int32_t available_mem,
                                                   const int32_t system_work_time_diff)
{
    ProcessInfo *result = NULL;
    shared_ptr<vector<int32_t>> pids = this->get_pid_by_name();
    if (pids != NULL && pids->size() > 0)
    {
        result = new ProcessInfo;
        result->set_process_name(this->ProcessName);
        int32_t total_cpu_time = 0;
        percent_t process_total_mem = 0;
        for (int32_t pid : *pids)
        {
            shared_ptr<vector<string>> process_stat = this->get_process_stat(pid);
            total_cpu_time += this->get_process_cpu_time(*process_stat);
            process_total_mem += this->get_process_mem(*process_stat);
        }
        result->set_cpu_usage(this->cal_proces_cpu_usage(total_cpu_time, system_work_time_diff));
        result->set_memory_usage(process_total_mem / (total_mem - available_mem));
    }
    ProcessInfoProvider::LOGGER << log4cpp::Priority::DEBUG << "success get process info: " << this->ProcessName;
    return result;
}

shared_ptr<vector<int32_t>> ProcessInfoProvider::get_pid_by_name()
{
    ProcessInfoProvider::LOGGER << log4cpp::Priority::DEBUG << "try to get pid: " << this->ProcessName;
    char temp[1024];
    FILE *pp = popen(("pgrep " + this->ProcessName).c_str(), "r");
    vector<int32_t> *result = new vector<int32_t>;
    while (fgets(temp, sizeof(temp), pp) != NULL)
    {
        result->push_back(stoi(string(temp)));
    }
    pclose(pp);

    return shared_ptr<vector<int32_t>>(result);
}

shared_ptr<vector<string>> ProcessInfoProvider::get_process_stat(int32_t pid)
{
    char proc_file_name[1024];
    sprintf(proc_file_name, "/proc/%d/stat", pid);
    ifstream fs(proc_file_name);
    string file_result;
    getline(fs, file_result);
    return split_string_by_whitspace2(file_result);
}

int32_t ProcessInfoProvider::get_process_cpu_time(vector<string> &process_stat)
{
    if (process_stat.size() > 0)
    {
        int cpu_time = stoi(process_stat[13]) + stoi(process_stat[14]);
        return cpu_time;
    }
    else
    {
        return -1;
    }
}

float ProcessInfoProvider::get_process_mem(vector<string> &process_stat)
{
    if (process_stat.size() > 0)
    {
        int page_usage = stoi(process_stat[23]);
        long page_size = sysconf(_SC_PAGE_SIZE);
        return (float)(page_usage * page_size) / 1000.0;
    }
    else
    {
        return -1;
    }
}

percent_t ProcessInfoProvider::cal_proces_cpu_usage(int32_t cpu_time, const int32_t system_work_time_diff)
{
    if (this->LastCPUTime != NULL)
    {
        percent_t result = ((percent_t)cpu_time - this->LastCPUTime->get_work_time()) / system_work_time_diff;
        this->LastCPUTime->set_work_time(cpu_time);
        this->LastCPUTime->set_total_time(cpu_time);
        return result;
    }
    else
    {
        this->LastCPUTime = new CPUTime(cpu_time, cpu_time);
        return -1;
    }
}