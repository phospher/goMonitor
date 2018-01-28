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

CPUTime *ProcessInfoProvider::LAST_CPU_TIME = NULL;

ProcessInfoProvider::ProcessInfoProvider(const string &process_name, int32_t total_mem, int32_t available_mem)
    : ProcessName(process_name), TotalMem(total_mem), AvailableMem(available_mem) {}

shared_ptr<ProcessInfo> ProcessInfoProvider::get_process_info()
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
        result->set_cpu_usage(this->cal_proces_cpu_usage(total_cpu_time));
        result->set_memory_usage(process_total_mem / (this->TotalMem - this->AvailableMem));
    }
    ProcessInfoProvider::LOGGER << log4cpp::Priority::DEBUG << "success get process info: " << this->ProcessName;
    return shared_ptr<ProcessInfo>(result);
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

percent_t ProcessInfoProvider::cal_proces_cpu_usage(int32_t cpu_time)
{
    if (ProcessInfoProvider::LAST_CPU_TIME != NULL)
    {
        percent_t result = ((percent_t)cpu_time - ProcessInfoProvider::LAST_CPU_TIME->get_work_time()) / SYSTEM_WORK_TIME_DIFF;
        ProcessInfoProvider::LAST_CPU_TIME->set_work_time(cpu_time);
        ProcessInfoProvider::LAST_CPU_TIME->set_total_time(cpu_time);
        return result;
    }
    else
    {
        ProcessInfoProvider::LAST_CPU_TIME = new CPUTime(cpu_time, cpu_time);
        return -1;
    }
}