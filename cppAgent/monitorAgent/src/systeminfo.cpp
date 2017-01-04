#include <string>
#include <fstream>
#include <iostream>
#include <cstdint>
#include <cstring>
#include "systeminfo.h"

using namespace std;

int32_t LAST_CPU_WORK_TIME = -1;
int32_t LAST_CPU_TOTAL_TIME = -1;

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
    ifstream fs;
    fs.open("/proc/stat");
    getline(fs, result);
    return result;
}

percent_t get_syetem_cpu_usage()
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

    if (LAST_CPU_WORK_TIME > 0 && LAST_CPU_TOTAL_TIME > 0)
    {
        return ((percent_t)(work_time - LAST_CPU_WORK_TIME)) / (total_time - LAST_CPU_TOTAL_TIME);
    }

    LAST_CPU_WORK_TIME = work_time;
    LAST_CPU_TOTAL_TIME = total_time;

    return -1;
}

void get_system_mem_info(int32_t *total_mem, int32_t *available_mem)
{
    string total_result;
    ifstream fs;
    fs.open("/proc/meminfo");
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