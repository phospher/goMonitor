#include <string>
#include <fstream>
#include <iostream>
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <map>
#include "systeminfo.h"

using namespace std;

class CPUTime
{
  public:
    int32_t WorkTime;
    int32_t TotalTime;
    CPUTime(int32_t work_time, int32_t total_time)
        : WorkTime(work_time), TotalTime(total_time)
    {
    }
};

CPUTime LAST_SYSTEM_CPU_TIME(-1, -1);

map<string, CPUTime> LAST_PROCESS_CPU_TIME;

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

    if (LAST_SYSTEM_CPU_TIME.WorkTime > 0 && LAST_SYSTEM_CPU_TIME.TotalTime > 0)
    {
        return ((percent_t)(work_time - LAST_SYSTEM_CPU_TIME.WorkTime)) / (total_time - LAST_SYSTEM_CPU_TIME.TotalTime);
    }

    LAST_SYSTEM_CPU_TIME.WorkTime = work_time;
    LAST_SYSTEM_CPU_TIME.TotalTime = total_time;

    return -1;
}

void get_system_mem_info(int32_t *total_mem, int32_t *available_mem)
{
    string total_result;
    ifstream fs("/proc/meminfo");
    getline(fs, total_result);
    cout << total_result << endl;
    vector<string> *total_result_list = split_string_by_whitspace(total_result);
    *total_mem = stoi((*total_result_list)[1]);

    getline(fs, total_result);

    string available_result;
    getline(fs, available_result);
    cout << available_result << endl;
    vector<string> *available_result_list = split_string_by_whitspace(available_result);
    *available_mem = stoi((*available_result_list)[1]);
    fs.close();
}

percent_t get_system_mem_usage()
{
    int32_t total_mem = 0;
    int32_t available_mem = 0;
    get_system_mem_info(&total_mem, &available_mem);
    cout << total_mem << endl;
    cout << available_mem << endl;
    return 1 - ((percent_t)available_mem) / total_mem;
}

vector<int32_t> *get_pid_by_name(string &name)
{
    char temp[1024];
    FILE *pp = popen(("pgrep " + name).c_str(), "r");
    vector<int32_t> *result = new vector<int32_t>;
    while (fgets(temp, sizeof(temp), pp) != NULL)
    {
        result->push_back(stoi(string(temp)));
    }
    pclose(pp);

    return result;
}

vector<string> *get_process_stat(int32_t pid)
{
    char proc_file_name[1024];
    sprintf(proc_file_name, "/proc/%d/stat", pid);
    ifstream fs(proc_file_name);
    string file_result;
    getline(fs, file_result);
    return split_string_by_whitspace(file_result);
}

ProcessInfo *get_process_info(string &process_name)
{
}